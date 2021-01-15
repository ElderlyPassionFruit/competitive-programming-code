#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

#define int ll
const int MAXV = 100;
const int INF = 1e18;
int n, m, A, B;
string a[10];
ld dp[10][10][MAXV][4];
vector<int> dx = {1, 0, -1, 0}, dy = {0, 1, 0, -1};

struct state{
	int x, y, speed, dir;
	ld dist;
	state() {}
	state(int _x, int _y, int _speed, int _dir, ld _dist) {
		x = _x, y = _y, speed = _speed, dir = _dir, dist = _dist;
	}
};

bool operator<(const state & a, const state & b) {
	return tie(a.dist, a.x, a.y, a.dir, a.speed) < tie(b.dist, b.x, b.y, b.dir, b.speed);
}

bool checkCell(int x, int y) {
	return x >= 0 && x < n && y >= 0 && y < m && a[x][y] != 'C';
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n >> m >> A >> B;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			for (int k = 0; k < MAXV; k++) {
				for (int x = 0; x < 4; x++) {
					dp[i][j][k][x] = INF;
				}
 			}
		}
	}
	set<state> q;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (a[i][j] == 'V') {
				for (int dir = 0; dir < 4; dir++) {
					dp[i][j][1][dir] = 0;
					q.insert({i, j, 1, dir, 0});
				}
			}
		}
	}
	while (!q.empty()) {
		auto now = *q.begin();
		q.erase(q.begin());
		//cout <<  now.x << " " << now.y << " " << now.speed << " " << now.dir << " " << now.dist << endl;
		if (now.speed == 1) {
			for (int dir = 0; dir < 4; dir++) {
				int nx = now.x + dx[dir], ny = now.y + dy[dir];
				if (!checkCell(nx, ny)) continue;
				for (int speed = 1; speed <= A + 1; speed++) {
					ld cost = now.dist + 2.0 / (ld) (speed + 1);
					if (dp[nx][ny][speed][dir] <= cost) continue;
					q.erase({nx, ny, speed, dir, dp[nx][ny][speed][dir]});
					dp[nx][ny][speed][dir] = cost;
					q.insert({nx, ny, speed, dir, dp[nx][ny][speed][dir]});
				}
			}
		}
		int nx = now.x + dx[now.dir], ny = now.y + dy[now.dir];
		if (!checkCell(nx, ny)) continue;
		for (int speed = max(1LL, now.speed - B); speed <= min(MAXV - 1, now.speed + A); speed++) {
			ld cost = now.dist + 2.0 / (ld) (now.speed + speed);
			if (dp[nx][ny][speed][now.dir] <= cost) continue;
			q.erase({nx, ny, speed, now.dir, dp[nx][ny][speed][now.dir]});
			dp[nx][ny][speed][now.dir] = cost;
			q.insert({nx, ny, speed, now.dir, dp[nx][ny][speed][now.dir]});
		}
	} 

	ld ans = INF;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (a[i][j] != 'E') continue;
			for (int speed = 0; speed < MAXV; speed++) {
				for (int dir = 0; dir < 4; dir++) {
					ans = min(ans, dp[i][j][speed][dir]);
				//	cout << dp[i][j][speed][dir] << endl;
				}
			} 
		}
	}
	cout.precision(20);
	cout.setf(ios::fixed);
	if (ans == INF) {
		cout << -1 << endl;
	} else {
		cout << ans << endl;
	}
 	return 0;
}