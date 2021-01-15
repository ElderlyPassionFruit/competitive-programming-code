#include <bits/stdc++.h>

using namespace std;
#define int long long
const int MAXN = 2 * 1e4 + 10;
int n, m, k, q;
vector <pair <int, int> > g[MAXN];
vector <int> hubs;
void read() {
	cin >> n >> m >> k >> q;
	for (int i = 0; i < m; i++) {
		int u, v, dist;
		cin >> u >> v >> dist;
		u--;
		v--;
		g[u].push_back({v, dist});
	}
	for (int i = 0; i < k; i++) {
		int a;
		cin >> a;
		a--;
		hubs.push_back(a);
	}
	sort(hubs.begin(), hubs.end());
}
const int INF = 1e18;
int solve(int a, int b) {
	vector <int> dist(n, INF);
	dist[a] = 0;
	set <pair <int, int> > q;
	q.insert({0, a});
	while (!q.empty()) {
		auto p = *q.begin();
		q.erase(q.begin());
		int v = p.second;
		int d = p.first;
		for (auto i : g[v]) {
			if (dist[i.first] > d + i.second) {
				q.erase({dist[i.first], i.first});
				dist[i.first] = i.second + d;
				q.insert({dist[i.first], i.first});
			}
		}
	}
	return dist[b];
}

int cnt, sum;
void run() {
	cnt = 0;
	sum = 0;
	for (int i = 0; i < q; i++) {
		int a, b;
		cin >> a >> b;
		a--;
		b--;
		int fans = solve(a, b);
		if (fans != INF)
			cnt++, sum += fans;
	}
}

void write() {
	cout << cnt << endl;
	cout << sum << endl;
}


signed main() {

	freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}