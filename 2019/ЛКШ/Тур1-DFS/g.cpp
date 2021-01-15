#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

void dfs_order(int v, vector<vector<int> > & g, vector<int> & used, vector<int> & tout, int & timer, vector<int> & order) {
	used[v] = true;
	for (auto i : g[v]) {
		if (!used[i]) {
			dfs_order(i, g, used, tout, timer, order);
		}
	}
	order.push_back(v);
	tout[v] = timer++;
}

void dfs_color(int v, vector<vector<int> > & gr, vector<int> & used, vector<int> & colors, int & color) {
	used[v] = true;
	colors[v] = color;
	for (auto i : gr[v]) {
		if (!used[i]) {
			dfs_color(i, gr, used, colors, color);
		}
	}
}

void add(int u, int v, vector<vector<int> > &g, vector<vector<int> > &gr, vector<pair <int, int> > & ed) {
	g[u].pb(v);
	gr[v].pb(u);
	ed.push_back({u, v});
}

signed main() {
	//freopen("2sat.in", "r", stdin);
	//freopen("2sat.out", "w", stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	while (cin >> n >> m) {
		vector<vector<int> > g(2 * n), gr(2 * n);
		vector<int> tout(2 * n), used(2 * n), colors(2 * n), order;
		vector<pair <int, int> > ed;
		for (int i = 0; i < m; i++) {
			int a, b, c, d;
			cin >> a >> b >> c >> d;
			if (b == 0 && d == 0) {
				add(a * 2 + 1, c * 2, g, gr, ed);
				add(c * 2 + 1, a * 2, g, gr, ed);
			}
			else if (b == 0 && d == 1) {
				add(a * 2 + 1, c * 2 + 1, g, gr, ed);
				add(c * 2, a * 2, g, gr, ed);
			}
			else if (b == 1 && d == 0) {
				add(a * 2, c * 2, g, gr, ed);
				add(c * 2 + 1, a * 2 + 1, g, gr, ed);
			}
			else {
				add(a * 2, c * 2 + 1, g, gr, ed);
				add(c * 2, a * 2 + 1, g, gr, ed);
			}
		}

		int timer = 0;
		for (int i = 0; i < 2 * n; i++) {
			if (!used[i]) {
				dfs_order(i, g, used, tout, timer, order);
			}
		}

		used.assign(2 * n, 0);
		int color = 0;
		reverse(order.begin(), order.end());
		
		for (auto i : order) {
			if (!used[i]) {
				dfs_color(i, gr, used, colors, color);
				color++;
			}
		}

		cout << "order = " << endl;
		for (auto i : order) 
			cout << i << " ";
		cout << endl;

		cout << "color = " << endl;
		for (int i = 0; i < n; i++) {
			cout << colors[i * 2] << " " << colors[i * 2 + 1] << endl; 
		}

		for (int i = 0; i < n; i++) {
			int v = colors[i * 2];
			int u = colors[i * 2 + 1];
			assert(v != u);
			if (u > v) {
				cout << "1";
			}
			else {
				cout << "0";
			}
		}
		cout << endl;
	}
	return 0;
}

/*
1 0

2 2
0 0 1 0
0 1 1 1

3 4
0 1 1 0
0 0 2 1
1 1 2 0
0 0 0 1

*/