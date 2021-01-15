#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 2e5 + 10;
vector<int> g[MAXN];
set<int> ans;
int n, m;

void read() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		a--;
		b--;
		c--;
		g[n + i].push_back(a);
		g[n + i].push_back(b);
		g[n + i].push_back(c);
		g[a].push_back(n + i);
		g[b].push_back(n + i);
		g[c].push_back(n + i);
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
					if (v >= n)
						ans.insert(v - n + 1);
				}
			}
		}
	}
	if (v == root && cnt > 1) {
		if (v >= n)
			ans.insert(v - n + 1);
	}
}

void run() {
	root = 0;
	cnt = 0;
	dfs(0, -1);
}

void write() {
	cout << ans.size() << "\n";
	for (auto i : ans) {
		cout << i << " ";
	}
	cout << "\n";
}

signed main() {
	freopen("city.in", "r", stdin);
	freopen("city.out", "w", stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}

/*
3 1
1 2 3

3 2
1 2 3
3 2 1

5 4
1 2 3
2 4 3
1 2 4
3 5 1
*/