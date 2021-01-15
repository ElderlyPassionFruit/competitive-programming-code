#include <bits/stdc++.h>

using namespace std;
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 17;
int g[MAXN][MAXN];
int dp[1 << MAXN][MAXN];
int par[1 << MAXN][MAXN];
int n;

const int INF = 1e9 + 10;

void read() {
	cin >> n;
	for (int i = 0; i < n; i++) 
		for (int j = 0; j < n; j++)
			cin >> g[i][j];
}

int fans;
vector<int> ans;

void run() {
	for (int i = 0; i < (1 << MAXN); i++)
		for (int j = 0; j < n; j++)
			dp[i][j] = INF;
	dp[1][0] = 0;

	for (int mask = 0; mask < (1 << MAXN); mask++) {
		for (int v = 0; v < n; v++) {
			if (!(mask & (1 << v))) 
				continue;
			for (int u = 0; u < n; u++) {
				int x = (1 << v);
				int y = (1 << u);
			 	if (!(((mask ^ x) & y)))
			 		continue;
				if (!g[u][v])
					continue;
				if (dp[mask][v] > dp[mask ^ (1 << v)][u] + g[u][v]) {
					dp[mask][v] = dp[mask ^ (1 << v)][u] + g[u][v];
					par[mask][v] = u;
				}
			}
		}
	}

	bool flag = false;
	for (int i = 0; i < n; i++) {
		flag |= dp[(1 << n) - 1][i] < INF;
	}
	if (!flag) {
		cout << -1 << endl;
		exit(0);
	}

	fans = INF;
	int v = -1;
	for (int i = 0; i < n; i++) {
		if (dp[(1 << n) - 1][i] < fans) {
			fans = dp[(1 << n) - 1][i];
			v = i;
		}
	}

	int mask = (1 << n) - 1;

	for (int i = 0; i < n; i++) {
		ans.push_back(v + 1);
		int new_mask = mask ^ (1 << v);
		v = par[mask][v];
		mask = new_mask;
	}
	reverse(ans.begin(), ans.end());
}

void write() {
	cout << fans << endl;
	for (auto i : ans) {
		cout << i << " ";
	}
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