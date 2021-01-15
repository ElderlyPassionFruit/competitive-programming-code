#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}
#define int ll
struct Edge{
	int to, len;
};

const int N = 2e5 + 10;
int n, m, k;
int a[N];
vector<Edge> g[N];

void read() {
	cin >> n >> m >> k;
	for (int i = 0; i < k; i++) {
		cin >> a[i];
		a[i]--;
	}
	for (int i = 0; i < m; i++) {
		int u, v, len;
		cin >> u >> v >> len;
		u--;
		v--;
		g[u].push_back({v, len});
		g[v].push_back({u, len});
	}
}

void no() {
	cout << -1 << endl;
	exit(0);
}

const int INF = 1e18;
int minT[N];
set<pair<int, int>> q;

void relaxT(int v, int t) {
	if (minT[v] <= t) return;
	q.erase({minT[v], v});
	minT[v] = t;
	q.insert({minT[v], v});
}

void build() {
	fill(minT, minT + N, INF);
	for (int i = 0; i < k; i++) {
		relaxT(a[i], 0);
	}
	while (!q.empty()) {
		int v = q.begin()->second;
		q.erase(q.begin());
		for (auto i : g[v]) {
			relaxT(i.to, i.len + minT[v]);
		}
	}
}

int dp[N];

void relaxDp(int v, int t) {
	if (dp[v] <= t || minT[v] <= t) return;
	q.erase({dp[v], v});
	dp[v] = t;
	q.insert({dp[v], v});
}

int ans;

void djkstra() {
	int s, f;
	cin >> s >> f;
	s--;
	f--;
	fill(dp, dp + N, INF);
	relaxDp(s, 0);
	while (!q.empty()) {
		int v = q.begin()->second;
		q.erase(q.begin());
		for (auto i : g[v]) {
			relaxDp(i.to, i.len + dp[v]);
		}
	}
	if (dp[f] == INF) no();
	ans = dp[f];
}

void run() {
	build();
	djkstra();
}

void write() {
	cout << ans << endl;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
	read();
	run();
	write();
	return 0;
}