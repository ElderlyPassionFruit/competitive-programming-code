#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 1e5 + 10;
vector<int> g[MAXN];
int n, m, q;

void read() {
	cin >> n >> m >> q;
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
}

int color[MAXN];

void dfs(int v, int c) {
	color[v] = c;
	for (auto i : g[v]) {
		if (color[i]) continue;
		dfs(i, c);
	}
}

void build() {
	int c = 1;
	for (int i = 0; i < n; i++) {
		if (!color[i]) {
			dfs(i, c++);
		}
	}
}

void run() {
	build();
	while (q--) {
		int u, v;
		cin >> u >> v;
		u--;
		v--; 
		if (color[u] == color[v])
			cout << "Yes\n";
		else
			cout << "No\n";

	}
}

void write() {

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