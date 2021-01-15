#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 210;
int dp[MAXN][MAXN][MAXN][2];

int n, len;
int x[MAXN];
int t[MAXN];

void read() {
	cin >> n >> len;
	for (int i = 1; i <= n; i++)
		cin >> x[i];
	for (int i = 1; i <= n; i++)
		cin >> t[i];
}

const int INF = 1e9 + 10;

void build() {
	for (int l = 0; l <= n; l++) {
		for (int r = 0; r <= n; r++) {
			for (int cnt = 0; cnt <= n; cnt++) {
				for (int flag = 0; flag <= 1; flag++) {
					dp[l][r][cnt][flag] = INF;
				}
			}
		}
	}
	dp[0][0][0][0] = dp[0][0][0][1] = 0;
}

int dist(int l, int r, int now, int nxt) {
	int pos_now = (now == 0 ? x[l] : x[n - r + 1]);
	int pos_nxt = (nxt == 0 ? x[l + 1] : x[n - r]);
	int ans = abs(pos_now - pos_nxt);
	chkmin(ans, len - ans);
	return ans;
}

int get_time(int l, int r, int nxt) {
	int ans = (nxt == 0 ? t[l + 1] : t[n - r]);
	return ans;	
}

void calc() {
	for (int l = 0; l <= n; l++) {
		for (int r = 0; r + l + 1 <= n; r++) {
			for (int cnt = 0; cnt <= n; cnt++) {
				for (int flag = 0; flag <= 1; flag++) {
					if (dp[l][r][cnt][flag] == INF) continue;
					if (cnt == n) continue;

					int val = dp[l][r][cnt][flag];

					for (int add = 0; add <= 1; add++) {
						for (int nxt = 0; nxt <= 1; nxt++) {
							int d = dist(l, r, flag, nxt);
							int t = get_time(l, r, nxt);
							if (t < d + val && add) continue;
							chkmin(dp[l + (nxt == 0)][r + (nxt == 1)][cnt + add][nxt], d + val);
						}
					}
				}
			}
		}
	}
}

int ans;

void make_ans() {
	ans = 0;
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= n; j++)
			for (int k = 0; k <= n; k++)
				for (int l = 0; l < 2; l++)
					if (dp[i][j][k][l] != INF)
						chkmax(ans, k);
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