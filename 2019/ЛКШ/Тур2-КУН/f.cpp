#include <bits/stdc++.h>

using namespace std;
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 5e4 + 10;
map<pair <int, int>, int> ed;
int n, m, e;

vector<pair <pair <int, int> , vector<int> > > g1, g2;

void read() {
	cin >> n >> m >> e;
	g1.resize(n);
	g2.resize(m);

	for (int i = 0; i < n; i++) {
		cin >> g1[i].first.first;
		g1[i].first.second = i;;
	}

	for (int i = 0; i < m; i++) {
		cin >> g2[i].first.first;
		g2[i].first.second = i;
	}

	for (int i = 0; i < e; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		g1[u].second.push_back(v);
		g2[v].second.push_back(u);
		ed[{u, v}] = i + 1;
	}
}

bool cmp1(pair <pair <int, int>, vector<int> > &a, pair <pair <int, int>, vector<int> > &b) {
	return a.first.first > b.first.first;
}

bool cmp2(pair <pair <int, int>, vector<int> > &a, pair <pair <int, int>, vector<int> > &b) {
	return a.first.second < b.first.second;
}

int mt1[MAXN], used1[MAXN];

bool dfs1(int v, int c) {
	if (used1[v] == c) return false;
	used1[v] = c;
	for (auto i : g1[v].second) {
		if (mt1[i] == -1 || dfs1(mt1[i], c)) {
			mt1[i] = v;
			return true;
		}
	}
	return false;
}

int mt2[MAXN], used2[MAXN];

bool dfs2(int v, int c) {
	if (used2[v] == c) return false;
	used2[v] = c;
	for (auto i : g2[v].second) {
		if (mt2[i] == -1 || dfs2(mt2[i], c)) {
			mt2[i] = v;
			return true;
		}
	}
	return false;
}

vector<vector<int> > gr;


int mt[MAXN], used[MAXN];


bool dfs(int v, int c) {
	if (used[v] == c) return false;
	used[v] = c;
	for (auto i : gr[v]) {
		if (mt[i] == -1 || dfs(mt[i], c)) {
			mt[i] = v;
			return true;
		}
	}
	return false;
}

int w;
vector<int> ans;

void run() {
	for (int i = 0; i < MAXN; i++) {
		used[i] = used1[i] = used2[i] = mt[i] = mt1[i] = mt2[i] = -1;
	}

	sort(g1.begin(), g1.end(), cmp1);
	for (int i = 0; i < n; i++) {
		dfs1(i, i);
	}

	vector<pair <int, int> > p1;
	set<int> good1;

	for (int i = 0; i < m; i++) {
		if (mt1[i] != -1) {
			good1.insert(g1[mt1[i]].first.second);
		}
	}	

	sort(g1.begin(), g1.end(), cmp2);
	sort(g2.begin(), g2.end(), cmp1);

	for (int i = 0; i < m; i++) {
		dfs2(i, i);
	}

	set<int> good2;

	for (int i = 0; i < n; i++) {
		if (mt2[i] != -1) {
			good2.insert(g2[mt2[i]].first.second);
		} 
	}

	sort(g2.begin(), g2.end(), cmp2);

	gr.resize(n);
	for (auto i : ed) {
		if (good1.count(i.first.first) && good2.count(i.first.second)) {
			gr[i.first.first].push_back(i.first.second);
		}
	}

	for (int i = 0; i < n; i++) {
		dfs(i, i);
	}

	vector<pair <int, int> > p;
	for (int i = 0; i < m; i++) {
		if (mt[i] != -1) {
			p.push_back({mt[i], i});
		}
	}

	set<int> vert1, vert2;

	for (auto i : p) {
		ans.push_back(ed[i]);
		vert1.insert(i.first);
		vert2.insert(i.second);
	}
	w = 0;
	for (auto i : vert1) {
		w += g1[i].first.first;
	}
	for (auto i : vert2) {
		w += g2[i].first.first;
	}
}	

void write() {
	cout << w << endl;
	cout << ans.size() << endl;
	sort(ans.begin(), ans.end());
	for (auto i : ans) {
		cout << i << " ";
	}
	cout << endl;
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
4 3 3 
2 0 9 9
1 0 9
1 2
2 1
1 1

3 2 4
1 2 3
1 2
1 1
2 1
2 2
3 2
*/