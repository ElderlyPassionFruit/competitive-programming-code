#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <cassert>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <bitset>
#include <ext/pb_ds/assoc_container.hpp>
#define rep(i, n) for (int i = 0; i < (n); i++)
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()

using ll = long long;
using ld = long double;
using ul = unsigned long long;
using namespace std;
using namespace __gnu_pbds;

const int N = 500001, L = 19;
int n;
vector<int> g[N];
vector<pair<int, int>> ng[N];
int up[L][N], h[N], sm[N], c[N], ans[N], mn, mx;

void dfs(int v, int p) {
	for (int u : g[v]) {
		if (u == p)
			continue;
		up[0][u] = v;
		h[u] = h[v] + 1;
		dfs(u, v);
	}
}

void dfs2(int v, int p) {
	for (int u : g[v]) {
		if (u == p)
			continue;
		dfs2(u, v);
		sm[v] += sm[u];
	}
	if (sm[v]) {
		//cout << v << ' ' << p << " 0" << endl;
		ng[v].push_back({p, 0});
		ng[p].push_back({v, 0});
	}
}

void dfs3(int v, int cc) {
	c[v] = cc;
	for (auto &pp : ng[v]) {
		if (c[pp.first] == -1)
			dfs3(pp.first, cc ^ pp.second);
		else if (c[pp.first] != cc ^ pp.second) {
			if (n > 10)
				assert(false);
			cout << -1;
			exit(0);
		}
	}
}

void dfs4(int v, int p) {
	mn = min(mn, ans[v]);
	mx = max(mx, ans[v]);
	for (int u : g[v]) {
		if (u == p)
			continue;
		ans[u] = ans[v] + c[u] * 2 - 1;
		dfs4(u, v);
	}
}
int lca(int u, int v) {
	if (h[u] < h[v])
		swap(u, v);
	for (int i = L - 1; i >= 0; i--)
		if (h[up[i][u]] >= h[v])
			u = up[i][u];
	if (u == v) {
		sm[u] -= 2;
		return u;
	}
	for (int i = L - 1; i >= 0; i--)
		if (up[i][u] != up[i][v]) {
			u = up[i][u];
			v = up[i][v];
		}
	assert(u != v);
	ng[u].push_back({v, 1});
	ng[v].push_back({u, 1});
	//cout << u << ' ' << v << " 1\n";
	sm[u]--;
	sm[v]--;
	assert(up[0][u] == up[0][v]);
	return up[0][u];
}

int main() {
#ifdef ONPC
	freopen("a.in", "r", stdin);
#endif
	ios_base::sync_with_stdio(0); cin.tie(0);
	int m, t, u, v, l;
	cin >> n >> m >> t;
	rep(i, n - 1) {
		cin >> u >> v;
		u--; v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(0, 0);
	rep(i, L - 1)
		rep(j, n)
			up[i + 1][j] = up[i][up[i][j]];
	rep(i, m) {
		cin >> u >> v;
		u--; v--;
		l = lca(u, v);
		sm[u]++;
		sm[v]++;
	}
	dfs2(0, 0);
	rep(i, n)
		c[i] = -1;
	rep(i, n)
		if (c[i] == -1)
			dfs3(i, 0);
	dfs4(0, 0);
	cout << mx - mn + 1 << '\n';
	rep(i, n)
		cout << ans[i] - mn + 1 << ' ';
}

