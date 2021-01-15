#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(), (x).end()
template <typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

mt19937 rnd(time(0));

const int MAXN = 900;

ll dp[MAXN][MAXN];

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.setf(ios::fixed), cout.precision(20);
    int n = MAXN - 1;
  	for (int i = 0; i < n; i++) {
  		for (int j = 0; j < n; j++) {
  			dp[i][j] = rnd();
  		}
  	}
  	for (int k = 0; k < n; k++) {
  		for (int i = 0; i < n; i++) {
  			for (int j = 0; j < n; j++) {
  				chkmin(dp[i][j], dp[i][k] + dp[k][j]);
  			}
  		}
  	}
  	vector<ll> a;
  	ll x;
  	while (cin >> x) {
  		a.push_back(x);
  	}
  	reverse(all(a));
  	for (auto i : a) {
  		cout << i << " ";
  	}
  	cout << endl;
    return 0;
}