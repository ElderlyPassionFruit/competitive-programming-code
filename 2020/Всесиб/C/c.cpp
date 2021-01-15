#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

#define int ll

struct edge{
	int to, cap, flow;
	ll cost;
	edge() {}
	edge(int a, int b, ll c) {
		to = a, cap = b, cost = c, flow = 0;
	}
};

struct min_cost_max_flow{
	vector<edge> Ed;
	vector<vector<int> > g;
	int n, s, t;
	
	min_cost_max_flow() {}

	min_cost_max_flow(int sz, int S, int T) {
		n = sz, s = S, t = T;
		g.assign(n, {});
	}

	void add_edge(int u, int v, int cap, int cost) {
		g[u].push_back(Ed.size());
		Ed.push_back({v, cap, cost});
		g[v].push_back(Ed.size());
		Ed.push_back({u, 0, -cost});
	}

	vector<int> p;
	vector<ll> dist;
	vector<bool> used;
	queue<int> q;
	const ll INF = 4e18;

	bool push() {
		p.assign(n, -1);
		dist.assign(n, INF);
		used.assign(n, false);
		
		dist[s] = 0;
		q.push(s);
		used[s] = true;

		while (!q.empty()) {
			int v = q.front();
			q.pop();
			used[v] = false;
			for (auto i : g[v]) {
				if (Ed[i].flow + 1 > Ed[i].cap) continue;
				int u = Ed[i].to;
				if (dist[u] <= dist[v] + Ed[i].cost) continue;
				dist[u] = dist[v] + Ed[i].cost;
				p[u] = i;
				if (!used[u])
					q.push(u);
				used[u] = true;
			}
		}
		if (dist[t] == INF) return false;

		int v = t;
		while (v != s) {
			Ed[p[v]].flow++;
			Ed[p[v] ^ 1].flow--;
			v = Ed[p[v] ^ 1].to;
		}
		return true;
	}

	ll get_min_cost() {
		while (push()) {}
		ll ans = 0;
		for (int i = 0; i < Ed.size(); i += 2)
			ans += Ed[i].flow * Ed[i].cost;
		return ans;
	}
};

int n;
vector<ll> a, b;

void read() {
	cin >> n;
	a.resize(n);
	for (auto &i : a)
		cin >> i;
	b.resize(n);
	for (auto &i : b)
		cin >> i;
}

ll ans;

void run() {
	int s = 2 * n, t = 2 * n + 1;
	min_cost_max_flow g(2 * n + 2, s, t);
	for (int i = 0; i < n; i++) {
		g.add_edge(s, i, 1, 0);
	}
	for (int i = 0; i < n; i++) {
		g.add_edge(i + n, t, 1, 0);
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			g.add_edge(i, j + n, 1, -1LL * (__gcd(a[i], b[j])));
		}
	}
	ans = abs(g.get_min_cost());
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