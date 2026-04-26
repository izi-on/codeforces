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

void solve(int x, int y) {
  if (y == 0) {
    cout << "NO" << endl;
    return;
  }
  if (x == 0) {
    if (y % 2 == 0) {
      cout << "NO" << endl;
      return;
    }
    cout << "YES" << endl;
    for (int i = 2; i <= y; i++) {
      cout << 1 << " " << i << endl;
    }
    return;
  }
  if (x > y) {cout << "NO" << endl; return;}
  cout << "YES" << endl;
  cout << 1 << " " << 2 << endl;
  int ptr = 2;
  for (int i = 2; i <= x; i+=1) {
    cout << ptr << " " << ptr + 1 << endl;
    cout << ptr + 1 << " " << ptr + 2 << endl;
    ptr = ptr + 2;
  }

  int p = ptr;
  int c = p + 1;
  for (int i = x+1; i <= y; i++) {
    cout << p << " " << c << endl;
    c++;
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;
  while (t--) {
    int x, y;
    cin >> x >> y;
    solve(x,y);
  }

  return 0;
}
