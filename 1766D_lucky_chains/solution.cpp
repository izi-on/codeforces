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
#include <queue>
#include <random>
#include <set>
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

int solve(int n1, int n2, vector<int>& spf) {
  int tmp = min(n1, n2);
  int tmp2 = max(n1, n2);
  n1 = tmp;
  n2 = tmp2;

  if (n2 - n1 == 1) return -1;

  int diff = n2 - n1;
  int smallest_chain = numeric_limits<int>::max();
  while (diff > 1) {
    int i = spf[diff];
    if (diff % i == 0) {
      int smallest_steps = (n2 % i == 0) ? 0 : (i - (n2 % i));
      smallest_chain = min(smallest_chain, smallest_steps);

      if (smallest_chain == 0)
        break;
    }
    diff /= i;
  }

  return smallest_chain;

}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  vector<int> primes;
  vector<int> spf(10000000 + 1, 0);

  for (int i = 2; i < 1e7 + 1; i++) {
    if (spf[i] == 0) {
      spf[i] = i;
      primes.push_back(i);
    }
    for (auto p : primes) {
      if (i * p > 10000000)
        break;
      spf[i * p] = p;
      if (i % p == 0)
        break;
    }
  }

  int n;
  cin >> n;
  while (n--) {
    int n1, n2;
    cin >> n1 >> n2;
    cout << solve(n1, n2, spf) << endl;
  }

  return 0;
}
