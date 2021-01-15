#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

bool check(int x, int n) {
	int cnt_bridges = (x + 1) / 2;
	if (cnt_bridges > n - 1)
		return false;
	int m = n - cnt_bridges;
	return cnt_bridges + m * (m - 1) / 2 >= x;
}

void solve() {
	int n;
	cin >> n;
	int l = 0, r = 2 * n;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (check(mid, n))
			l = mid;
		else
			r = mid;
	}
	cout << l << "\n";
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