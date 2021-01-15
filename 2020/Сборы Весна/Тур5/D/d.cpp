#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 70010, MAXA = 10;
const int INF = 1e9 + 228 + 1337;
string s;
int n;
int p[MAXN][MAXA], q[MAXN][MAXA][MAXA];
bool need[MAXN];
int cnt;

void read() {
	cin >> n >> s;
}

int ans;

void build() {
	ans = 0;
	reverse(all(s));
	while (!s.empty() && s.back() == 'e') {
		s.pop_back();
		ans++;
		n--;
	}
	if (s.empty()) {
		cout << ans << endl;
		exit(0);
	}
	reverse(all(s));
	for (auto i : s) {
		ans += 2 * (i == 'e');
	}
	string ns = "";
	ns += s[0];
	for (int i = 1; i < n; i++) {
		if (s[i] == 'e') continue;
		ns += s[i];
		if (s[i - 1] == 'e') {
			need[ns.size() - 1] = true;
		}
	}
	s = ns;
	n = s.size();

	for (int i = 0; i < MAXN; i++) {
		for (int j = 0; j < MAXA; j++) {
			p[i][j] = INF;
			for (int k = 0; k < MAXA; k++) {
				q[i][j][k] = INF;
			}
		}
	}
	for (int i = 0; i < MAXA; i++) {
		p[0][i] = 2;
	}
	p[0][s[0] - 'a'] = 0;
}

void calc() {
	for (int k = 1; k <= n; k++) {
		int last = s[k - 1] - 'a';
		for (int c = 0; c < MAXA; c++) {
			int & fupd = p[k][c];
			if (!need[k - 1] && c != last) {
				chkmin(fupd, p[k - 1][c]);
			}
			chkmin(fupd, p[k - 1][last] + 2);
			if (c != last) {
				chkmin(fupd, q[k - 1][last][c]);
			} 
			chkmin(fupd, q[k - 1][last][last] + 2);
		}
		if (k == n) break;
		for (int c = 0; c < MAXA; c++) {
			for (int d = 0; d < MAXA; d++) {
				int & fupd = q[k][c][d];
				if (c != last) {
					chkmin(fupd, p[k - 1][c] + 1 + 2);
				}
				chkmin(fupd, p[k - 1][last] + 1 + 2 + 2);
				if (c != last && d != last) {
					chkmin(fupd, q[k - 1][c][d] + 1);
				}
				if (d != last) {
					chkmin(fupd, q[k - 1][last][d] + 1 + 2);
				}
				if (c != last) {
					chkmin(fupd, q[k - 1][c][last] + 1 + 2);
				}
				chkmin(fupd, q[k - 1][last][last] + 1 + 2 + 2);
			}
		}
	}
}

void make_ans() {
	int fans = INF;
	for (int i = n; i <= n; i++) {
		for (int c = 0; c < MAXA; c++) {
			chkmin(fans, p[i][c] - 2);
		}
	}
	ans += fans;
}

void run() {
	build();
	calc();
	make_ans();
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