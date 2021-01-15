#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 1e5 + 10;
vector<int> g[MAXN];
int n, m, q;

void read() {
	cin >> n >> m >> q;
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v; 
		u--;
		v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
}

const int BUBEN = 150;

int dist[MAXN];

mt19937 rnd(time(0));

void build(int x) {
	for (int j = 0; j < n; j++)
		dist[j] = -1;

	queue<int> q;
	q.push(x);
	dist[x] = 0;
	while (!q.empty()) {
		x = q.front();
		q.pop();
		for (auto i : g[x]) {
			if (dist[i] != -1) continue;
			dist[i] = dist[x] + 1;
			q.push(i);
		}
	}
}

const int MAXQ = 2e5 + 10;

int ans[MAXQ], query[MAXQ][2];

void solve(int x) {
	build(x);
	for (int i = 0; i < q; i++) {
		chkmin(ans[i], dist[query[i][0]] + dist[query[i][1]]);
	}
}

int get() {
	return rnd() % n;
}

void run() {
	for (int i = 0; i < q; i++) {
		ans[i] = n + 1;
		cin >> query[i][0] >> query[i][1];
		query[i][0]--;
		query[i][1]--;
	}
	for (int i = 0; i < BUBEN; i++) {
		int x = get();
		solve(x);
	}
}

void write() {
	for (int i = 0; i < q; i++)
		cout << ans[i] << '\n';
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