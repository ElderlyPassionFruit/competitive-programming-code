#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int a, b, c, x, k;

void read() {
	cin >> a >> b >> c >> x >> k;
}

int ans;

void run() {
	int cost = x / k;
	if (cost > b || cost < a) {
		ans = cost;
		return;
	}
	int l = a - 1, r = b + 1;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (((mid * (100 + c) + 99) / 100) * k <= x)
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