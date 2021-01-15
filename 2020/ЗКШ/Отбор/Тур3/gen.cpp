#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

mt19937 rnd(time(0));

int get(int l, int r) {
	return rnd() % (r - l + 1) + l;
}

set<pair<int, int> > ed;

void add(int u, int v) {
	ed.insert({min(u, v), max(u, v)});
}

bool check(int u, int v) {
	return !ed.count({min(u, v), max(u, v)}) && u != v;
}

int n, m;

void add() {
	while (true) {
		int u = get(1, n);
		int v = get(1, n);
		if (!check(u, v)) continue;
		add(u, v);
		break;
	}
}

vector<vector<int>> g;

vector<bool> used;

void dfs(int v) {
	used[v] = true;
	for (auto i : g[v])  {
		if (!used[i])
			dfs(i);
	}
}

void gen() {
	while (true) {
		g.assign(n, {});
		for (int i = 0; i < m; i++) {
			add();
		}
		for (auto i : ed) {
			g[i.first - 1].push_back(i.second - 1);
			g[i.second - 1].push_back(i.first - 1);
		}
		used.assign(n, 0);
		dfs(0);
		bool flag = true;
		for (auto i : used)
			flag &= i;
		if (flag) return;
	}
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	n = get(1, 10);
	m = get(n - 1, n + 1);
	if (n == 1)
		m = 0;
	if (n == 2)
		m = min(m, 1);
	if (n == 3)
		m = min(m, 3);
	cout << n << " " << m << endl;
	gen();
	for (auto i : ed)
		cout << i.first << " " << i.second << endl;
	return 0;
}