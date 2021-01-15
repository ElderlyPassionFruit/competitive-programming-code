#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 510;
int n, m;
int a[MAXN][MAXN];

void read() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> a[i][j];
		}
	}
}

int l, r, u, d;

string ans;

bool checkL() {
	if (l <= 0) return false;
	int now = (r - l + 1) * (d - u + 1) + 1;
	for (int i = u; i <= d; i++, now++) {
		if (a[i][l - 1] != now) return false;
	}
	return true;
}

bool checkR() {
	if (r >= m - 1) return false;
	int now = (r - l + 1) * (d - u + 1) + 1;
	for (int i = u; i <= d; i++, now++) {
		if (a[i][r + 1] != now) return false;
	}
	return true;
}

bool checkU() {
	if (u <= 0) return false;
	int now = (r - l + 1) * (d - u + 1) + 1;
	for (int i = l; i <= r; i++, now++) {
		if (a[u - 1][i] != now) return false;
	}
	return true;
}

bool checkD() {
	if (d >= n - 1) return false;
	int now = (r - l + 1) * (d - u + 1) + 1;
	for (int i = l; i <= r; i++, now++) {
		if (a[d + 1][i] != now) return false;
	}
	return true;
}

void run() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (a[i][j] != 1) continue;
			l = j, r = j;
			u = i, d = i;
		}
	}
	ans = "";
	while (l > 0 || r + 1 < m || u > 0 || d + 1 < n) {
		//cout << ans << endl;
		if (checkL()) ans += "L", l--;
		else if (checkR()) ans += "R", r++;
		else if (checkU()) ans += "U", u--;
		else if (checkD()) ans += "D", d++;
		else assert(false);
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