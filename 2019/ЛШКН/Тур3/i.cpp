#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 1000;

int n, m;
int a[MAXN], b[MAXN];
vector<pair<int, int> > ed;
void read() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	for (int i = 1; i <= n; i++) {
		cin >> b[i];
	}
	ed.resize(m);
	for (auto &i : ed)
		cin >> i.first >> i.second;
}


struct edge {
	int v, to, cap, flow;
};

int sz = 0;
edge Edge[MAXN * 4];
vector<int> g[MAXN];

void add(int v, int to, int cap) {
	Edge[sz] = {v, to, cap, 0};
	g[v].push_back(sz++);
	Edge[sz] = {to, v, 0, 0};
	g[to].push_back(sz++);
}

const int INF = 1e9;

int s, f;

void build() {
	s = 0, f = 2 * n + 1;
	for (int i = 1; i <= n; i++) {
		add(s, i, a[i]);
	}
	for (int i = 1; i <= n; i++) {
		add(i + n, f, b[i]);
	}
	for (auto i : ed) {
		add(i.first, i.second + n, INF);
		add(i.second, i.first + n, INF);
	}
	for (int i = 1; i <= n; i++) {
		add(i, i + n, INF);
	}
} 

int ans[MAXN][MAXN];

bool used[MAXN];

int dfs(int v, int flow) {
	if (v == f) 
		return flow;
	used[v] = true;
	for (auto u : g[v]) {
		auto vu = Edge[u];
		if (!used[vu.to] && vu.flow < vu.cap) {
			int df = dfs(vu.to, min(flow, vu.cap - vu.flow));
			if (df > 0) {
				Edge[u].flow += df;
				Edge[u ^ 1].flow -= df;
				return df;
			}
		}
	}
	return 0;
}

int flow() {
	int ans = 0;
	while (true) {
		for (int i = 0; i <= f; i++)
			used[i] = false;
		int x = dfs(s, INF);
		if (x == 0)
			return ans;
		ans += x;
	}
}

void run() {
	build();
	int have = flow();

	int sum_a = 0, sum_b = 0;
	for (int i = 1; i <= n; i++) {
		sum_a += a[i];
		sum_b += b[i];
	}

	if (sum_a != sum_b || sum_a != have || sum_b != have) {
		cout << "NO" << endl;
		exit(0);
	}

	for (int i = 0; i < sz; i += 2) {
		int v = Edge[i].v;
		int to = Edge[i].to;
		if (v == s || v == f || to == s || to == f)
			continue;
		to -= n;
		ans[v][to] += Edge[i].flow;
	}
}

void write() {
	cout << "YES" << endl;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cout << ans[i][j] << " ";
		}
		cout << endl;
	}
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