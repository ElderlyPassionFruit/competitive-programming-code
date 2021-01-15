#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int a, b, c;

void read() {
	cin >> a >> b >> c;
}

int ans;
void run() {
	ans = 0;
	int have = c / a;
	for (int i = 0; i <= have; i++) {
		int cnt_b = (c - i * a) / b;
		if (cnt_b < 0)
			continue;
		if (i + cnt_b == have) {
			if (i * a + cnt_b * b <= c) {
				chkmax(ans, i * a + cnt_b * b);
			}
		}
	}
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