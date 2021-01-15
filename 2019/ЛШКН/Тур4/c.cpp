#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int INF = 1e9 + 10;
const int MAXN = 51;

struct event{
	int l, r, x, c;
};

int dp[MAXN][MAXN][MAXN];
int n, m, h;
vector<event> prob;
void read() {
	cin >> n >> h >> m;
	for (int i = 0; i < m; i++) {
		int l, r, x, c;
		cin >> l >> r >> x >> c;
		prob.push_back({l - 1, r - 1, x, c});
	}
}

bool cmp(event a, event b) {
	return a.x < b.x;
}

int ans;

void run() {
	sort(prob.begin(), prob.end(), cmp);

	for (int l = n - 1; l >= 0; l--) {
		for (int r = l; r < n; r++) {
			for (int max_h = 0; max_h <= h; max_h++) {
				dp[l][r][max_h] = -INF;
				for (int mid = l; mid <= r; mid++) {
					int sum = 0;
					for (int k = 0; k < m; k++) {
						if (prob[k].l <= mid && mid <= prob[k].r && prob[k].l >= l && prob[k].r <= r && prob[k].x < max_h) {
							sum += prob[k].c;
						} 
					}
					
					int fans = 0;
					if (mid - 1 >= l)
						fans += dp[l][mid - 1][max_h];
					if (mid + 1 <= r)
						fans += dp[mid + 1][r][max_h];
					chkmax(dp[l][r][max_h], fans + max_h * max_h - sum);
				}

				if (max_h) {
					chkmax(dp[l][r][max_h], dp[l][r][max_h - 1]);
				}
			}
		}
	}

	ans = dp[0][n - 1][h];
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