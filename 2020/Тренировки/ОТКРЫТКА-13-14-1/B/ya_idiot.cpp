#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct edge{
	int to, ind1, ind2;
	edge() {}
	edge(int _to, int _ind1, int _ind2) {
		to = _to, ind1 = _ind1, ind2 = _ind2;
	}
};

const int MAXN = 3e5 + 10;
vector<edge> g[MAXN];
int p[MAXN];
int n, m;

void read() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		cin >> p[i];
	}
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		int ind1 = g[u].size();
		int ind2 = g[v].size();
		g[u].push_back({v, ind1, ind2});
		g[v].push_back({u, ind2, ind1});
	}
}

struct segment_tree{
	//vector<pair<int, int>> tree;
	int n;
	vector<vector<pair<int, int>>> sparse;
	vector<int> lg;
	vector<int> p;
	int LOG;

	segment_tree() {}

	/*void build(int v, int tl, int tr, const vector<pair<int,int>> & a) {
		//if (v == 0) exit(0);
		//cout << v << " " << tl << " " << tr << endl;
		if (tl == tr - 1) {
			tree[v] = a[tl];
			return;
		}
		int tm = (tl + tr) / 2;
		build(v * 2, tl, tm, a);
		build(v * 2 + 1, tm, tr, a);
		tree[v] = max(tree[v * 2], tree[v * 2 + 1]);
	}*/

	segment_tree(vector<pair<int, int>> a) {
		n = a.size();
		if (n == 0) return;
		lg.resize(n + 1);
		lg[0] = -1;
		for (int i = 1; i <= n; i++) {
			lg[i] = lg[i / 2] + 1;
		}
		LOG = lg.back();
		p.resize(LOG + 1);
		p[0] = 1;
		for (int i = 1; i < p.size(); i++) {
			p[i] = p[i - 1] * 2;
		}
		//cout << "puhh" << endl;
		sparse.resize(n, vector<pair<int,int>> (LOG + 1, make_pair(-1, -1)));
		for (int i = 0; i < n; i++) {
			sparse[i][0] = a[i];
		}
		//cout << "puhh1" << endl;
		for (int l = 1; l < LOG; l++) {
			for (int i = 0; i + (1 << (l - 1)) < n; i++) {
				sparse[i][l] = max(sparse[i][l - 1], sparse[i + p[l - 1]][l - 1]);
			}
		}
		//cout << "puhh2" << endl;
	}

	pair<int, int> get(int l, int r) {
		if (l > r) return {-1, -1};
		int len = r - l + 1;
		int log = lg[len];
		int pw = p[log];

		return max(sparse[l][log], sparse[r - pw + 1][log]);
	}
};

segment_tree pref[MAXN];


pair<int, int> color[MAXN];
void build() {
	for (int i = 0; i < n; i++) {
		color[i] = {-1, -1};
	}
	for (int i = 0; i < n; i++) {
		vector<pair<int, int>> a;
		for (auto [j, ind1, ind2] : g[i]) {
			a.push_back({p[j], j});
		}
		pref[i] = segment_tree(a);
	}
	//cout << "puhh" << endl;
}

int ans;
vector<int> fans;


void build_color(int v, int c) {
	for (auto [to, ind1, ind2] : g[v]) {
		//if (g[to].size() > g[v].size()) continue;
		if (c == 0) {
			color[to] = {ind1, ind2};
		}
		else {
			color[to] = {-1, -1};
		}
	}
}


pair<int, int> get(int v, int ind1, int ind2) {
	if (ind1 == -1 && ind2 == -1) return pref[v].get(0, pref[v].n - 1);
	if (ind1 == -1) return max(pref[v].get(0, ind2 - 1), pref[v].get(ind2 + 1, pref[v].n - 1));
	if (ind2 == -1) return max(pref[v].get(0, ind1 - 1), pref[v].get(ind1 + 1, pref[v].n - 1));
	if (ind1 > ind2) swap(ind1, ind2);
	pair<int, int> ans = {-1, -1};
	chkmax(ans, pref[v].get(0, ind1 - 1));
	chkmax(ans, pref[v].get(ind1 + 1, ind2 - 1));
	chkmax(ans, pref[v].get(ind2 + 1, pref[v].n - 1));
	return ans;
} 

void run() {
	ans = 0;
	build();
	vector<int> order(n);
	iota(all(order), 0);
	sort(all(order), [&] (int i, int j) {return g[i].size() > g[j].size();});
	for (auto v1 : order) {
		build_color(v1, 0);
		for (auto [v2, ind1, ind2] : g[v1]) {
			if (g[v2].size() > g[v1].size()) continue;
			for (auto [v3, ind3, ind4] : g[v2]) {
				if (v3 == v1) continue;
				if (color[v3] == make_pair(-1, -1)) {
					pair<pair<int, int>, int> fans = {{-1, -1}, -1};
					chkmax(fans, make_pair(get(v1, ind1, -1), v1));
					chkmax(fans, make_pair(get(v3, ind4, -1), v3));
					if (fans.first.second != -1) {
						if (fans.second == v3) {
							relax({v1, v2, v3, fans.first.second});
						}
						else {
							relax({fans.first.second, v1, v2, v3});	
						}
					}
				}	
				else {
					pair<pair<int, int>, int> fans = {{-1, -1}, -1};
					chkmax(fans, make_pair(get(v1, ind1, color[v3].first), v1));
					chkmax(fans, make_pair(get(v2, ind2, ind3), v2));
					chkmax(fans, make_pair(get(v3, ind4, color[v3].second), v3));
					if (fans.first.second != -1) {
						if (fans.second == v3) {
							relax({v1, v2, v3, fans.first.second});
						}
						else if (fans.second == v1) {
							relax({fans.first.second, v1, v2, v3});	
						}
						else {
							relax({v1, v3, v2, fans.first.second});		
						}
					}
				}			
			} 
		}
		build_color(v1, 1);
	}
	for (int i = 0; i < n; i++) {
		relax({i});
		for (auto [j, ind1, ind2] : g[i]) {
			relax({i, j});
		}
		if (g[i].size() < 2) continue;
		sort(all(g[i]), [&] (edge a, edge b) {return p[a.to] > p[b.to];});
		relax({g[i][0].to, i, g[i][1].to});
	}
}

void write() {
	cout << fans.size() << "\n";
	for (auto i : fans) {
		cout << i + 1 << " ";
	}
	cout << "\n";
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
5 5
4 5 2 1 2 
3 5
1 2
3 1
3 2
5 1

5 5
2 2 2 5 4 
4 2
4 1
5 1
1 3
2 1

*/