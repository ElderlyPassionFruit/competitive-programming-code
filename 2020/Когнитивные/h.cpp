#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 31;

int table[MAXN][MAXN];
int n, m;

void read() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> table[i][j];
		}
	}
}

const int MAXLEN = MAXN * MAXN;

const int INF = 1e9 + 10;

int dp[MAXN][MAXN][MAXLEN];

void build() {
	for (int i = 0; i < MAXN; i++) {
		for (int j = 0; j < MAXN; j++) {
			for (int k = 0; k < MAXLEN; k++) {
				dp[i][j][k] = INF;
			}
		}
	}
	dp[0][0][0] = 0;
}

vector<int> dx = {-1, 0, 1, 0};
vector<int> dy = {0, 1, 0, -1};

struct event{
	int x, y, len, cost;
	event() {}
	event(int a, int b, int c, int d) {
		x = a, y = b, len = c, cost = d;
	}
};

bool operator<(const event & a, const event & b) {
	return tie(a.cost, a.len, a.x, a.y) < tie(b.cost, b.len, b.x, b.y);
}

bool check(int x, int y) {
	return x >= 0 && x < n && y >= 0 && y < m;
}

int get_cost(int len, int cost, int x, int y) {
	return cost + table[x][y] + 2 * len * table[x][y] + 1;
}

set<event> q;

void calc() {
	q.insert({0, 0, 0, 0});
	while (!q.empty()) {
		auto v = *q.begin();
		q.erase(q.begin());
		for (int i = 0; i < 4; i++) {
			int nx = v.x + dx[i];
			int ny = v.y + dy[i];
			if (!check(nx, ny)) continue;
			int nlen = v.len + 1;
			if (nlen > n * m) continue;
			int ncost = get_cost(v.len, v.cost, nx, ny);
			if (dp[nx][ny][nlen] <= ncost) continue;
			q.erase({nx, ny, nlen, dp[nx][ny][nlen]});
			dp[nx][ny][nlen] = ncost;
			q.insert({nx, ny, nlen, dp[nx][ny][nlen]});
		}
	}
}

int ans = INF;

void make_ans() {
	for (int i = 0; i < MAXLEN; i++) {
		if (dp[n - 1][m - 1][i] == INF) continue;
		chkmin(ans, dp[n - 1][m - 1][i] - i);
	}
}

void run() {
	build();
	calc();
	make_ans();
}

void write() {
	cout << ans << endl;
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