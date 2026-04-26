#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <complex>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <pthread.h>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

using ll = long long;
using ld = long double;
using ull = unsigned long long;

using pii = pair<int,int>;
using pll = pair<ll,ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<double>;
using vld = vector<ld>;
using vs = vector<string>;

#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define rep(i,a,b) for (int i = (a); i < (b); ++i)
#define per(i,a,b) for (int i = (b) - 1; i >= (a); --i)
#define pb push_back
#define eb emplace_back
#define fi first
#define se second

template <class T>
bool ckmin(T& a, const T& b) {
    if (b < a) {
        a = b;
        return true;
    }
    return false;
}

template <class T>
bool ckmax(T& a, const T& b) {
    if (a < b) {
        a = b;
        return true;
    }
    return false;
}

string pack(int col, int k, int upper, int lower) {
  return to_string(col) + "," + to_string(k) + "," + to_string(upper) + "," + to_string(lower);
}

tuple<int, int, int, int> unpack(string sig) {
  vector<int> parts;
  stringstream ss(sig);
  string part;
  while (getline(ss, part, ',')) {
    parts.push_back(stoi(part));
  }
  return {parts[0], parts[1], parts[2], parts[3]};
}

void solve(int k) {
  map<string, ll> memo;
  map<string, string> forward_best;
  // 0: unrest, 1: empty satis, 2: empty unsatis, 3: mine

  function<ll(int col, int kh, int type_upper, int type_lower)> helper;
  helper = [&](int col, int kh, int type_upper, int type_lower ) -> ll {
    if (kh == 0)
      return 0;
    if (kh < 0)
      return numeric_limits<int>::max();
    if (col >= k)
      return numeric_limits<int>::max();
    string sig = pack(col, kh, type_upper, type_lower);
    if (memo.count(sig) > 0) {
      return memo[sig];
    }

    string best_forward;
    ll best_cost = numeric_limits<int>::max();
    if (type_upper == 3 || type_lower == 3) {
      ll cost = helper(col + 1, kh - 2, 1, 1) + 1;
      if (cost < best_cost) {
        best_forward = pack(col + 1, kh - 2, 1, 1);
        best_cost = cost;
      }
    } else if (type_upper == 2 && type_lower == 2) {

      ll cost = helper(col + 1, kh - 3, 3, 1) + 1;
      if (cost < best_cost) {
        best_forward = pack(col + 1, kh - 3, 3, 1);
        best_cost = cost;
      }

      cost = helper(col + 1, kh - 3, 1, 3) + 1;
      if (cost < best_cost) {
        best_forward = pack(col + 1, kh - 3, 1, 3);
        best_cost = cost;
      }

    } else if (type_upper == 1 && type_lower == 1) {
      ll cost = helper(col + 1, kh, 2, 2) + 1;
      if (cost < best_cost) {
        best_forward = pack(col + 1, kh, 2, 2);
        best_cost = cost;
      }
    }

    memo[sig] = best_cost;
    forward_best[sig] = best_forward;
    return best_cost;
  };

  ll cost = numeric_limits<int>::max();
  cost = min(cost, helper(1, k, 2, 2));
  string fwd = pack(1, k, 2, 2);
  ll cost2 = min(cost, helper(1, k-1, 3, 1));
  string fwd2 = pack(1, k-1, 3, 1);
  if (cost2 < cost) {
    cost = cost2;
    fwd = fwd2;
  }

  vector<pair<int, int>> ans;
  function<void(string)> backtrack;
  backtrack = [&](string sig) {
    auto [col, ks, upper, lower] = unpack(sig);
    ans.push_back({upper, lower});
    if (ks == 0)
      return;
    backtrack(forward_best[sig]);
  };

  if (cost == numeric_limits<int>::max())
    cout << "NO" << endl;
  else {
    cout << "YES" << endl;
    cout << cost + 1 << endl;
    backtrack(fwd);
    for (auto [up, low] : ans) {
      if (up == 1 || up == 2)
        cout << ".";
      else
       cout << "*";
    }
    cout << endl;
    for (auto [up, low] : ans) {
      if (low == 1 || low == 2)
        cout << ".";
      else
       cout << "*";
    }
    cout << endl;
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;
  while (t--) {
    int k;
    cin >> k;
    solve(k);
  }
  return 0;
}
