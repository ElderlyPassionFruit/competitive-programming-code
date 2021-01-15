#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

struct edge{
	int to, cost;
	edge() {}
	edge(int _to, int _cost) {
		to = _to, cost = _cost;
	}
};

const int MAXN = 1e5 + 10;
vector<edge> g[MAXN];
int n, m;

vector<bool> get(int start, int cost) {
	vector<bool> used(n, false);
	used[start] = true;
	queue<int> q;
	q.push(start);
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		for (auto [to, my_cost] : g[v]) {
			if (used[to]) continue;
			if (my_cost > cost) continue;
			used[to] = true;
			q.push(to);
		}
	}
	return used;
}

bool check(int cost) {
	vector<bool> L = get(0, cost);
	vector<bool> R = get(n - 1, cost);
	for (int i = 0; i < n; i++) {
		if (!L[i]) continue;
		if (R[i]) return true;
		for (auto [to, my_cost] : g[i]) {
			if (!R[to]) continue;
			return true;
		}
	}
	return false;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		a--;
		b--;
		g[a].push_back({b, c});
		g[b].push_back({a, c});
	}

	int l = -1, r = 1e9 + 228;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (check(mid)) {
			r = mid;
		} else {
			l = mid;
		}
	}
	if (r > 1e9 + 200) r = -1;
	cout << r << endl;
	return 0;
}