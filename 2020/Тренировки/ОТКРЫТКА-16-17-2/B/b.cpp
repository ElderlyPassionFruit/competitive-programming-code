#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n, x, y;
string s;

void read() {
	cin >> n >> s >> x >> y;
}

int ans[4];

void no() {
	cout << "-1" << endl;
	exit(0);
}

void run() {
	for (int i = 0; i < 4; i++)
		ans[i] = n;
	if (x >= 0) {
		ans[0] = 0;
		for (int i = 0; i < n; i++) {
			if (x == 0) {
				ans[2] = i;
				break;
			}
			if (s[i] == 'R') x--;
		}
	}
	else {
		ans[2] = 0;
		for (int i = 0; i < n; i++) {
			if (x == 0) {
				ans[0] = i;
				break;
			}
			if (s[i] == 'L') x++;
		}
	}
	if (y >= 0) {
		ans[3] = 0;
		for (int i = 0; i < n; i++) {
			if (y == 0) {
				ans[1] = i;
				break;
			}
			if (s[i] == 'U') y--;
		}
	}
	else {
		ans[1] = 0;
		for (int i = 0; i < n; i++) {
			if (y == 0) {
				ans[3] = i;
				break;
			}
			if (s[i] == 'D') y++;
		}
	}
	if (x != 0 || y != 0) no();
}

void write() {
	for (int i = 0; i < 4; i++)
		cout << ans[i] << " ";
	cout << endl;
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