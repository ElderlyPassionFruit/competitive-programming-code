#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct edge{
	int a, b, c, d, w;
	edge() {}
	edge(int x, int y, int z, int t, int u) {
		a = x, b = y, c = z, d = t, w = u;
	}
};

int n, m;
vector<edge> a;

void read() {
	cin >> n >> m;
	a.resize(m);
	for (auto &i : a) {
		cin >> i.a >> i.b >> i.c >> i.d >> i.w;
		i.a--;
		i.b--;
		i.c--;
		i.d--;
	}
}

const int INF = -1e18;

bool dfs(int v, int p, vector<vector<int> > & g, vector<bool> & used) {
	used[v] = true;
	for (auto i : g[v]) {
		if (i == p) continue;
		if (used[i]) return true;
		if(dfs(i, v, g, used)) return true;
	}
	return false;
}

int check(vector<int> help) {
	vector<vector<int>> g(n + n);
	int ans = 0;
	for (int i = 0; i < m; i++) {
		if (help[i] == 1) {
			ans += a[i].w;
			g[a[i].a].push_back(a[i].b);
			g[a[i].b].push_back(a[i].a);
			g[a[i].c + n].push_back(a[i].d + n);
			g[a[i].d + n].push_back(a[i].c + n);
		}
	}

	for (int i = 0; i < 2 * n; i++) {
		int x = g[i].size();
		sort(all(g[i]));
		g[i].resize(unique(all(g[i])) - g[i].begin());
		if (x != g[i].size()) return INF;
	}

	vector<bool> used(2 * n, 0);
	for (int i = 0; i < 2 * n; i++) {
		if (!used[i]) {
			if (dfs(i, i, g, used)) {
				return INF;
			}
		}
	}
	return ans;
}

int solve(int x) {
	vector<int> help(m);
	for (int i = 0; i < x; i++)
		help[m - 1 - i] = 1;
	int ans = INF;
	do {
		chkmax(ans, check(help));
	} while (next_permutation(all(help)));
	return ans;
}

vector<int> ans;

void run() {
	for (int i = 1; i <= m; i++) {
		ans.push_back(solve(i));
	}
}

void write() {
	for (auto i : ans)
		if (i == INF)
			cout << "Impossible" << "\n";
		else
			cout << i << "\n";
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