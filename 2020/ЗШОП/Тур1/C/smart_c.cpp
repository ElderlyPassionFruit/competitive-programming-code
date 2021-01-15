#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 2e5 + 10;

int n, m, q;
vector<int> g[MAXN];

vector<pair<int, int> > edge;
vector<int> op;
set<int> used;

void read() {
	cin >> n >> m >> q;
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		g[u].push_back(v);
		g[v].push_back(u);
		edge.push_back({u, v});
	}
	op.resize(q);
	for (int i = 0; i < m; i++)
		used.insert(i);
	for (auto &i : op) {
		cin >> i;
		i--;
		used.erase(i);
	}
}

const int INF = 1e9;
int d[MAXN];
queue<int> Q;
vector<bool> good;

void build() {
	for (int i = 0; i < n; i++) d[i] = INF;
	d[0] = 0;
	Q.push(0);
	while (!Q.empty()) {
		int v = Q.front();
		Q.pop();
		for (auto i : g[v]) {
			if (d[i] != INF) continue;
			d[i] = d[v] + 1;
			Q.push(i);
		}
	}
	for (auto &i : edge) {
		if (d[i.first] > d[i.second]) swap(i.first, i.second);
		if (abs(d[i.first] - d[i.second]) == 1)
			good.push_back(1);
		else
			good.push_back(0);
	}
}

int p[MAXN], sz[MAXN];
vector<int> el[MAXN];

int get_p(int v) {
	if (v == p[v]) return v;
	return p[v] = get_p(p[v]);
}

vector<int> Queue[MAXN];

void uni(int a, int b) {
	int la = a, lb = b;
	a = get_p(a);
	b = get_p(b);
	if (a == b) return;
	int c = get_p(0);
	
	if (a != c) {
		Queue[la].push_back(lb);
		return;
	}

	if (sz[a] < sz[b]) swap(a, b);
	sz[a] += sz[b];
	p[b] = a;
	for (auto i : el[b])
		el[a].push_back(i);
	el[b].clear();
}

void make() {
	for (int i = 0; i < n; i++)
		p[i] = i, sz[i] = 1, el[i] = {i};
}

vector<int> ans;

bool relax() {
	int v = get_p(0);
	if (el[v].size() == 0) return false;
	vector<int> a = el[v];
	el[v].clear();
	for (auto i : a) {
		for (auto j : Queue[i]) {
			uni(i, j);
		}
	}
	return true;
}

void Relax() {
	while (relax()) {}
}

void run() {
	build(), make();
	/*for (auto i : good)
		cout << i << " ";
	cout << endl;*/
	reverse(all(op));
	for (auto i : used) {
		if (good[i]) {
			uni(edge[i].first, edge[i].second);
			//cout << edge[i].first << " " << edge[i].second << endl;
		}
	}

	Relax();
	
	ans.push_back(n - sz[get_p(0)]);
	for (auto i : op) {
		if (good[i]) {
			uni(edge[i].first, edge[i].second);
		}
		Relax();
		ans.push_back(n - sz[get_p(0)]);
	}
	ans.pop_back();
	reverse(all(ans));
}

void write() {
	for (auto i : ans) {
		cout << i << "\n";
	}
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

/*

5 6 2
1 2
1 3
1 4
2 4
3 5
4 5
2
6



*/