#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct pt{
	int x, y;
	pt() {}
	pt(int _x, int _y) {
		x = _x, y = _y;
	}
};

const int MAXQ = 1e5 + 10;
const int MAX_ABC = 2e7 + 10;
const int MAXN = 151;

int n, m;
char table[MAXN][MAXN];
int q;
vector<pt> a[MAXQ], b[MAXQ], c[MAXQ];

int cntq = 0;
unsigned char qx[MAX_ABC], qy[MAX_ABC];
int qstart[MAXN][MAXN];
int qnext[MAX_ABC];

unsigned int dp[MAXN][MAXN];

unsigned int qans[MAX_ABC];
int ans[MAXQ];

void read() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> table[i][j];
		}
	}
	cin >> q;
	for (int i = 0; i < q; i++) {
		int n;
		cin >> n;
		a[i].resize(n);
		for (auto &j : a[i])
			cin >> j.x >> j.y;
		cin >> n;
		b[i].resize(n);
		for (auto &j : b[i])
			cin >> j.x >> j.y;
		cin >> n;
		c[i].resize(n);
		for (auto &j : c[i])
			cin >> j.x >> j.y;
	}
}

void add(pt a, pt b, int q) {
	qx[q] = b.x, qy[q] = b.y, qnext[q] = qstart[a.x][a.y], qstart[a.x][a.y] = q; 
}

void add_all(vector<pt> & a, vector<pt> & b) {
	for (auto i : a) {
		for (auto j : b) {
			add(i, j, cntq++);
		}
	}
}

void calc_dp(int x, int y) {
	for (int i = x; i <= n; i++) {
		for (int j = y; j <= m; j++) {
			dp[i][j] = 0;
			if (table[i][j] == '#') continue;
			if (i == x && j == y) { 
				dp[i][j] = 1; 
				continue;
			}
			if (i > x) dp[i][j] = dp[i][j] + dp[i - 1][j];
			if (j > y) dp[i][j] = dp[i][j] + dp[i][j - 1];
		}
	}
	
}

void solve(int x, int y) {
	calc_dp(x, y);
	for (int i = qstart[x][y]; i != -1; i = qnext[i]) {
		qans[i] = (qx[i] >= x && qy[i] >= y ? dp[qx[i]][qy[i]] : 0);
	}
}

void run() {
	for (int i = 0; i < MAXN; i++) for (int j = 0; j < MAXN; j++) qstart[i][j] = -1;
	
	for (int i = 0; i < q; i++) {
		add_all(a[i], c[i]);
		add_all(a[i], b[i]);
		add_all(b[i], c[i]);
	}

	for (int x = 1; x <= n; x++) {
		for (int y = 1; y <= m; y++) {
			solve(x, y);
		}
	}

	int cnt = 0;
	for (int it = 0; it < q; it++) {
		int sa = a[it].size(), sb = b[it].size(), sc = c[it].size();
		int fans = 0;
		for (int a = 0; a < sa; a++) {
			for (int c = 0; c < sc; c++) {
				int haveAC = qans[cnt + a * sc + c];
				if (!haveAC) continue;
				for (int b = 0; b < sb; b++) {
					int haveAB = qans[cnt + sa * sc + a * sb + b];
					int haveBC = qans[cnt + sa * sc + sa * sb + b * sc + c];
					fans += (int)(haveAC != haveAB * haveBC);
				}
			}
		}
	
		cnt += sa * sb + sa * sc + sb * sc;
		ans[it] = fans;
	}
}

void write() {
	for (int i = 0; i < q; i++) {
		cout << ans[i] << "\n";
	}
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