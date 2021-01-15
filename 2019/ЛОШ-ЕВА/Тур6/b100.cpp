#include <bits/stdc++.h>

using namespace std;

vector<vector<int> > ed;
int n, m;
void read() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int u, v, a, b;
		cin >> u >> v >> a >> b;
		ed.push_back({u, v, a, b});
	}
}

const int MAXN = 3e5 + 10;
int pred[MAXN], sz[MAXN];

void make(){
	for (int i = 0; i < n; i++) {
		pred[i] = i, sz[i] = 1;
	}
}

int get(int v) {
	if (v == pred[v]) return v;
	return pred[v] = get(pred[v]);
}

void uni(int v, int u) {
	v = get(v);
	u = get(u);
	if (v == u) return;
	if (sz[v] < sz[u]) swap(v, u);
	pred[u] = v;
	sz[v] += sz[u];
}

struct edge{
	int u, v, a, b;
	double cost;
	edge() {

	}
	edge(int x, int y, int z, int t, double c) {
		u = x, v = y, a = z, b = t;
		cost = c;
	}
};

bool cmp(edge a, edge b) {
	return a.cost > b.cost;
}

pair <bool, pair <int, int> > get_ans(double x) {
	make();
	vector<edge> help;
	for (int i = 0; i < m; i++) {
		help.push_back(edge(ed[i][0], ed[i][1], ed[i][2], ed[i][3], (double) ed[i][2] - ed[i][3] * x));
	}
	sort(help.begin(), help.end(), cmp);

	double full_cost = 0;
	int p = 0, q = 0;
	for (int i = 0; i < m; i++) {
		if (get(help[i].u) != get(help[i].v)) {
			uni(help[i].u, help[i].v);
			full_cost += help[i].cost;
			p += help[i].a;
			q += help[i].b;
		}
	}
	pair <bool, pair <int, int> > ans = {full_cost > 0, {p, q}};
	return ans;
}

int p, q;
void run() {
	double l = 0, r = 110;
	while (abs(l - r) > 1e-6) {
		double mid = (l + r) / 2;
		if (get_ans(mid).first)
			l = mid;
		else
			r = mid;
	}
	auto help = get_ans(l);
	p = help.second.first;
	q = help.second.second;
	int g = __gcd(p, q);
	p /= g;
	q /= g;
}

void write() {
	cout << p << "/" << q << endl;
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