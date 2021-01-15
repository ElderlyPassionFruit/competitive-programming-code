#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 2e5 + 10;
vector<int> g[MAXN];
vector<int> c[MAXN];
int n;

void read() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		x--;
		c[x].push_back(i);
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

int tin[MAXN], timer = 0;
int tout[MAXN];

int sz[MAXN];

const int MAXLOG = 20;
int dp[MAXN][MAXLOG];
ll help_sum[MAXN];


ll get(int n) {
	if (n < 0) return 0;
	return (ll)n * (n - 1) / 2 + n;
}


void dfs(int v, int p) {
	tin[v] = timer++;
	sz[v] = 1;
	dp[v][0] = p;
	for (int i = 1; i < MAXLOG; i++)
		dp[v][i] = dp[dp[v][i - 1]][i - 1];
	for (auto i : g[v]) {
		if (i == p) continue;
		dfs(i, v);
		help_sum[v] += get(sz[i]);
		sz[v] += sz[i];
	}
	tout[v] = timer;
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

int pre_lca(int p, int v) {
	for (int i = MAXLOG - 1; i >= 0; i--)
		if (!is_upper(dp[v][i], p))
			v = dp[v][i];
	return v;
}

ll ans[MAXN];

vector<int> get_all_vert(vector<int> & v) {
	sort(all(v), [&] (int a, int b) {return tin[a] < tin[b];});
	v.resize(unique(all(v)) - v.begin());
	vector<int> have = v;
	int n = v.size();
	for (int i = 0; i < n - 1; i++) {
		have.push_back(lca(have[i], have[i + 1]));
	}
	sort(all(have), [&] (int a, int b) {return tin[a] < tin[b];});
	have.resize(unique(all(have)) - have.begin());
	return have;
}

vector<int> tree[MAXN];

void build_tree(vector<int> & have) {
	int n = have.size();
	for (int i = 0; i < n; i++)
		tree[i].clear();
	vector<pair<int, int>> st; 
	for (int i = 0; i < n; i++) {
		while (!st.empty() && !is_upper(st.back().first, have[i]))
			st.pop_back();
		if (!st.empty()) {
			tree[st.back().second].push_back(i);
		}
		st.push_back({have[i], i});
	}
}

bool cmp(int a, int b) {
	return tin[a] < tin[b];
}

int dfs_calc(int v, vector<int> & have, vector<int> & good, ll & fans) {
	bool flag = false;
	int pos = lower_bound(all(good), have[v], cmp) - good.begin();
	if (pos >= 0 && pos < (int)good.size() && good[pos] == have[v]) {
		flag = true;
	} 
	int cnt = 0;
	if (flag) {
		cnt = sz[have[v]];
	}

	ll other = help_sum[have[v]];

	for (auto i : tree[v]) {
		int now = dfs_calc(i, have, good, fans);
		if (flag) {
			int real_i = pre_lca(have[v], have[i]);
			ll x = get(sz[real_i] - now);
			fans += x;
			other -= get(sz[real_i]);
		} else {
			cnt += now;
		}
	}
	if (flag) {
		fans += other;
	}
	return cnt;
}

ll calc(vector<int> & v) {
	if (v.empty()) return get(n);
	vector<int> have = get_all_vert(v);
	build_tree(have);
	ll ans = 0;
	int now = dfs_calc(0, have, v, ans);
	ans += get(sz[0] - now);
	return ans;
} 

void run() {
	dfs(0, 0);
	for (int i = 0; i < n; i++) {
		ans[i] = get(n) - calc(c[i]);
	}
}

void write() {
	for (int i = 0; i < n; i++)
		cout << ans[i] << "\n";
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
