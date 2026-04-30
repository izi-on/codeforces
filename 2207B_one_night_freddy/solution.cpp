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

void solve(vi & resets, int m, int l) {
  int n = resets.size();
  multiset<int> animatronics;
  for (int i = 0; i < min(n+1, m); i++) {
    animatronics.insert(0);
  }
  int prev = 0;
  for (int i = 0; i < resets.size(); i++) {
    for (int s = prev+1; s <= resets[i]; s++) {
      auto it = animatronics.begin();
      auto val = *it;
      animatronics.erase(it);
      animatronics.insert(val + 1);
    }
    prev = resets[i];
;
    auto mx_iter = --animatronics.end();
    animatronics.erase(mx_iter);
    int resets_left = resets.size() - i - 1;
    if (animatronics.size() < resets_left+1) {
      animatronics.insert(0);
    }
  }
  cout << (l - resets[resets.size() - 1] + *animatronics.begin()) << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;
  while (t--) {
    int n, m, l;
    cin >> n >> m >> l;
    vi resets(n,0);
    for (int i = 0; i < n; i++) {
      cin >> resets[i];
    }
    solve(resets, m, l);
  }

  return 0;
}
