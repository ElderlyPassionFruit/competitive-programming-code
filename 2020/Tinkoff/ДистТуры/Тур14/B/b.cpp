#include <bits/stdc++.h>

using namespace std;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct edge{
	int to, cost;
	edge() {}
	edge(int _to, int _cost) {
		to = _to;
		cost = _cost;
	}
};

const int MAXN = 1e5 + 10;
vector<edge> g[MAXN];
int n, t, k;

void read() {
	cin >> n >> t >> k;
	if (t == 0 && k == 0) {
		cout << "1 1" << endl;
		exit(0);
	}
	if (t == 0 || k == 0) {
		cout << "0 0" << endl;
		exit(0);
	}
	for (int i = 0; i < n - 1; i++) {
		int a, b, cost;
		cin >> a >> b >> cost;
		a--;
		b--;
		g[a].push_back({b, cost});
		g[b].push_back({a, cost});
	}
}

const int INF = 1e9;
pair<int, int> ans;

void relax(int a, int b) {
	if (a > b) swap(a, b);
	chkmin(ans, make_pair(a + 1, b + 1));
}

int sz[MAXN];
bool used[MAXN];
int centr;

void dfs_centroid(int v, int p, int size) {
	sz[v] = 1;
	int mx = 0;
	for (auto i : g[v]) {
		if (used[i.to]) continue;
		if (i.to == p) continue;
		dfs_centroid(i.to, v, size);
		chkmax(mx, sz[i.to]);
		sz[v] += sz[i.to];
	}
	chkmax(mx, size - sz[v]);
	if (mx <= size / 2) {
		centr = v;
	}
}

unordered_map<int, int> cnt[MAXN];

void dfs_add(int v, int p, int len, int cost, int add) {
	if (len > 0) {
		if (add == 1){
			if (cnt[len].find(cost) != cnt[k - len].end())
				chkmin(cnt[len][cost], v);
			else
				cnt[len][cost] = v;
		}
		else{
			cnt[len].erase(cost);
		}
	}
	for (auto i : g[v]) {
		if (i.to == p) continue;
		if (used[i.to]) continue;
		dfs_add(i.to, v, len + 1, cost + i.cost, add);
	}
}

void dfs_calc(int v, int p, int len, int cost) {
	if (len > k) return;
	if (cost > t) return;
	if (len == k && t == cost) {
		relax(centr, v);
	}
	if (cnt[k - len].find(t - cost) != cnt[k - len].end()) {
		relax(v, cnt[k - len][t - cost]);
	}
	for (auto i : g[v]) {
		if (used[i.to]) continue;
		if (i.to == p) continue;
		dfs_calc(i.to, v, len + 1, cost + i.cost);
	}
}

void solve(int v, int size) {
	dfs_centroid(v, -1, size);
	v = centr;
	used[v] = true;

	for (auto i : g[v]) {
		if (used[i.to]) continue;
		dfs_calc(i.to, v, 1, i.cost);
		dfs_add(i.to, v, 1, i.cost, 1);
	}
	dfs_add(v, v, 0, 0, -1);
	for (auto i : g[v]) {
		if (used[i.to]) continue;
		int fsz = sz[i.to];
		if (fsz > sz[v]) fsz = size - sz[v];
		solve(i.to, fsz);
	}
} 

void run() {
	ans = {INF, INF};
	solve(0, n);
	if (ans == make_pair(INF, INF))
		ans = {0, 0};
}

void write() {
	cout << ans.first << " " << ans.second << endl;
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