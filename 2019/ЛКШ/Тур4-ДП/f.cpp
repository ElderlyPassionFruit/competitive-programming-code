#include <bits/stdc++.h>

using namespace std;

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
const long long INF = 1e18;
const long long MAXN = 25e4 + 10;
const long long MAXC = 1e12 + 10;
vector<pair <long long, long long> > g[MAXN];
int n, k;

inline void read() {
	cin >> n >> k;
	assert(n < MAXN);
	for (int i = 1; i < n; i++) {
		long long u, v, c;
		cin >> u >> v >> c;
		assert(abs(c) <= 1e6);
		u--;
		v--;
		g[u].push_back({v, c});
		g[v].push_back({u, c});
	}
}

pair <long long, long long> dp[MAXN][2];

void dfs(long long v, long long p, long long x) {
	dp[v][0] = {0, 0};
	dp[v][1] = {-INF, 0};
	for (auto i : g[v]) {
		if (i.first != p) {
			dfs(i.first, v, x);
		}
	}

	for (auto i : g[v]) {
		if (i.first != p) {
			auto help = max(dp[i.first][0], dp[i.first][1]);
			dp[v][0].first += help.first;
			dp[v][0].second += help.second;
		}
	}

	for (auto i : g[v]) {
		if (i.first != p) {
			auto help = max(dp[i.first][0], dp[i.first][1]);
			chkmax(dp[v][1], make_pair((long long)dp[v][0].first - help.first + dp[i.first][0].first + i.second + x,
			 dp[v][0].second - help.second + dp[i.first][0].second + 1));
		}
	}
}

long long ans;

inline void run() {
	long long l = -MAXC, r = MAXC;
	while (l < r - 1) {
		long long mid = (l + r) / 2;
		dfs(0, 0, mid);
		auto help = max(dp[0][0], dp[0][1]);
		if (help.second >= k)
			r = mid;
		else
			l = mid;
	}
	
	dfs(0, 0, r);
	pair <long long, long long> help = max(dp[0][0], dp[0][1]);

	if (help.second < k) {
		cout << "Impossible" << endl;
		exit(0);
	}

	ans = help.first - (long long)k * r;
}

inline void write() {
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