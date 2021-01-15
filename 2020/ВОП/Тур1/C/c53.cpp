#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(), (x).end()
template <typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

struct pt{
	int x, y;
	pt() {}
	pt(int _x, int _y) {
		x = _x, y = _y;
	}
};

const int MAXN = 110;
int k, c, t;
vector<pt> a;
bool used[MAXN][MAXN];

void read() {
	cin >> k >> c >> t;
	if (k == 1 && c == 0) {
		cout << (ll) t * t + (ll) (t + 1) * (t + 1) << endl;
		exit(0);
	}
	a.resize(k);
	for (auto &i : a) {
		cin >> i.x >> i.y;
		i.x++;
		i.y++;
	}
	while (c--) {
		pt x;
		cin >> x.x >> x.y;
		x.x++;
		x.y++;
		used[x.x][x.y] = true;
	}
}

vector<int> dx = {0, 1, 0, -1}, dy = {1, 0, -1, 0};

int dist[MAXN][MAXN];
const int INF = 1e9 + 10;

bool check(int x, int y) {
	return x >= 0 && x < MAXN && y >= 0 && y < MAXN;
}

void bfs() {
	for (int i = 0; i < MAXN; i++) {
		for (int j = 0; j < MAXN; j++) {
			dist[i][j] = INF;
		}
	}
	queue<pt> q;
	for (auto [x, y] : a) {
		dist[x][y] = 0;
		q.push({x, y});
	}
	while (!q.empty()) {
		pt v = q.front();
		q.pop();
		for (int it = 0; it < 4; it++) {
			int nx = v.x + dx[it];
			int ny = v.y + dy[it];
			if (!check(nx, ny)) continue;
			if (dist[nx][ny] != INF) continue;
			if (used[nx][ny]) continue;
			dist[nx][ny] = dist[v.x][v.y] + 1;
			q.push({nx, ny});
		}
	} 
}

ll ans;

void calc_ans() {
	ans = 0;
	for (int i = 0; i < MAXN; i++) {
		for (int j = 0; j < MAXN; j++) {
			if (dist[i][j] > t) continue;
			ans++;
			int add = 0;
			if (i == 0 || i == MAXN - 1) {
				ans += t - dist[i][j];
				add += t - dist[i][j];
			}
			if (j == 0 || j == MAXN - 1) {
				ans += t - dist[i][j];
				add += t - dist[i][j];
			}
			if ((i == 0 || i == MAXN - 1) && (j == 0 || j == MAXN - 1)) {
				ll delta = t - dist[i][j];
				delta -= 1;
				if (delta > 0) {
					ans += delta * (delta + 1) / 2;
					add += delta * (delta + 1) / 2;
				}
			}
		}
	}
}

void run() {
	bfs();
	calc_ans();	
}

void write() {
	cout << ans << endl;
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.setf(ios::fixed), cout.precision(20);
    read();
    run();
    write();
    return 0;
}