#include <bits/stdc++.h>

using namespace std;
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 1e5 + 10;
int par[MAXN], sz[MAXN];

void make(int n) {
	for (int i = 0; i < n; i++) {
		par[i] = i;
		sz[i] = 1;
	}
}

int get_par(int v) {
	if (v == par[v])
		return v;
	return par[v] = get_par(par[v]);
}

int get_sz(int v) {
	v = get_par(v);
	return sz[v];
}

void uni(int a, int b) {
	a = get_par(a);
	b = get_par(b);
	if (a == b) return;
	if (sz[a] < sz[b])
		swap(a, b);
	par[b] = a;
	sz[a] += sz[b];
}

struct edge{
	int u, v, cost;
	edge(int a, int b, int c) {
		u = a, v = b, cost = c;
	}
};

struct question{
	int u, v, z;
	question(int a, int b, int c) {
		u = a, v = b, z = c;
	}
};	

int n, m;
vector<edge> g;
int q;
vector<question> query;

void read() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		g.push_back(edge(u, v, i + 1));
	}
	cin >> q;
	for (int i = 0; i < q; i++) {
		int a, b, z;
		cin >> a >> b >> z;
		a--;
		b--;
		query.push_back(question(a, b, z));
	}
}

vector<int> ans;

void run() {
	vector<pair <int, int> > fq;
	for (int i = 0; i < q; i++) {
		fq.push_back({0, m});
	}

	while (true) {
		bool flag = false;
		for (auto i : fq)
			flag |= (i.first < i.second - 1);
		if (!flag)
			break;
		
		vector<pair <int, int> > mid;
		for (int i = 0; i < q; i++) {
			mid.push_back({(fq[i].first + fq[i].second) / 2, i});
		} 
		
		sort(mid.begin(), mid.end());

		make(n);

		int pos = 0;

		while (pos < q && mid[pos].first == 0) {
			pos++;
		}

		for (int i = 0; i < m; i++) {
			uni(g[i].u, g[i].v);
			while (pos < q && mid[pos].first == g[i].cost) {
				int u = get_par(query[mid[pos].second].u);
				int v = get_par(query[mid[pos].second].v);
				int sz = get_sz(u);
				if (u != v)
					sz += get_sz(v);

				if (sz >= query[mid[pos].second].z)
					fq[mid[pos].second].second = mid[pos].first;
				else
					fq[mid[pos].second].first = mid[pos].first;
				pos++;
			}
		}
	}

	for (auto i : fq)
		ans.push_back(i.second);
}

void write() {
	for (auto i : ans)
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