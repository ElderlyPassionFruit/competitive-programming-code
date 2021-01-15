#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

long long lcm(int a, int b) {
	return a * b / __gcd(a, b);
}

void solve() {
	int a, b;
	cin >> a >> b;
	int ans = a;
	int s = b - 65;
	chkmax(s, 1);
	for (int i = b; i >= s; i--) {
		chkmax(ans, lcm(a, i));
	}
	cout << ans << "\n";
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}