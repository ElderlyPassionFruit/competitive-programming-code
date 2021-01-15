#include <bits/stdc++.h>

using namespace std;
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
const int MAXN = 1e3 + 10;
vector<pair <pair <int, int> , vector<int> > > g;
int n;

bool cmp(pair <pair <int, int> , vector<int> > & a, pair <pair <int, int> , vector<int> > & b) {
	return a.first.first > b.first.first;
}

void read() {
	cin >> n;
	g.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> g[i].first.first;
		g[i].first.second = i;
	}
	for (int i = 0; i < n; i++) {
		int sz;
		cin >> sz;
		for (int j = 0; j < sz; j++) {
			int v;
			cin >> v;
			v--;
			g[i].second.push_back(v);
		}
	}
	sort(g.begin(), g.end(), cmp);
}

vector <int> mt, used;

bool dfs(int v, int c) {
	if (used[v] == c) return false;
	used[v] = c;
	for (auto i : g[v].second) {
		if (mt[i] == -1 || dfs(mt[i], c)) {
			mt[i] = v;
			return true;
		}
	}
	return false;
}

vector <int> ans;

void run() {
	mt.assign(n, -1);
	used.assign(n, -1);
	for (int i = 0; i < n; i++) {
		dfs(i, i);
	}

	ans.assign(n, 0);
	for (int i = 0; i < n; i++) {
		if (mt[i] != -1) {
			ans[g[mt[i]].first.second] = i + 1;
		}
	}
}

void write() {
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
4
1 3 2 4
4 1 2 3 4
2 1 4
2 1 4
2 1 4
*/