#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int MAXN = 1e4 + 10;
int n, m;
vector<int> g[MAXN], gr[MAXN];

vector<int> order;
bool used[MAXN];

void dfs(int v) {
	used[v] = true;
	for (auto i : g[v]) {
		if (!used[i]) {
			dfs(i);
		}
	}
	order.push_back(v);
}

int sz = 0;

void dfs_ans(int v) {
	used[v] = true;
	sz++;
	for (auto i : gr[v]) {
		if (!used[i]) {
			dfs_ans(i);
		}
	}
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int v, u;
		cin >> v >> u;
		v--;
		u--;
		g[v].push_back(u);
		gr[u].push_back(v);
	}
	for (int i = 0; i < n; i++) {
		if (!used[i]) {
			dfs(i);
		}
	}
	reverse(all(order));
	fill(used, used + n, false);
	int ans = 0;
	for (auto i : order) {
		if (!used[i]) {
			sz = 0;
			dfs_ans(i);
			ans += min(2, sz);
		}
	}
	cout << ans << endl;
	return 0;
}