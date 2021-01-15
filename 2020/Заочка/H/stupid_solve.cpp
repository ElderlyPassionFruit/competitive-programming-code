#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

bool solve(int p, int q, int a, int b, ll n) {
	if (a < 0 || b < 0) return false;
	if (a * p > n) return false;
	if (n == 0) return true;
	if (b && n % q == 0 && solve(p, q, a, b - 1, n / q)) return true;
	return solve(p, q, a - 1, b, n - p);
}

void solve(){
	int p, q, a, b;
	ll n;
	cin >> p >> q >> a >> b >> n;
	if (solve(p, q, a, b, n))
		cout << "Yes\n";
	else
		cout << "No\n";
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t--)
		solve();
	return 0;
}