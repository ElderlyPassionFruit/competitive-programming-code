#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 1e5 + 10;
int n, m;
vector<int> g[MAXN];
int c[MAXN];

void read() {
	cin >> n >> m;
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	for (int i = 0; i < n; i++) {
		cin >> c[i];
	}
}

int col[MAXN];

void dfs(int v, int p, int len) {
	if (col[len] == -1) {
		col[len] = c[v];
	}
	else {
		col[len] = -2;
	}
	for (auto i : g[v]) {
		if (i == p) continue;
		dfs(i, v, len + 1);
	}
}

int calc(int v) {
	for (int i = 0; i < n; i++)
		col[i] = -1;
	dfs(v, -1, 0);
	set<int> have;
	for (int i = 1; i < n; i++) {
		have.insert(col[i]);
	}
	have.erase(-1);
	have.erase(-2);
	return have.size();
}

vector<int> ans;

void run() {
	for (int i = 0; i < n; i++) {
		ans.push_back(calc(i));
	}
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