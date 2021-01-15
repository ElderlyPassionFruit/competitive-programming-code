#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
#define int ll
const int MAXN = 2e5 + 10;
int n;
int c[MAXN][2];

ll ans;

void make(int & a, int l, int r) {
	if (a < l) ans += l - a, a = l;
	if (a > r) ans += a - r, a = r;
}

void read() {
	cin >> n;
	for (int i = 0; i < 2 * n; i++) {
		int x, y;
		cin >> x >> y;
		make(x, 1, n);
		make(y, 1, 2);
		x--;
		y--;
		c[x][y]++;
	}
}

void run() {
	for (int i = 0; i < n; i++) {
		int t0 = c[i][0];
		int t1 = c[i][1];
		t0--;
		t1--;
		if (t0 * t1 < 0) {
			int t = min(abs(t0), abs(t1));
			if (t0 < 0) t0 += t, t1 -= t;
			else t0 -= t, t1 += t;
			ans += t;
		}
		ans += abs(t0) + abs(t1);	
		c[i + 1][0] += t0;
		c[i + 1][1] += t1;
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