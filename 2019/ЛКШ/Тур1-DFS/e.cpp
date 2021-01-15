#include <bits/stdc++.h>

using namespace std;
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 3e5 + 10, MAXM = 3e5 + 10;
vector<pair <int, int> > g[MAXN];
int n, m;

void read() {
	cin >> n;
	m = 0;
	for (int i = 0; i < n; i++) {
		int sz;
		cin >> sz;
		for (int j = 0; j < sz; j++) {
			int v;
			cin >> v;
			v--;
			if (i < v) {
				g[i].push_back({v, m});
				g[v].push_back({i, m});
				m++;
			}
		}
	}
}

bool used[MAXM];
vector<int> path, ans;
vector<int> iter;
void dfs(int v) {
	for (; iter[v] < g[v].size(); iter[v]++) {
		auto i = g[v][iter[v]];
		if (!used[i.second]) {
			used[i.second] = true;
			dfs(i.first);
		}
	}
	path.push_back(v + 1);
}

void run() {
	iter.assign(n, 0);
	bool flag = false;
	for (int i = 0; i < n; i++) {
		flag |= (((int) g[i].size())) % 2 == 1;
	}
	if (!flag) {
		dfs(0);
		ans = path;
		return;
	}

	int u = -1, v = -1;
	for (int i = 0; i < n; i++) {
		if ((((int) g[i].size()) % 2) == 1) {
			if (u == -1)
				u = i;
			else
				v = i;
		}
	} 
	g[u].push_back({v, m});
	g[v].push_back({u, m});
	m++;

	dfs(0);
	for (int i = 1; i <= m; i++)
		path.push_back(path[i]);

	u++;
	v++;

	for (int i = 0; i < path.size() - 1; i++) {
		if ((path[i] == u) && (path[i + 1] == v) || (path[i] == v && path[i + 1] == u)) {
			for (int j = i + 1; j < i + 1 + m; j++) {
				ans.push_back(path[j]);
			}
			return;
		}
	}
}

void write() {
	cout << ans.size() - 1 << endl;
	for (auto i : ans) {
		cout<< i << " ";
	}
	cout << endl;
}

signed main() {
	freopen("euler.in", "r", stdin);
	freopen("euler.out", "w", stdout);
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
2 2 2
4 1 4 3 1
2 2 4
2 3 2
*/