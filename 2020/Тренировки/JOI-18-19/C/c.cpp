#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 410;

int n;
int a[MAXN];
int pos[MAXN][3];
int cnt[MAXN][3];

void read() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		char x;
		cin >> x;
		if (x == 'R') a[i] = 0;
		else if (x == 'G') a[i] = 1;
		else a[i] = 2;
		for (int j = 0; j < 3; j++)
			cnt[i][j] = cnt[i - 1][j];
		cnt[i][a[i]]++;
		pos[cnt[i][a[i]]][a[i]] = i;
	}
}

const int INF = 1e9 + 10;
vector<vector<vector<vector<int>>>> dp;

void build() {
	dp.assign(cnt[n][0] + 1, vector<vector<vector<int>>> (cnt[n][1] + 1, vector<vector<int>> (cnt[n][2] + 1, vector<int> (3, INF))));
	dp[0][0][0][0] = dp[0][0][0][1] = dp[0][0][0][2] = 0;
}

void calc() {
	for (int i = 0; i <= cnt[n][0]; i++) {
		for (int j = 0; j <= cnt[n][1]; j++) {
			for (int k = 0; k <= cnt[n][2]; k++) {
				for (int ch = 0; ch < 3; ch++) {
					if (ch != 0 && i + 1 <= cnt[n][0]) {
						int p = pos[i + 1][0];
						chkmin(dp[i + 1][j][k][0], dp[i][j][k][ch] + max(0, cnt[p][1] - j) + max(0, cnt[p][2] - k));
					}
					if (ch != 1 && j + 1 <= cnt[n][1]) {
						int p = pos[j + 1][1];
						chkmin(dp[i][j + 1][k][1], dp[i][j][k][ch] + max(0, cnt[p][0] - i) + max(0, cnt[p][2] - k));
					}
					if (ch != 2 && k + 1 <= cnt[n][2]) {
						int p = pos[k + 1][2];
						chkmin(dp[i][j][k + 1][2], dp[i][j][k][ch] + max(0, cnt[p][0] - i) + max(0, cnt[p][1] - j));
					}
				}
			}
		}
	}
}

int ans;

void make_ans() {
	ans = INF;
	for (int i = 0; i < 3; i++) {
		chkmin(ans, dp[cnt[n][0]][cnt[n][1]][cnt[n][2]][i]);
	}
	if (ans == INF) ans = -1;
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