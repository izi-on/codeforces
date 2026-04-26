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

void solve(vi &hs, int h) {
  int n = hs.size();
  vector<ll> drained(n, 0);
  for (int i = 0; i < n; i++) {
    ll cur = hs[i];
    ll dr = 0;
    dr += h - cur;
    for (int k = i-1; k >= 0; k--) {
      cur = max(cur, (ll) hs [k]);
      dr += h - cur;
    }
    cur = hs[i];
    for (int k = i+1; k < n; k++) {
      cur = max(cur, (ll) hs [k]);
      dr += h - cur;
    }
    drained[i] = dr;
  }

  ll cand_ans = 0;
  for (int i = 0; i < n; i++) {
    int mij_val = hs[i];
    int mij = i;
    for (int j = i; j < n; j++) {
      if (mij_val < hs[j]) {
        mij = j;
        mij_val = hs[j];
      }
      cand_ans = max(cand_ans, drained[i] + drained[j] - drained[mij]);
    }
  }
  cout << cand_ans << endl;
}

int main() {
  ios::sync_with_stdio(false);

  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--) {
    int n,h;
    cin >> n >> h;
    vi hs(n,0);
    for (int i = 0; i < n; i++) {
      cin >> hs[i];
    }
    solve(hs, h);
  }

  return 0;
}
