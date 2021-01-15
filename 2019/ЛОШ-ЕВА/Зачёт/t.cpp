#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 2e5 + 10, MAXK = 7;

int n, k;
vector<int> a[MAXN];
vector<int> have[MAXK];
int mid[MAXK];

void read() {
	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		a[i].resize(k);
		for (int j = 0; j < k; j++) {
			cin >> a[i][j];
			have[j].push_back(a[i][j]);
		}
	}
}

int get_mask(vector<int> & a) {
	int mask = 0;
	for (int i = 1; i < k; i++) {
		mask *= 3;
		if (a[i] == mid[i])
			mask += 1;
		else if (a[i] > mid[i])
			mask += 2;
	}
	return mask;
}

const int MAXPOW = 3e3;

vector<int> L[MAXPOW], R[MAXPOW];

void build() {
	for (int i = 0; i < k; i++) {
		sort(all(have[i]));
		mid[i] = have[i][(n - 1) / 2];
	}
	for (int i = 0; i < n; i++) {
		if (mid[0] >= a[i][0]) {
			L[get_mask(a[i])].push_back(i);
		}	
		else {
			R[get_mask(a[i])].push_back(i);
		}	
	}
}

struct edge{
	int to, cap, flow;
	edge() {}
	edge(int a, int b, int c) {
		to = a, cap = b, flow = c;
	} 
	int get_cap() {
		return cap - flow;
	}
};

const int INF = 1e9;

struct max_flow{
	vector<edge> Edges;
	vector<vector<int> > g;
	int n;
	int s, f;
	int flow;

	max_flow() {
		flow = 0;
	}
	max_flow(int sz, int S, int F) {
		n = sz;
		s = S;
		f = F;
		flow = 0;
		g.resize(n);
	}

	void add_edge(int v, int to, int cap) {
		g[v].push_back(Edges.size());
		Edges.push_back({to, cap, 0});
		g[to].push_back(Edges.size());
		Edges.push_back({v, 0, 0});
	}

	vector<int> dist;

	bool bfs() {
		dist.assign(n, INF);
		dist[s] = 0;
		queue<int> q;
		q.push(s);
		while (!q.empty()) {
			int v = q.front();
			q.pop();
			for (auto i : g[v]) {
				if (Edges[i].get_cap() < 1) continue;
				if (dist[Edges[i].to] != INF) continue;
				dist[Edges[i].to] = dist[v] + 1;
				q.push(Edges[i].to);
			}
		}
		return dist[f] != INF;
	}

	vector<int> pos;

	int dfs(int v, int min_cap) {
		if (v == f) return min_cap;
		while (pos[v] < g[v].size()) {
			int ind = g[v][pos[v]];
			pos[v]++;
			if (Edges[ind].get_cap() < 1) continue;
			if (dist[v] + 1 != dist[Edges[ind].to]) continue;
			int ans = dfs(Edges[ind].to, min(min_cap, Edges[ind].get_cap()));
			if (ans) {
				Edges[ind].flow += ans;
				Edges[ind ^ 1].flow -= ans;
				pos[v]--;
				return ans;
			}
		}
		return 0;
	}

	void make_flow() {
		while (bfs()) {
			pos.assign(n, 0);
			while (true) {
				int x = dfs(s, INF);
				flow += x;
				if (x == 0) break;
			}
		}
	}
};

bool check(int mask_l, int mask_r) {
	for (int i = 0; i < k - 1; i++) {
		int l = mask_l % 3;
		int r = mask_r % 3;
		mask_l /= 3;
		mask_r /= 3;
		if (l != r) continue;
		if (l == 1) continue;
		return false;
	}
	return true;
}

max_flow g;

void build_flow() {
	int cnt = 1;
	for (int i = 0; i < k - 1; i++)
		cnt *= 3;
	int s = cnt * 2;
	int f = cnt * 2 + 1;
	g = max_flow(cnt * 2 + 2, s, f);
	for (int i = 0; i < cnt; i++) {
		g.add_edge(s, i, L[i].size());
		g.add_edge(i + cnt, f, R[i].size());
	}
	for (int i = 0; i < cnt; i++) {
		for (int j = 0; j < cnt; j++) {
			if (check(i, j)) {
				g.add_edge(i, j + cnt, INF);
			}
		}
	}
	g.make_flow();
}

vector<pair<int, int> > ans;

void build_ans() {
	if (g.flow != n / 2) {
		cout << "NO" << endl;
		exit(0);
	}
	int cnt = (g.n - 2) / 2;
	for (int i = 0; i < cnt; i++) {
		for (auto j : g.g[i]) {
			while (g.Edges[j].flow > 0) {
				assert(L[i].size() > 0);
				int l = L[i].back();
				L[i].pop_back();
				int r = R[g.Edges[j].to - cnt].back();
				R[g.Edges[j].to - cnt].pop_back();
				ans.push_back({l, r});
				g.Edges[j].flow--;
			}
		}
	}
}

void run() {
	build();
	build_flow();
	build_ans();
}

void write() {
	cout << "YES" << "\n";
	for (auto i : ans)
		cout << i.first + 1 << " " << i.second + 1 << "\n";
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