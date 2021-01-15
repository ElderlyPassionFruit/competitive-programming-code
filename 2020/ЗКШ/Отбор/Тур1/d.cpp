#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct edge{
	int v, cap, flow, price;
	edge() {}
	edge(int a, int b, int c) {
		v = a, cap = b, flow = 0, price = c;
	}
};

const int INF = 1e9 + 7;

struct min_cost_max_flow{
	vector<edge> Ed;
	vector<vector<int>> g;
	int s, t;
	int n;
	int cost;

	min_cost_max_flow() {}
	min_cost_max_flow(int sz, int S, int T) {
		n = sz;
		s = S;
		t = T;
		g.resize(n);
		cost = 0;
	}
	void add_edge(int u, int v, int cap, int price) {
		g[u].push_back(Ed.size());
		Ed.push_back({v, cap, price});
		g[v].push_back(Ed.size());
		Ed.push_back({u, 0, -price});
	}

	vector<int> dist;
	vector<int> p;
	vector<bool> used;

	void FB() {
		dist.assign(n, INF);
		p.assign(n, -1);
		used.assign(n, false);
		queue<int> q;
		q.push(s);
		dist[s] = 0;
		used[s] = true;
		while (!q.empty()) {
			int v = q.front();
			used[v] = false;
			q.pop();
			for (auto i : g[v]) {
				if (Ed[i].cap - Ed[i].flow < 1) continue; 
				int u = Ed[i].v;
				if (dist[u] > dist[v] + Ed[i].price) {
					dist[u] = dist[v] + Ed[i].price;
					p[u] = i;
					if (!used[u])
						q.push(u);
					used[u] = true;
				}
			}
		}
	}

	void push() {
		FB();
		if (dist[t] == INF) return;
		int v = t;
		while (v != s) {
			int ind = p[v];
			Ed[ind].flow++;
			Ed[ind ^ 1].flow--;
			v = Ed[ind ^ 1].v;
		}
	}

	int get_min_cost(int k) {
		for (int i = 0; i < k; i++)
			push();
		int ans = 0;
		for (int i = 0; i < Ed.size(); i += 2) {
			ans += Ed[i].price * Ed[i].flow;
		}
		return ans;
	}
};

const int MAXN = 10;

int n, m, k;
int table[MAXN][MAXN];

void read() {
	cin >> n >> m >> k;
	k = min(k, 100);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			char x;
			cin >> x;
			table[i][j] = x - '0';
		}
	}
}

int ans;

int get_ind(int i, int j) {
	return i * m + j;
}

void run() {
	int s = 2 * n * m, t = 2 * n * m + 1;
	min_cost_max_flow flow_graph(2 * n * m + 2, s, t);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int ind = get_ind(i, j);
			flow_graph.add_edge(ind, ind + n * m, INF, 0);
			for (int k = 1; k <= table[i][j]; k++)
				flow_graph.add_edge(ind, ind + n * m, 1, -k);
			if (i + 1 < n) {
				int nxt = get_ind(i + 1, j);
				flow_graph.add_edge(ind + n * m, nxt, INF, 0);
			}	
			if (j + 1 < m) {
				int nxt = get_ind(i, j + 1);
				flow_graph.add_edge(ind + n * m, nxt, INF, 0);
			}
		}
	}
	flow_graph.add_edge(s, 0, INF, 0);
	flow_graph.add_edge(2 * n * m - 1, t, INF, 0);
	ans = flow_graph.get_min_cost(k);
}

void write() {
	cout << abs(ans) << endl;
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