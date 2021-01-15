#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()
#define int ll
const int MAXN = 1e5 + 10;
const int MAXLOG = 20;

int n;
vector<int> g[MAXN];

int dp[MAXN][MAXLOG], tin[MAXN], tout[MAXN], h[MAXN], timer = 0;

void dfs(int v, int p) {
	tin[v] = timer++;
	dp[v][0] = p;
	for (int i = 1; i < MAXLOG; i++) {
		dp[v][i] = dp[dp[v][i - 1]][i - 1];
	}
	for (auto i : g[v]) {
		if (i == p) continue;
		h[i] = h[v] + 1;
		dfs(i, v);
	}
	tout[v] = timer++;
}

bool is_upper(int v, int u) {
	return tin[v] <= tin[u] && tout[v] >= tout[u];
}

int lca(int v, int u) {
	if (is_upper(v, u)) return v;
	if (is_upper(u, v)) return u;
	for (int i = MAXLOG - 1; i >= 0; i--) {
		if (!is_upper(dp[v][i], u)) {
			v = dp[v][i];
		}
	}
	return dp[v][0];
}

int dist(int v, int u) {
	return h[v] + h[u] - 2 * h[lca(v, u)];
}


struct fset{
	int tin, v;
	fset() {}
	fset(int _v, int _tin) {
		v = _v, tin = _tin;
	}
};

bool operator<(const fset & a, const fset & b) {
	return tie(a.tin, a.v) < tie(b.tin, b.v);
}

ll ans = 0;
set<fset> setik;

void add(int v) {
	if (v == 0) return;
	auto it = setik.lower_bound({-1, tin[v]});
	int nxt = 0;
	if (it != setik.end()) {
		nxt = it->v;
	}
	int pre = 0;
	if (it != setik.begin()) {
		--it;
		pre = it->v;
	}
	ans -= dist(nxt, pre);
	ans += dist(nxt, v);
	ans += dist(pre, v);
	setik.insert({v, tin[v]});
}

void del(int v) {
	if (v == 0) return;
	auto it = setik.lower_bound({v, tin[v]});
	int nxt = 0;
	++it;
	if (it != setik.end()) {
		nxt = it->v; 
	}
	--it;
	int pre = 0;
	if (it != setik.begin()) {
		--it;
		pre = it->v;
	}
	ans += dist(nxt, pre);
	ans -= dist(nxt, v);
	ans -= dist(pre, v);
	setik.erase({v, tin[v]});
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n;
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(0, 0);
	int q;
	cin >> q;
	while (q--) {
		int type;
		cin >> type;
		if (type == 1) {
			int v;
			cin >> v;
			v--;
			add(v);
		} else if (type == 2) {
			int v;
			cin >> v;
			v--;
			del(v);
		} else {
			cout << ans << "\n";
		}
	}
	return 0;
}