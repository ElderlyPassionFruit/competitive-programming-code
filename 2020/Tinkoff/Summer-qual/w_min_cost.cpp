#include <bits/stdc++.h>

using namespace std;
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int INF = 1e9 + 10;

namespace min_cost_flow{
	struct edge{
		int u, v, cap, cost, flow;
	};

	vector<edge> Edge;
	int n;
	vector<vector<int> > g;
	int s, f;

	void add_edge(int u, int v, int cap, int cost) {
		g[u].push_back(Edge.size());
		Edge.push_back({u, v, cap, cost, 0});
		g[v].push_back(Edge.size());
		Edge.push_back({v, u, 0, -cost, 0});
	}

	void make(int sz, int n_s, int n_f) {
		n = sz;
		g.resize(n);
		s = n_s;
		f = n_f;
	}

	vector<int> dist;
	vector<int> p;
	vector<bool> used;
	queue<int> q;

	void FB(){
		dist.assign(n, INF);
		p.assign(n, 0);
		used.assign(n, false);

		dist[s] = 0;
		q.push(s);
		used[s] = true;
		
		while (!q.empty()) {
			int v = q.front();
			q.pop();
			used[v] = false;
			for (auto i : g[v]) {
				if (Edge[i].cap - Edge[i].flow <= 0) continue; 
				int u = v ^ Edge[i].u ^ Edge[i].v;
				if (dist[u] <= dist[v] + Edge[i].cost) continue;
				dist[u] = dist[v] + Edge[i].cost;
				p[u] = i;
				if (!used[u]) {
					q.push(u);
					used[u] = true;
				}
			}
		}
	}

	void push_flow() {
		FB();
		if (dist[f] == INF)
			return;
		int v = f;
		while (v != s) {
			int ind = p[v];
			Edge[ind].flow++;
			Edge[ind ^ 1].flow--;
			v ^= Edge[ind].u ^ Edge[ind].v;
		}
	}

	int get_min_cost(int k) {
		for (int i = 0; i < k; i++){
			push_flow();
		}
		int ans = 0;
		for (int i = 0; i < Edge.size(); i += 2) {
			ans += Edge[i].flow * Edge[i].cost;
		}

		return ans;
	}
};

struct pt{
	int x, y;
};

struct ed{
	pt a, b;
	int cost;
};

bool operator<(ed a, ed b) {
	return a.cost > b.cost;
}

bool operator<(pt a, pt b) {
	return tie(a.x, a.y) < tie(b.x, b.y);
}

const int MAXN = 2010;
int n, k;
int a[MAXN][MAXN];

void read() {
	cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> a[i][j];
		}
	}
}

bool check(int x, int y) {
	return x >= 1 && x <= n && y >= 1 && y <= n;
}

void build() {
	vector<ed> have;
	vector<int> dx = {-1, 0, 1, 0}, dy = {0, 1, 0, -1};
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if ((i + j) % 2 == 1) continue;
			for (int k = 0; k < 4; k++) {
				int x = i + dx[k];
				int y = j + dy[k];
				if (!check(x, y)) continue;
				have.push_back({{i, j}, {x, y}, a[i][j] + a[x][y]});				
			}
		}
	}
	sort(have.begin(), have.end());
	while (have.size() > 10000)
		have.pop_back();

	set<pt> left, right;
	for (auto i : have) {
		left.insert(i.a);
		right.insert(i.b);
	}
	
	map <pt, int> pos_left;
	int cnt_left = 0;
	
	for (auto i : left) {
		pos_left[i] = cnt_left++;
	}

	map <pt, int> pos_right;
	int cnt_right = 0;
	for (auto i : right) {
		pos_right[i] = cnt_right++;
	}

	min_cost_flow::make(cnt_left + cnt_right + 2, 0, 1);
	for (auto i : have) {
		min_cost_flow::add_edge(2 + pos_left[i.a], 2 + cnt_left + pos_right[i.b], 1, -i.cost);
	}

	for (int i = 0; i < cnt_left; i++) {
		min_cost_flow::add_edge(0, i + 2, 1, 0);
	}

	for (int i = 0; i < cnt_right; i++) {
		min_cost_flow::add_edge(i + 2 + cnt_left, 1, 1, 0);
	}
}

long long ans;

void run() {
	build();
	ans = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			ans += a[i][j];
		}
	}
	ans += min_cost_flow::get_min_cost(k);
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