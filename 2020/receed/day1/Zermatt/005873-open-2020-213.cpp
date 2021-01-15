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
vector<int> g[N], c1[2][N], s1[N][2], gg[N];
vector<pair<int, int>> ng[N], lp[N];
vector<vector<int>> ps[N][2];
int up[L][N], h[N], sm[N], c[N], ans[N], mn, mx, md, dp[N], cn[N], cnum, nz[N], ca[N], ba[N], dir[N];

void dfs(int v, int p) {
	rep(i, g[v].size())
		if (g[v][i] == p) {
			swap(g[v][i], g[v].back());
			g[v].pop_back();
			break;
		}
	for (int u : g[v]) {
		up[0][u] = v;
		h[u] = h[v] + 1;
		dfs(u, v);
	}
}

void dfs2(int v, int p) {
	for (int u : g[v]) {
		dfs2(u, v);
		sm[v] += sm[u];
	}
	if (sm[v]) {
		//cout << v << ' ' << p << " 0" << endl;
		nz[v] = 1;
		ng[v].push_back({p, 0});
		ng[p].push_back({v, 0});
	}
}
void lca(int u, int v) {
	if (h[u] < h[v])
		swap(u, v);
	for (int i = L - 1; i >= 0; i--)
		if (h[up[i][u]] > h[v])
			u = up[i][u];
	if (up[0][u] == v) {
		nz[u] = 1;
		sm[u]--;
		sm[v]--;
		return;
	}
	if (h[u] > h[v])
		u = up[0][u];
	for (int i = L - 1; i >= 0; i--)
		if (up[i][u] != up[i][v]) {
			u = up[i][u];
			v = up[i][v];
		}
	ng[u].push_back({v, 1});
	ng[v].push_back({u, 1});
	lp[up[0][u]].push_back({u, v});
	sm[u]--;
	sm[v]--;
	nz[u] = nz[v] = 1;
}

void dfs3(int v, int cc) {
	c[v] = cc;
	cn[v] = cnum;
	for (auto &pp : ng[v]) {
		if (c[pp.first] == -1)
			dfs3(pp.first, cc ^ pp.second);
		else if (c[pp.first] != cc ^ pp.second) {
			cout << -1;
			exit(0);
		}
	}
}

int dfs4(int v, int p) {
	int m1 = 0, m2 = 0, mr = 0, ml = 0;
	for (int u : g[v]) {
		ca[u] = 0;
		if (dfs4(u, v))
			return 1;
		if (cn[u] == cn[v]) {
			if (c[u] == c[v])
				mr = max(mr, 1 + dp[u]);
			else
				ml = max(ml, 1 + dp[u]);
		}
	}
	rep(i, ps[v][0].size()) {
		s1[v][0][i] = s1[v][1][i] = 0;
		rep(z, 2)
			for (int j : ps[v][z][i])
				s1[v][z][i] = max(s1[v][z][i], dp[j] + 1);
		if (s1[v][0][i] > s1[v][1][i]) {
			swap(s1[v][0][i], s1[v][1][i]);
			swap(ps[v][0][i], ps[v][1][i]);
		}
		//cout << md << ' ' << v << ' ' << s1[v][0][i] << ' ' << s1[v][1][i] << '\n';
		//for (int j : ps[v][1][i])
		//		ca[j] = 1;
		m1 = max(m1, s1[v][0][i]);
		m2 = max(m2, s1[v][1][i]);
	}
	if (max(mr, m1) + max(ml, m2) > md) {
		if (max(mr, m2) + max(ml, m1) > md)
			return 1;
		swap(m1, m2);
		rep(i, ps[v][0].size())
			swap(ps[v][0][i], ps[v][1][i]);
	}
	rep(i, ps[v][1].size())
		for (int j : ps[v][1][i])
			ca[j] = 1;
	dp[v] = max(mr, m1);
	return 0;
}

void dfs5(int v, int p) {
	for (int u : g[v]) {
		dir[u] = dir[v] ^ ba[u];
		if (nz[u]) {
			if (dir[u])
				gg[u].push_back(v);
			else
				gg[v].push_back(u);
		}
		dfs5(u, v);
	}
}

void dfs6(int v) {
	ans[v] = 1;
	for (int u : gg[v]) {
		if (!ans[u])
			dfs6(u);
		ans[v] = max(ans[v], ans[u] + 1);
	}
}

int main() {
#ifdef ONPC
	freopen("a.in", "r", stdin);
#endif
	ios_base::sync_with_stdio(0); cin.tie(0);
	int m, t, u, v;
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
		lca(u, v);
		sm[u]++;
		sm[v]++;
	}
	dfs2(0, 0);
	rep(i, n)
		c[i] = -1;
	rep(i, n)
		if (c[i] == -1) {
			cnum++;
			dfs3(i, 0);
		}
	//rep(i, n)
//		cout << c[i] << ' ' << cn[i] << ' ' << nz[i] << "!\n";
	rep(i, n) {
		for (int j : g[i]) {
			if (!nz[j] || cn[j] == cn[i])
				continue;
			//cout << i << ' ' << j << '\n';
			c1[c[j] ^ c[i]][cn[j]].push_back(j);
		}
		for (int j : g[i]) {
			if (!nz[j] || cn[j] == cn[i])
				continue;
			if (!c1[0][cn[j]].empty() || !c1[1][cn[j]].empty())
				rep(z, 2)
					ps[i][z].push_back(c1[z][cn[j]]);
			rep(z, 2)
				c1[z][cn[j]].clear();
		}
		s1[i][0].resize(ps[i][0].size());
		s1[i][1].resize(ps[i][0].size());
	}
	int l = -1, r = n + 1;
	while (r - l > 1) {
		md = (l + r) / 2;
		if (dfs4(0, 0))
			l = md;
		else {
			r = md;
			rep(i, n)
				ba[i] = ca[i];
		}
	}
	if (l == n) {
		cout << -1;
		return 0;
	}
	dfs5(0, 0);
	rep(i, n)
		if (!ans[i])
			dfs6(i);
	cout << r + 1 << '\n';
	rep(i, n)
		cout << ans[i] << ' ';
}

