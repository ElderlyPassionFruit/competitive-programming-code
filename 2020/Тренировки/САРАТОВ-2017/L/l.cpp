#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int MAXN = 3e5 + 10;
const ll INF = 1e18;

int n, m;
vector<pair<int, int>> g[MAXN];
ll ans[MAXN];


void no() {
	cout << "NO\n";
	exit(0);
}

void dfs(int v) {
	queue<int> q;
	q.push(v);
	while (!q.empty()) {
		v = q.front();
		q.pop();
		for (auto [to, cost] : g[v]) {
			if (ans[to] == ans[v] + cost) continue;
			if (ans[to] == INF) {
				ans[to] = ans[v] + cost;
				q.push(to);
			} else {
				no();
			}
		}
	}
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int l, r, x;
		cin >> l >> r >> x;
		g[l - 1].push_back({r, x});
		g[r].push_back({l - 1, -x});
	}
	fill(ans, ans + MAXN, INF);
	for (int i = 0; i <= n; i++) {
		if (ans[i] != INF) continue;
		ans[i] = 0;
		dfs(i);
	}
	for (int i = n; i >= 1; i--) {
		ans[i] -= ans[i - 1];
	}
	cout << "YES\n";
	for (int i = 1; i <= n; i++) {
		cout << ans[i] << " ";
	}
	cout << "\n";
	return 0;
}