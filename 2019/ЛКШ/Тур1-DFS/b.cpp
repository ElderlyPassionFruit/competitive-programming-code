#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 2 * 1e4 + 10;
vector<int> g[MAXN];
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
	}
}

int tin[MAXN], up[MAXN], timer = 0;
int root, cnt;
bool used[MAXN];

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
			if (v == root) {
				cnt++;
			}
			chkmin(up[v], up[u]);
			if (v != root) {
				if (up[u] >= tin[v]) {
					ans.insert(v);
				}
			}
		}
	}
	if (v == root && cnt > 1) {
		ans.insert(v);
	}
}

void run() {
	for (int i = 0; i < n; i++) {
		if (!used[i]) {
			root = i;
			cnt = 0;
			dfs(i, -1);
		}
	}
}

void write() {
	cout << ans.size() << "\n";
	for (auto i : ans) {
		cout << i + 1 << " ";
	}
	cout << "\n";
}

signed main() {
	freopen("points.in", "r", stdin);
	freopen("points.out", "w", stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}

/*
6 7
1 2
2 3
2 4
2 5
4 5
1 3
3 6


*/