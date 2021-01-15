#include <bits/stdc++.h>
 
using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()
 
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
 
const int MAXN = 2e5 + 10;
vector<int> g[MAXN];
int n, m, s;
int w[MAXN];
 
void read() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		cin >> w[i];
	}
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	cin >> s;
	s--;
}
 
int tin[MAXN], up[MAXN], timer = 0;
bool used[MAXN];
 
set <pair <int, int> > bridges;
 
void add(int u, int v) {
	if (u > v) swap(u, v);
	bridges.insert({u, v});
}
 
void dfs_bridges(int v, int p) {
	tin[v] = up[v] = timer++;
	used[v] = true;
	for (auto i : g[v]) {
		if (i == p) continue;
		if (used[i]) {
			chkmin(up[v], tin[i]);
		}
		else {
			dfs_bridges(i, v);
			chkmin(up[v], up[i]);
			if (tin[v] < up[i]) {
				add(v, i);
			}
		}
	}
}
 
bool check(int u, int v) {
	if (u > v) swap(u, v);
	return bridges.find(make_pair(u, v)) == bridges.end();
}
 
int color[MAXN];
int sz[MAXN];
 
void dfs_color(int v, int c) {
	used[v] = true;
	color[v] = c;
	sz[c]++;
	for (auto i : g[v]) {
		if (!used[i] && check(i, v)) {
			dfs_color(i, c);
		}
	}
}
 
set<int> g1[MAXN];
int w2[MAXN];


void build() {
	dfs_bridges(0, 0);
	for (int i = 0; i < n; i++)
		used[i] = false;
	int c = 0;
	for (int i = 0; i < n; i++) {
		if (!used[i]) {
			dfs_color(i, c++);
		}
	}
 
	for (auto i : bridges) {
		int u = color[i.first];
		int v = color[i.second];
		if (u != v) {
			g1[u].insert(v);
			g1[v].insert(u);
		}
	}
 
	
 	for (int i = 0; i < n; i++)
 		w2[color[i]] += w[i];
	s = color[s];
	//cout << "puhh" << endl;
}

int ans;
 
int dfs1(int v, int p) {
	int ans1 = 0;
	for (auto i : g1[v]) {
		if (i != p) {
			int x = dfs1(i, v);
			if (ans1 < x) ans1 = x;
		}
	}
	return ans1 + w2[v];
}

pair <int, bool> dfs2(int v, int p) {
	pair <int, bool> ans = {0, 0};
	for (auto i : g1[v]) {
		if (i != p) {
			auto fans = dfs2(i, v);
			if (fans.second) {
				ans.second = true;
				ans.first += fans.first;
			}
		}
	}
	if (sz[v] > 1 || ans.second == true) ans.first += w2[v], ans.second = true;
	
	return ans;
}
 
void solve() {
	ans = 0;
	for (int i = 0; i < MAXN; i++)
		used[i] = false;
	int fans = 0;
	for (auto i : g1[s]) {
		auto x = dfs2(i, s);
		if (x.second) ans += x.first, chkmax(fans, dfs1(i, s) - x.first);
		else chkmax(fans, dfs1(i, s));	
	}
	ans += fans;
	ans += w2[s];
}
 
void run() {
	build();
	solve();
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