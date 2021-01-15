#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 2 * 1e4 + 10;
vector<int> g[MAXN];
map <pair <int, int> , int> ed;
set<int> ans;
int n, m;

void read() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		g[u].push_back(v);
		g[v].push_back(u);
		ed[{u, v}] = i + 1;
		ed[{v, u}] = i + 1;
	}
}

int tin[MAXN], up[MAXN], timer = 0;
bool used[MAXN];

void is_bridge(int u, int v) {
	ans.insert(ed[{u, v}]);
}

void dfs(int v, int p) {
	used[v] = true;
	tin[v] = up[v] = timer++;
	for (auto u : g[v]) {
		if (used[u]) {
			if (u != p)
				chkmin(up[v], tin[u]);
		}
		else {
			dfs(u, v);
			chkmin(up[v], up[u]);
			if (up[u] > tin[v]) {
				is_bridge(u, v);
			}
		}
	}
}

void run() {
	for (int i = 0; i < n; i++) {
		if (!used[i]) {
			dfs(i, -1);
		}
	}
}

void write() {
	cout << ans.size() << "\n";
	for (auto i : ans) {
		cout << i << "\n";
	}
}

signed main() {
	freopen("bridges.in", "r", stdin);
	freopen("bridges.out", "w", stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}