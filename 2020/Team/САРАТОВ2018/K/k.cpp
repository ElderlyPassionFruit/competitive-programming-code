#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,avx,avx2,mmx,tune=native,popcnt")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int MAXN = 2e5 + 10;
int dp[MAXN];
int sz[MAXN];
int n;
int ans = 1e9;
vector<int> g[MAXN];

void dfs_sz(int v, int p) {
	sz[v] = 1;
	for (auto i : g[v]) {
		if (i != p) {
			dfs_sz(i, v);
			sz[v] += sz[i];
		}
	}
}

void recalc(int x, int y, int z) {
	if (x < 0 || y < 0 || z < 0) return;
	int fans = 0;
	fans = max(fans, abs(x - y));
	fans = max(fans, abs(x - z));
	fans = max(fans, abs(z - y));
	ans = min(ans, fans);
}



set<int> calc_pred(int v, int p) {
	set<int> have;
	for (auto i : g[v]) {
		if (i != p) {
			auto x = calc_pred(i, v);
			if (x.size() > have.size())
				swap(x, have);
			for (auto j : x)
				have.insert(j);
		}
	}
	auto it = have.lower_bound((sz[v] + 1) / 2);
	if (it != have.end() && p != -1) {
		int x = n - sz[v];
		int y = *it;
		int z = sz[v] - *it;
		recalc(x, y, z);	
	}
	if (it != have.begin() && p != -1) {
		it--;
		int x = n - sz[v];
		int y = *it;
		int z = sz[v] - *it;
		recalc(x, y, z);
	}
	have.insert(sz[v]);
	return have;
}

set<int> calc_pred1(int v, int p) {
	set<int> have;
	for (auto i : g[v]) {
		if (i != p) {
			auto x = calc_pred(i, v);
			if (x.size() > have.size())
				swap(x, have);
			for (auto j : x)
				have.insert(j);
		}
	}
	auto it = have.lower_bound((n - sz[v] + 1) / 2);
	if (it != have.end() && p != -1) {
		int x = n - sz[v];
		int y = *it;
		int z = sz[v] - *it;
		recalc(x, y, z);	
	}
	if (it != have.begin() && p != -1) {
		it--;
		int x = n - sz[v];
		int y = *it;
		int z = sz[v] - *it;
		recalc(x, y, z);
	}
	have.insert(sz[v]);
	return have;
}

int K;

struct event{
	int min, max, v;
	event() {}
	event(int a, int b, int c) {
		min = a, max = b, v = c;
	}
};

bool operator<(const event & a, const event & b) {
	return min(K - a.min, a.max - K) < min(K - b.min, b.max - K);
}

const int It = 10;

event calc(int v, int p) {
	vector<event> help;
	for (auto i : g[v]) {
		if (i != p) {
			help.push_back(calc(i, v));
		}
	}
	sort(all(help));
	for (int i = 0; i < min(It, (int)help.size()); i++) {
		for (int j = i + 1; j < min(It, (int)help.size()); j++) {
			recalc(help[i].min, help[j].min, n - help[i].min - help[j].min);
			recalc(help[i].min, help[j].max, n - help[i].min - help[j].max);
			recalc(help[i].max, help[j].min, n - help[i].max - help[j].min);
			recalc(help[i].max, help[j].max, n - help[i].max - help[j].max);
		}
	}
	event ans = event(-1e9, 1e9, v);
	for (auto i : help) {
		ans.min = max(ans.min, i.min);
		ans.max = min(ans.max, i.max);
	}
	if (sz[v] < K) {
		ans.min = max(ans.min, sz[v]);
	}
	if (sz[v] >= K) {
		ans.max = min(ans.max, sz[v]);
	}
	return ans;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n;
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	int v = rand() % n;
	dfs_sz(v, v);
	calc_pred(v, -1);
	calc_pred1(v, -1);
	for (int i = max(0, n / 3 - 3); i < min(n / 3 + 3, n); i++) {
		K = i;
		calc(v, v);
	}
	for (int i = 0; i < 45; i++) {
		K = rand() % n + 1;
		calc(v, v);
	}
	cout << ans << endl;
	return 0;
}