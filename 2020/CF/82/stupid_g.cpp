#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

#define int ll

const int MAXN = 1e5 + 10;
vector<int> g[MAXN];
int n;
int a[MAXN];

void read() {
	cin >> n;
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	for (int i = 0; i < n; i++) 
		cin >> a[i];
}

ll ans;

void dfs(int v, int p, int sum, int fans) {
	sum += a[v];
	fans += sum;
	chkmax(ans, fans);
	for (auto i : g[v]) {
		if (i == p) continue;
		dfs(i, v, sum, fans);
	}
}

void run() {
	ans = 0;
	for (int i = 0; i < n; i++) {
		dfs(i, -1, 0, 0);
	}
}

void write() {
	cout << ans << endl;
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