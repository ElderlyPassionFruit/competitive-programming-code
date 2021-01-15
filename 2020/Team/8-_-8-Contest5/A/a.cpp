#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()
#define y1 y1228

const int N = 310;
int dp[N][N][N];
int w, h;
int n;
int x1[N], x2[N], y1[N], y2[N];

struct Event{
	int x, y, t;
};

queue<Event> q;

void relax(int x, int y, int t, int it) {
	if (dp[x][y][t]) return;
	dp[x][y][t] = it + 1;
	if (t + 1 < n) q.push({x, y, t});
}

vector<int> dx = {0, 1, 0, -1};
vector<int> dy = {1, 0, -1, 0};

bool checkRect(int x, int y, int t) {
	return x1[t] <= x && x <= x2[t] && y1[t] <= y && y <= y2[t];
}

bool checkCell(int x, int y) {
	return x >= 1 && x <= w && y >= 1 && y <= h;
}

void bfs() {
	for (int x = 1; x <= w; x++) {
		for (int y = 1; y <= h; y++) {
			if (checkRect(x, y, 0)) continue;
			relax(x, y, 0, 10);
		}
	}
	while (!q.empty()) {
		//cout << "puhh" << endl;
		auto v = q.front();
		q.pop();
		for (int it = 0; it < 4; it++) {
			int nx = v.x + dx[it];
			int ny = v.y + dy[it];
			int nt = v.t + 1;
			if (!checkCell(nx, ny)) continue;
			if (checkRect(nx, ny, nt)) continue;
			relax(nx, ny, nt, it);
		}
	}

	/*for (int t = 0; t < n; t++) {
		for (int i = 1; i <= w; i++) {
			for (int j = 1; j <= h; j++) {
				cout << dp[i][j][t] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}*/
}

void makeAns() {
	int x = -1, y = -1;
	for (int i = 1; i <= w; i++) {
		for (int j = 1; j <= h; j++) {
			if (dp[i][j][n - 1]) {
				x = i, y = j;
			}
		}
	}
	if (x == -1 && y == -1) {
		cout << "Impossible\n";
		exit(0);
	}
	vector<pair<int, int>> ans;
	for (int t = n - 1; t >= 0; t--) {
		ans.push_back({x, y});
		if (t == 0) break;
		int it = dp[x][y][t] - 1;
		x -= dx[it];
		y -= dy[it];
	}
	reverse(all(ans));
	for (auto i : ans) {
		cout << i.first << " " << i.second << "\n";
	}
}

signed main() {
	freopen("broadcast.in", "r", stdin);
	freopen("broadcast.out", "w", stdout);
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> w >> h;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> x1[i] >> y1[i] >> x2[i] >> y2[i];
	}
	bfs();
	makeAns();
	return 0;
}