#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n, m;
int x1, Y1, x2, y2;

void read() {
	cin >> n >> m;
	x1 = -1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int x;
			cin >> x;
			if (x == 1) {
				if (x1 == -1)
					x1 = i, Y1 = j;
				else
					x2 = i, y2 = j;
			}
		}
	}
}

int ans;

void run() {
	ans = 0;
	if (x1 != x2) {
		chkmax(ans, m * (n - min(x1, x2) - 1));
		chkmax(ans, m * max(x1, x2));	
	}
	if (Y1 != y2) {
		chkmax(ans, n * (m - min(Y1, y2) - 1));
		chkmax(ans, n * max(Y1, y2));	
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