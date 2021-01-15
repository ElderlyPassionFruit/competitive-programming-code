//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,avx,avx2")
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

struct edge{
	int to, cap, flow, cost;
	edge() {}
	edge(int _to, int _cap, int _cost) {
		to = _to, cap = _cap, cost = _cost;
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
	
	void addEdge(int u, int v, int cap, int cost) {
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

	vector<int> dist;
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
				int cost = Edges[i].cost;
				if (dist[to] <= dist[v] + cost) continue;
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

	int getAns() {
		int ans = 0;
		for (int i = 0; i < (int)Edges.size(); i += 2) {
			ans += Edges[i].flow * Edges[i].cost;
		}
		return ans;
	}
};

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int n;
	cin >> n;
	vector<int> a(n);
	for (auto &i : a) {
		cin >> i;
	}
	MinCostMaxFlow solver = MinCostMaxFlow(6*n+229, 0, 6 * n + 228);
	for (int i = 0; i < n; i++) {
		solver.addEdge(solver.s, i + 1, 5, 0);
		solver.addEdge(i + 1, i+ n + 1,1,-1);
		solver.addEdge(solver.s, i +2*n + 1,5,0);
		solver.addEdge(solver.s,i +3*n + 1,5,0);
		solver.addEdge(i+2*n+1, solver.t,5,0);
		solver.addEdge(i+3*n+1, solver.t,5,0);
		solver.addEdge(i+2*n+1, i+1,228,0);
		solver.addEdge(i+3*n+1,i+1,228,0);
//		solver.addEdge(i+n+1,i+2*n+1,228,0);
//		solver.addEdge(i+n+1,i+3*n+1, 228,0);
		solver.addEdge(i + n + 1, solver.t, 5, 0);
	}
	vector<int> poses(1e5+337, -1);
	vector<int> posrem(8, -1);
	for(int i =n-1;i>=0;--i)
	{
		if(posrem[a[i]%7] !=-1)
		{
			int x = posrem[a[i]%7];
			solver.addEdge(i + n+1, x + 1,5,0);
			solver.addEdge(i+n+1, x + 2*n + 1,5,0);
			solver.addEdge(i + 2*n + 1, x  +2*n+1,5,0);
		}
		if(poses[a[i] + 1] !=-1)
		{
			int x = poses[a[i] + 1];
			solver.addEdge(i+n+1, x + 1,5,0);
			solver.addEdge(i+n+1, x+3*n+1,5,0);
			solver.addEdge(i+3*n+1, x+3*n+1,5,0);
		}
		if(poses[a[i] - 1] != -1)
		{
			int x = poses[a[i] -1];
			solver.addEdge(i + n+1, x+1,5,0);
			solver.addEdge(i+n+1,x+3*n+1,5,0);
			solver.addEdge(i+3*n+1, x+3*n+1,5,0);
		}
		poses[a[i]] = i;
		posrem[a[i]% 7] = i;
	}
	for (int it = 0; it < 4; it++) solver.push();
	cout << abs(solver.getAns()) << endl;
	return 0;
}


