#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

int n, m;

void read() {
	cin >> n >> m;
}

const int N = 1100;
char ans[N][N];

void paint(int & x, int & y, int len, char t) {
	if (!len) return;
	ans[x][y] = t;
	if (x & 1) {
		if (y == 0) {
			x++;
		} else {
			y--;
		}
	} else {
		if (y == m - 1) {
			x++;
		} else {
			y++;
		}
	}
	len--;
	paint(x, y, len, t);
}

vector<int> have;

void run() {
	int sum = 0;
	int now = 0;
	while (sum + now + 1 <= n * m) {
		now++;
		have.push_back(now);
		sum += now;
	}
	assert(sum <= n * m);
	have[have.size() - 1] += n * m - sum;
	int x = 0, y = 0;
	char last = 'B';
	char lastZ = 'T';
	char lastX = 'Y';
	for (auto len : have) {
		int haveLen = 0;
		if (x & 1) {
			haveLen = y + 1;
		} else {
			haveLen = m - y;
		}
		if (len <= haveLen) {
			if (x & 1) {
				if (last != 'C') {
					last = 'C';
				} else {
					last = 'D';
				}
				paint(x, y, len, last);
			} else {
				if (last != 'A') {
					last = 'A';
				} else {
					last = 'B';
				}
				paint(x, y, len, last);
			}
		} else {
			if (x & 1) {
				if (lastZ != 'Z') {
					lastZ = 'Z';
				} else {
					lastZ = 'T';
				}
				last = lastZ;
			} else {
				if (lastX != 'X') {
					lastX = 'X';
				} else {
					lastX = 'Y';
				}
				last = lastX;
			}
			paint(x, y, len, last);
		}
	}
}

void write() {
	cout << have.size() << "\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << ans[i][j];
		}
		cout << "\n";
	}
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
	read();
	run();
	write();
	return 0;
}