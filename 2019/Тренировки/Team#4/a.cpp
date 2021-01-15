#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n, m;

void read() {
	cin >> n >> m;
}

bool check(int x, int n, int m) {
	int cnt1 = (x + 1) / 2;
	int cnt2 = x - cnt1;
	int need1 = cnt1 * cnt1 + cnt2 * cnt2;
	int need2 = cnt1 * cnt2 * 2;
	return need1 <= n && need2 <= m;
}

int ans;

void run() {
	int l = 0, r = 1e9;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (check(mid, n, m) || check(mid, m, n))
			l = mid;
		else
			r = mid;
	}
	ans = l;
}

void write() {
	cout << ans << endl;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}