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

void solve(vector<ll> &as, ll p, ll q, ll k) {
  ll n = as.size();
  vector<ll> individual(n+1,0);
  vector<ll> b(n+1,0);
  vector<ll> c(n+1,0);
  for (ll i = 0; i < n; i++) {
    individual[i+1] = individual[i] + min((as[i] % q) % p, as[i] % p);
    b[i+1] = b[i] + (as[i] % p);
    c[i+1] = c[i] + ((as[i] % q) % p);
  }

  ll ans = numeric_limits<ll>::max();
  for (ll i = 0; i < n - k + 1; i++) {
    ll l = i;
    ll r = i + k - 1;
    ll int_b = b[r+1] - b[l];
    ll int_c = c[r+1] - c[l];
    ll ind_l = individual[l];
    ll ind_r = individual[n] - individual[r+1];
    ans = min(ans, ind_l + ind_r + min(int_b, int_c));
  }
  cout << ans << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;
  while (t--) {
    ll n, k, p, q;
    cin >> n >> k >> p >> q;
    vector<ll> as(n,0 );
    for (int i = 0; i < n; i++) {
      cin >> as[i];
    }
    solve(as, p, q, k);
  }

  return 0;
}
