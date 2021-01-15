#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template<typename T1, typename T2>
inline void chkmin(T1 &x, const T2 &y) {
	if (x > y) x = y;
}

const int MAXN = 100, INF = 1e18;
int dp[MAXN][MAXN][MAXN];
int sum[MAXN][MAXN];

struct node{
	int key, prior, val;
	node() {
		key = prior = val = 0;
	}
};

bool operator<(node a, node b) {
	return a.key < b.key;
}

int n, k;
node a[MAXN];

void read() {
	cin >> n >> k;

	for (int i = 1; i <= n; i++)
		cin >> a[i].key;
	for (int i = 1; i <= n; i++)
		cin >> a[i].prior;
	for (int i = 1; i <= n; i++)
		cin >> a[i].val;
	sort(a + 1, a + n + 1);
	a[0].prior = INF;
}

void build() {
	for (int i = 1; i <= n; i++) {
		for (int j = i; j <= n; j++) {
			sum[i][j] = sum[i][j - 1] + a[j].val;
		}
	}

	for (int i = 1; i < MAXN; i++)
		for (int j = i + 1; j < MAXN; j++)
			for (int v = 0; v < MAXN; v++)
				dp[i][j][v] = INF;
}

void solve() {
	for (int l = n; l >= 1; l--) {
		for (int r = l + 1; r <= n + 1; r++) {
			for (int m = l; m < r; m++) {
				vector<int> left;
				vector<int> right;
				left.pb(0);
				right.pb(0);
				
				for (int i = l; i < m; i++) left.pb(i);
				for (int i = m + 1; i < r; i++) right.pb(i);

				for (auto v1 : left) {
					for (auto v2 : right) {
						if (a[m].prior < min(a[v1].prior, a[v2].prior))
							chkmin(dp[l][r][m], dp[l][m][v1] + dp[m + 1][r][v2] + sum[l][r - 1]);
			
						chkmin(dp[l][r][a[v1].prior < a[v2].prior ? v1 : v2], 
							dp[l][m][v1] + dp[m + 1][r][v2] + sum[l][r - 1] + k);
					}
				}
			}
		}
	}
}


int ans;
void run() {
	build();
	solve();
	ans = INF;
	for (int i = 0; i <= n; i++)
		ans = min(ans, dp[1][n + 1][i]);
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