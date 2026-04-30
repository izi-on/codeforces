
#pragma once

#include <algorithm>
#include <array>
#include <bitset>
#include <cctype>
#include <chrono>
#include <cmath>
#include <complex>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <optional>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#ifdef LOCAL
#define dbg(...)                                                               \
  ::debug::dbg_impl(__FILE__, __LINE__, #__VA_ARGS__, __VA_ARGS__)
#else
#define dbg(...) ((void)0)
#endif

namespace debug {

// ---------- tuple printing ----------
template <std::size_t I = 0, class... Ts>
inline std::enable_if_t<I == sizeof...(Ts), void>
tuple_print(std::ostream &, const std::tuple<Ts...> &) {}

template <std::size_t I = 0, class... Ts>
    inline std::enable_if_t <
    I<sizeof...(Ts), void> tuple_print(std::ostream &os,
                                       const std::tuple<Ts...> &t) {
  if (I)
    os << ", ";
  os << std::get<I>(t);
  tuple_print<I + 1>(os, t);
}

template <class... Ts>
inline std::ostream &operator<<(std::ostream &os, const std::tuple<Ts...> &t) {
  os << "(";
  tuple_print(os, t);
  return os << ")";
}

// ---------- pair ----------
template <class A, class B>
inline std::ostream &operator<<(std::ostream &os, const std::pair<A, B> &p) {
  return os << "(" << p.first << ", " << p.second << ")";
}

// ---------- strings (FIXED: avoid infinite recursion) ----------
inline std::ostream &operator<<(std::ostream &os, const std::string &s) {
  os.put('"');
  ::std::operator<<(os, s); // force std::string overload
  os.put('"');
  return os;
}

inline std::ostream &operator<<(std::ostream &os, const char *s) {
  os.put('"');
  ::std::operator<<(os, s ? s : "(null)");
  os.put('"');
  return os;
}

// ---------- iterable detection ----------
template <class T, class = void> struct is_iterable : std::false_type {};
template <class T>
struct is_iterable<T, std::void_t<decltype(std::begin(std::declval<T>())),
                                  decltype(std::end(std::declval<T>()))>>
    : std::true_type {};

template <class T> struct is_string : std::false_type {};
template <> struct is_string<std::string> : std::true_type {};
template <> struct is_string<const char *> : std::true_type {};

// ---------- container printer ----------
template <class T>
inline std::enable_if_t<is_iterable<T>::value && !is_string<T>::value,
                        std::ostream &>
operator<<(std::ostream &os, const T &v) {
  os << "{";
  bool first = true;
  for (auto &&x : v) {
    if (!first)
      os << ", ";
    first = false;
    os << x;
  }
  return os << "}";
}

// ---------- priority_queue (by copy) ----------
template <class T, class C, class Comp>
inline std::ostream &operator<<(std::ostream &os,
                                std::priority_queue<T, C, Comp> pq) {
  os << "pq[";
  bool first = true;
  while (!pq.empty()) {
    if (!first)
      os << ", ";
    first = false;
    os << pq.top();
    pq.pop();
  }
  return os << "]";
}

// ---------- dbg implementation ----------
inline void print_split(std::ostream &) {}

template <class Head, class... Tail>
inline void print_split(std::ostream &os, const Head &h, const Tail &...t) {
  os << h;
  if constexpr (sizeof...(t))
    os << " | ";
  print_split(os, t...);
}

template <class... Ts>
inline void dbg_impl(const char *file, int line, const char *names,
                     const Ts &...xs) {
  std::cerr << "[DBG] " << file << ":" << line << "  " << names << " = ";
  print_split(std::cerr, xs...);
  std::cerr << "\n";
}

} // namespace debug
