#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;

#define all(x) (x).begin(), (x).end()
template <typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;};
template <typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (y > x) x = y;};
const int MAXN = 1e5 + 10;
int n, m, q;
set<int> g[MAXN];

void read() {
	cin >> n >> m >> q;
	//assert(n <= 100);
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		g[u].insert(v);
		g[v].insert(u);
	}
}

const int INF = 1e9;

int dfs(int v, int p, int u1, int v1) {
	int ans = INF;
	for (auto i : g[v]) {
		if (i == p) continue;
		if (i == v1) continue;
		if (i == u1) 
			ans = 0;
		else 
			ans = min(ans, dfs(i, v, u1, v1) + 1);
	}
	return ans;
}

int get(int v, int u) {
	if (u == v) return 0;
	int ans = dfs(v, -1, u, v);
	if (ans == INF) ans = -1;
	return ans;
}

void run() {
	for (int i = 0; i < q; i++) {
		char type;
		int u, v;
		cin >> type >> u >> v;
		u--;
		v--;
		if (type == '+') {
			g[u].insert(v);
			g[v].insert(u);		
		}
		else if (type == '-') {
			g[u].erase(v);
			g[v].erase(u);
		}
		else {
			cout << get(u, v) << endl;
		}
	}
}

void write() {

}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.setf(ios::fixed), cout.precision(20);
	read();
	run();
	write();
	return 0;
}