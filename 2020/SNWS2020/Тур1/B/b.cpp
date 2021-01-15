#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int INF = 1e9;

const int MAXN = 510, MAXA = 26;
int n, m, k;
int dp[MAXN][MAXN];
char table[MAXN][MAXN];
int nxt[MAXN][MAXN][MAXA];
string s;

void read() {
	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> table[i][j];
		}
	}
	cin >> s;
}

void recalc(string & s, int pos, int it) {
	for (int i = 1; i <= n; i++) {
		chkmin(nxt[i][pos][s[n - it + i - 1] - 'a'], it); 
	}
}

void build() {
	for (int i = 0; i < MAXN; i++) {
		for (int j = 0; j < MAXN; j++) {
			dp[i][j] = 0;
		}
	}

	for (int i = 0; i < MAXN; i++) {
		for (int j = 0; j < MAXN; j++) {
			for (int k = 0; k < MAXA; k++) {
				nxt[i][j][k] = INF;
			}
		}
	}

	for (int j = 1; j <= m; j++) {
		string s = "";
		for (int i = 1; i <= n; i++) {
			s += table[i][j];
		}
		for (int i = 1; i <= n; i++) {
			s += table[i][j];
		}
		for (int i = 0; i < n; i++) {
			recalc(s, j, i);
		}
	}
}

void calc() {
	for (int len = 1; len <= k; len++) {	
		for (int i = n; i >= 1; i--) {
			for (int j = m; j >= 1; j--) {
				int x = nxt[i][j][s[len - 1] - 'a'];
				if (dp[i][j - 1] == INF || x == INF) dp[i][j] = INF;
				else dp[i][j] = dp[i][j - 1] + x;
			}
		}
		if (len == 1) {
			for (int i = 0; i < MAXN; i++) {
				for (int j = 0; j < MAXN; j++) {
					if (i == 0 || j == 0)
						dp[i][j] = INF;
				}
			}
		}
	}
}

int ans;
void make_ans() {
	ans = INF;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			chkmin(ans, dp[i][j]);
		}
	}
	if (ans == INF)
		ans = -1;
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