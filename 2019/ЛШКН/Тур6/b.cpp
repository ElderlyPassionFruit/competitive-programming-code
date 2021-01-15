#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 1e6 + 10;

vector<int> g[MAXN];
int cnt[MAXN];
int n, m;
int loop = 0;
void read() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		if (u == v) {
			loop++;
			cnt[u]++;
		}
		else
		g[u].push_back(v), g[v].push_back(u);
	}
}

bool used[MAXN];

void dfs(int v) {
	used[v] = true;
	for (auto i : g[v]) {
		if (!used[i])
			dfs(i);
	}
}

bool check() {
	int v = 0;
	while (v < n && g[v].empty())
		v++;
	dfs(v);
	for (int i = 0; i < n; i++) {
		if (!used[i] && (!g[i].empty() || cnt[i]))
			return false;
	}
	return true;
}

int ans = 0;

void run() {
	if (!check())
		return;
	for (int i = 0; i < n; i++) {
		ans += (int)(g[i].size()) * ((int)g[i].size() - 1) / 2;
	}

	cout << ans << endl;
	ans += loop * (loop - 1) / 2 + loop * (m - loop);
	cout << ans << endl;
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