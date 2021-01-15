#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

void solve() {
	string s;
	cin >> s;
	int x = 0, y = 0;
	int max_x, min_x, max_y, min_y;
	max_x = min_x = max_y = min_y = 0;
	for (auto i : s) {
		if (i == 'W') {
			y++;
		}
		if (i == 'S') {
			y--;
		}
		if (i == 'A') {
			x--;
		}
		if (i == 'D') {
			x++;
		}
		chkmax(max_x, x);
		chkmin(min_x, x);
		chkmax(max_y, y);
		chkmin(min_y, y);
	}
	int len1 = max_x - min_x + 1;
	int len2 = max_y - min_y + 1;

	int ans = len1 * len2;
	if (len1 > 1) {
		chkmin(ans, len2 * (len1 - 1));
	}
	if (len2 > 1) {
		chkmin(ans, len1 * (len2 - 1));
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