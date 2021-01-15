#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

#define int ll
const int MAXN = 200;
vector<int> g[MAXN];
int c[MAXN];
int n;

void read() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		x--;
		c[i] = x;
	}
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
}

int ans[MAXN];

void dfs(int v, int p, vector<int> have) {
	have.push_back(c[v]);
	sort(all(have));
	have.resize(unique(all(have)) - have.begin());
	for (auto i : have)
		ans[i]++;
	for (auto i : g[v]) {
		if (i == p) continue;
		dfs(i, v, have);
	}
}

void run() {
	for (int i = 0; i < n; i++) {
		dfs(i, i, {});
		ans[c[i]]++;
	}
}

void write() {
	for (int i = 0; i < n; i++)
		cout << ans[i] / 2 << "\n";
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