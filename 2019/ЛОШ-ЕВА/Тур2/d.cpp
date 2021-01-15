#pragma comment(linker, "/stack:200000000")
//#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,avx,avx2")
#include <bits/stdc++.h>

using namespace std;
const int MAXN = 2 * 1e5 + 10, MAXLOG = 18, max_XOR = 1 << 20;

int n;
vector<int> g[MAXN];
char lett[MAXN];

int dp[MAXN][MAXLOG], tin[MAXN], tout[MAXN], timer = 0;

long long start[MAXN], finish[MAXN];
long long calc[max_XOR];

unordered_set <int> good_nums;

bool used[MAXN];
int sz[MAXN];
int centr;

long long ans[MAXN], diff[MAXN];

void dfs(int v, int p) {
	tin[v] = timer++;
	dp[v][0] = p;
	for (int i = 1; i < MAXLOG; i++)
		dp[v][i] = dp[dp[v][i - 1]][i - 1];
	for (auto i : g[v])
		if (i != p)
			dfs(i, v);
	tout[v] = timer++;
}

bool is_upper(int v, int u) {
	return tin[v] <= tin[u] && tout[v] >= tout[u];
}

int lca(int v, int u) {
	if (is_upper(v, u)) return v;
	if (is_upper(u, v)) return u;
	for (int i = MAXLOG - 1; i >= 0; i--)
		if (!is_upper(dp[v][i], u))
			v = dp[v][i];
	return dp[v][0];
}

void dfs_centroid(int v, int p, int size) {
	sz[v] = 1;
	int mx = 0;
	for (auto i : g[v]) {
		if (i != p && !used[i]) {
			dfs_centroid(i, v, size);
			sz[v] += sz[i];
			mx = max(sz[i], mx);
		}
	}
	mx = max(mx, size - sz[v]);
	if (mx <= size / 2) {
		centr = v;
	}
}

bool check(int num) {
	return good_nums.count(num);
}

void add_path(int u, int v, long long cnt) {
	int l = lca(u, v);
	if (l != u && l != v) {
		start[u] += cnt;
		start[v] += cnt;
		finish[l] += 2 * cnt;
		diff[l] += 2 * cnt;
		return;
	}
	if (l != u) {
		start[u] += cnt;
		finish[l] += cnt;
		return;
	}
	if (l != v) {
		start[v] += cnt;
		finish[l] += cnt;
		return;
	}
}

long long dfs_ans(int v, int p) {
	ans[v] = start[v];
	for (auto i : g[v]) {
		if (i != p) {
			ans[v] += dfs_ans(i, v);
		}
	}
	return ans[v] - finish[v];
}

void dfs_calc(int v, int p, int XOR, int centr) {
	XOR ^= 1 << (lett[v] - 'a');
	long long add = 0;
	if (check(XOR ^ (1 << (lett[centr] - 'a')))) {
		add_path(v, centr, 1);
	}

	add += calc[XOR^(1 << (lett[centr] - 'a'))];

	for (int i = 0; i < 20; i++)
		add += calc[XOR ^ (1 << i) ^ (1 << (lett[centr] - 'a'))];
	
	add_path(v, centr, add);
	diff[centr] += add;
	
	for (auto i : g[v]) {
		if (i != p && !used[i]) {
			dfs_calc(i, v, XOR, centr);
		}
	}
}

void dfs_add(int v, int p, int XOR, int add) {
	XOR ^= (1 << (lett[v] - 'a'));
	calc[XOR] += add;
	for (auto i : g[v]) {
		if (i != p && !used[i]) {
			dfs_add(i, v, XOR, add);
		}
	}
}

void solve(int v, int size) {
	if (used[v]) return;
	dfs_centroid(v, -1, size);
	int u = centr;
	used[u] = true;
	
	for (auto i : g[u]) {
		if (used[i]) continue;
		dfs_add(i, u, 0, 1);
	} 
	
	for (auto i : g[u]) {
		if (used[i]) continue;
		dfs_add(i, u, 0, -1);
		dfs_calc(i, u, 0, centr);
		dfs_add(i, u, 0, 1);
	}

	for (auto i : g[u]) {
		if (used[i]) continue;
		dfs_add(i, u, 0, -1);
	}	

	for (auto i : g[u]) {
		if (used[i]) continue;
		int help_sz = sz[i];
		if (help_sz > sz[u])
			help_sz = size - sz[u];
		solve(i, help_sz);
	}
}

void read() {
	cin >> n;
	for (int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	for (int i = 0; i < n; i++)
		cin >> lett[i];
	dfs(0, 0);
}

void run() {
	good_nums.insert(0);
	for (int i = 0; i < 20; i++)
		good_nums.insert(1 << i);
	solve(0, n);
	dfs_ans(0, 0);
}

void write() {
	for (int i = 0; i < n; i++) 
	cout << ans[i] - diff[i] / 2 + 1 << " ";
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