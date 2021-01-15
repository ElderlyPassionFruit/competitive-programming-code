#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const ld EPS = 1e-9;

int sign(ld x) {
	if (x > EPS) return 1;
	if (x < -EPS) return -1;
	return 0;
}

struct edge{
	int to, cap, flow;
	ld cost;
	edge() {}
	edge(int _to, int _cap, ld _cost) {
		to = _to, cap = _cap, cost = _cost, flow = 0;
	}
	int getCap() {
		return cap - flow;
	}
};

const int INF = 1e9;

struct MinCostMaxFlow{
	vector<vector<int>> g;
	vector<edge> Edges;
	int n;
	int s, t;
	
	void addEdge(int u, int v, int cap, ld cost) {
		assert(u < n && v < n);
		g[u].push_back(Edges.size());
		Edges.push_back({v, cap, cost});
		g[v].push_back(Edges.size());
		Edges.push_back({u, 0, -cost});
	}

	MinCostMaxFlow() {}
	MinCostMaxFlow(int _n, int _s, int _t) {
		n = _n, s = _s, t = _t;
		assert(s < n && t < n);
		g.assign(n, {});
		Edges = {};
	}

	vector<ld> dist;
	vector<int> p;
	queue<int> q;
	vector<bool> used;

	void FB() {
		dist.assign(n, INF);
		p.assign(n, -1);
		used.assign(n, false);
		q.push(s);
		dist[s] = 0;
		used[s] = true;
		while (!q.empty()) {
			int v = q.front();
			q.pop();
			//cout << "v = " << v << endl;
			used[v] = false;
			for (auto i : g[v]) {
				assert(i < Edges.size());
				if (Edges[i].getCap() < 1) continue;
				int to = Edges[i].to;
				ld cost = Edges[i].cost;
				if (sign(dist[to] - (dist[v] + cost)) <= 0) continue;
				dist[to] = dist[v] + cost;
				p[to] = i;
				if (!used[to]) {
					q.push(to);
					used[to] = true;
				}
			}
		}
	}

	void push() {
		FB();
		/*cout << "dist = " << endl;
		for (auto i : dist) {
			cout << i << " ";
		}
		cout << endl;*/
		assert(dist[t] != INF);
		//exit(0);
		int v = t;
		while (v != s) {
			Edges[p[v]].flow++;
			Edges[p[v] ^ 1].flow--;
			v = Edges[p[v] ^ 1].to;	
		}
	}

	ld getAns() {
		ld ans = 0;
		for (int i = 0; i < (int)Edges.size(); i += 2) {
			ans += Edges[i].flow * Edges[i].cost;
		}
		return ans;
	}
};

const int MAXN = 110;
int n;
int a[MAXN][MAXN];

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> a[i][j];
		}
	}
	MinCostMaxFlow solver(2 * n + 2, 2 * n, 2 * n + 1);
	for (int i = 0; i < n; i++) {
		solver.addEdge(solver.s, i, 1, 0);
		for (int j = 0; j < n; j++) {
			solver.addEdge(i, j + n, 1, -log(a[i][j]));
			//cout << log(a[i][j]) << " ";
		}
		//cout << endl;
		solver.addEdge(i + n, solver.t, 1, 0);
	}
	for (int i = 0; i < n; i++) {
		solver.push();
	}
	vector<int> ans(n);
	for (int i = 0; i < (int)solver.Edges.size(); i += 2) {
		if (solver.Edges[i].getCap() != 0) continue;
		if (solver.Edges[i].to == solver.t) continue;
		if (solver.Edges[i ^ 1].to == solver.s) continue;
		ans[solver.Edges[i ^ 1].to] = solver.Edges[i].to - n;
	}
	vector<int> fout(n);
	for (int i = 0; i < n; i++) {
		fout[ans[i]] = i;
	}
	for (auto i : fout) {
		cout << i + 1 << " ";
	}
	cout << endl;
	//cout << solver.getAns() << endl;
	return 0;
}