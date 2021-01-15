#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

bool check(int x, int y, int p, int q, int a) {
	return p * a >= x && q * a - p * a >= y - x;
}

void solve() {
	int x, y, p, q;
	cin >> x >> y >> p >> q;

	int l = 0, r = 1e9 + 10;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (check(x, y, p, q, mid))
			r = mid;
		else
			l = mid;
	}
	if (r == 1e9 + 10) {
		cout << -1 << "\n";
	}
	else {
		cout << q * r - y << "\n";
	}
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int q;
	cin >> q;
	while (q--)
		solve();
	return 0;
}