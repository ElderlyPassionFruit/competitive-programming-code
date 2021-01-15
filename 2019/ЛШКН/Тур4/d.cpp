#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 2e5 + 10;

vector<int> g[MAXN];
int n, m;

void read() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
}

int sz[MAXN];
int color[MAXN];

void dfs(int v, int col) {
	color[v] = col;
	sz[col]++;
	for (auto i : g[v]) {
		if (!color[i])
			dfs(i, col);
	}
}

bool ans;
int cnt[MAXN];

void run() {
	int c = 1;
	for (int i = 0; i < n; i++) {
		if (!color[i])
			dfs(i, c++);
	}

	for (int i = 0; i < n; i++) {
		cnt[color[i]] += g[i].size();
	}

	for (int i = 0; i < MAXN; i++)
		cnt[i] /= 2;


	ans = true;
	for (int i = 0; i < MAXN; i++) {
		if (sz[i] * (sz[i] - 1) / 2 != cnt[i])
			ans = false;
	}
}

void write() {
	if (ans)
		cout << "YES" << endl;
	else
		cout << "NO" << endl;
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