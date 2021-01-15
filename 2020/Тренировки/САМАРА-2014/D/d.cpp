#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()
#define x first
#define y second

int n, m, v;
const int MAXN = 1e3 + 10;
int dp[MAXN][MAXN];
vector<int> dx = {0, 1, 0, -1}, dy = {1, 0, -1, 0};

bool check(int x, int y) {
	return x >= 0 && x < n && y >= 0 && y < m;
}

char a[MAXN][MAXN];

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n >> m >> v;
	pair<int, int> s, f;
	cin >> s.x >> s.y >> f.x >> f.y;
	s.x--, s.y--, f.x--, f.y--;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> a[i][j];
		}
	}

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			dp[i][j] = v + 1;

	dp[s.x][s.y] = 0;
	queue<pair<int, int>> q;
	q.push(s);
	while (!q.empty()) {
		auto x = q.front();
		q.pop();
		if (dp[x.x][x.y] == v) continue;
		for (int it = 0; it < 4; it++) {
			int nx = x.x + dx[it], ny = x.y + dy[it];
			if (!check(nx, ny)) continue;
			int nd = dp[x.x][x.y] + 1;
			if (a[nx][ny] == 'F') nd = 0;
			if (dp[nx][ny] <= nd) continue;
			dp[nx][ny] = nd;
			q.push({nx, ny});
		}
	}
	if (dp[f.x][f.y] <= v) {
		cout << "Hello, Deimos!\n";
	} else {
		cout << "Dire victory\n";
	}
	return 0;
}