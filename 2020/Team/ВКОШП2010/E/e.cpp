#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

int n, m;
const int MAXN = 50;
char table[MAXN][MAXN];

struct pt{
	int x, y;
};

struct event{
	pt a, b;
};

bool operator==(const pt & a, const pt & b) {
	return tie(a.x, a.y) == tie(b.x, b.y);
}

const int INF = 1e9;
int dp[MAXN][MAXN][MAXN][MAXN];

deque<event> q;
pt s, f;

bool check(pt a) {
	return a.x >= 0 && a.x < n && a.y >= 0 && a.y < m && table[a.x][a.y] != '#';
}

void recalc(event v, int d) {
	if (!check(v.a) || !check(v.b)) return;
	if (dp[v.a.x][v.a.y][v.b.x][v.b.y] != INF) return;
	dp[v.a.x][v.a.y][v.b.x][v.b.y] = d;
	q.push_back(v);
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	freopen("parking.in", "r", stdin);
	freopen("parking.out", "w", stdout);
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> table[i][j];
			if (table[i][j] == 'X')
				s = {i, j};
			if (table[i][j] == '.')
				f = {i, j};
		}
	}

	for (int i0 = 0; i0 < MAXN; i0++)
		for (int i1 = 0; i1 < MAXN; i1++)
			for (int i2 = 0; i2 < MAXN; i2++)
				for (int i3 = 0; i3 < MAXN; i3++)
					dp[i0][i1][i2][i3] = INF;
	
	dp[s.x][s.y][f.x][f.y] = 0;
	q.push_back({s, f});
	vector<int> dx = {-1, 0, 1, 0};
	vector<int> dy = {0, 1, 0, -1};

	while (!q.empty()) {
		auto v = q[0];
		q.pop_front();
		for (int i = 0; i < 4; i++) {
			auto u = v;
			u.b.x += dx[i];
			u.b.y += dy[i];
			if (u.a == u.b) {
				u = v;
				swap(u.a, u.b);
				recalc(u, dp[v.a.x][v.a.y][v.b.x][v.b.y] + 1);
				continue;
			}
			recalc(u, dp[v.a.x][v.a.y][v.b.x][v.b.y] + 1);
		}

	}

	int ans = INF;
	for (int i2 = 0; i2 < MAXN; i2++)
		for (int i3 = 0; i3 < MAXN; i3++) {
			ans = min(ans, dp[f.x][f.y][i2][i3]);
		}
	if (ans == INF) {
		cout << "Impossible";
	}
	else {
		cout << ans;
	}
	return 0;
}