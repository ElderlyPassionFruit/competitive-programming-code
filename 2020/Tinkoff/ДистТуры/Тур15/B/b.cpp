#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct ed{
	int u, v, cost;
	ed() {}
	ed(int _u, int _v, int _cost) {
		u = _u, v = _v;
		cost = _cost;
	}
};

int n, m;
const int MAXN = 1e5 + 10;
vector<ed> have;

void read() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int u, v, cost;
		cin >> u >> v >> cost;
		have.push_back({u, v, cost});
	}
}

set<pair<int, int>> bridges;

int tin[MAXN], up[MAXN];
bool used[MAXN];

int timer = 0;

vector<pair<int, int> > g[MAXN];

void dfs_bridges(int v, int p) {
	used[v] = true;
	tin[v] = up[v] = timer++;
	for (auto [to, cost] : g[v]) {
		if (to == p) continue;
		if (used[to]) 
			chkmin(up[v], tin[to]);
		else {
			dfs_bridges(to, v);
			chkmin(up[v], up[to]);
			if (up[to] > tin[v]) {
				bridges.insert({min(v, to), max(v, to)});
			}
		}
	}
}

void build() {
	dfs_bridges()
}

int ans;

void add(ed have) {
	build();

}

void run() {
	sort(all(have), [&] (ed a, ed b) {return a.cost > b.cost;});
	ans = 0;
	for (int i = 0; i < m; i++) {
		add(have[i]);
	}
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