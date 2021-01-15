#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int l, x, d, m;

void read() {
	cin >> l >> x >> d >> m;
}

int ans;

void run() {
	int dx = d - (d - (m - 1) * x);
	//cout << "dx = " << dx << endl;
	if (dx <= 0) {
		ans = -1;
		return;
	}
	ans = (d + dx - 1) / dx + 1;
}

void write() {
	cout << ans;
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