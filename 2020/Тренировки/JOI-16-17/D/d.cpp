#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
#define int ll
struct pt{
	int x, y;
	pt() {}
	pt(int _x, int _y) {
		x = _x, y = _y;
	}
};

bool operator<(const pt & a, const pt & b) {
	return tie(a.x, a.y) < tie(b.x, b.y);
}

const int MAXK = 510, MAXN = 1e5 + 10;
pt p[MAXN];
int n;
int w, h;
int a, b, c;

pt s;

void read() {
	cin >> h >> w;
	cin >> a >> b >> c;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> p[i].x >> p[i].y;
	}
	s = p[0];
}

const ll INF = 1e18;
ll d[MAXK][MAXK];
vector<int> dx = {-1, 0, 1, 0};
vector<int> dy = {0, 1, 0, -1};

bool check(int x, int y) {
	return x >= 0 && x <= h && y >= 0 && y <= w;
}

void build () {
	for (int i = 0; i <= h; i++) {
		for (int j = 0; j <= w; j++) {
			d[i][j] = INF;
		}
	}

	queue<pt> q;
	for (int i = 0; i < n; i++) {
		d[p[i].x][p[i].y] = 0;
		q.push(p[i]);
	}
	while (!q.empty()) {
		auto v = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			int nx = v.x + dx[i];
			int ny = v.y + dy[i];
			if (!check(nx, ny)) continue;
			if (d[nx][ny] != INF) continue;
			d[nx][ny] = d[v.x][v.y] + 1;
			q.push({nx, ny});
		}
	}
}

struct event{
	pt a;
	ll dist;
	int type;
	event() {}
	event(pt _a, ll _dist, int _type) {
		a = _a, dist = _dist, type = _type;
	}
};

bool operator<(const event & a, const event & b) {
	return tie(a.dist, a.type, a.a) < tie(b.dist, b.type, b.a);
}

ll dp[MAXK][MAXK][5];

void calc() {
	for (int i = 0; i <= h; i++)
		for (int j = 0; j <= w; j++)
			for (int k = 0; k <= 4; k++)
				dp[i][j][k] = INF;

	dp[s.x][s.y][4] = d[s.x][s.y];
	set<event> q;
	q.insert({s, d[s.x][s.y], 4});
	
	while (!q.empty()) {
		auto v = *q.begin();
		int x = v.a.x;
		int y = v.a.y;
		int dist = v.dist;
		int type = v.type;
		q.erase(q.begin());
		if (type == 4) {
			for (int i = 0; i < 4; i++) {
				int nx = x + dx[i], ny = y + dy[i];
				if (!check(nx, ny)) continue;
				if (dp[nx][ny][4] <= dist + c) continue;
				q.erase({{nx, ny}, dp[nx][ny][4], 4});
				dp[nx][ny][4] = dist + c;
				q.insert({{nx, ny}, dp[nx][ny][4], 4});
			}
			for (int i = 0; i < 4; i++) {
				if (dp[x][y][i] <= dist + b) continue;
				q.erase({{x, y}, dp[x][y][i], i});
				dp[x][y][i] = dist + b;
				q.insert({{x, y}, dp[x][y][i], i});
			}
		}
		else {
			if (dp[x][y][4] > dist + d[x][y] * c) {
				q.erase({{x, y}, dp[x][y][4], 4});
				dp[x][y][4] = dist + d[x][y] * c;
				q.insert({{x, y}, dp[x][y][4], 4});
			} 
			int nx = x + dx[type], ny = y + dy[type];
			if (!check(nx, ny)) continue;
			if (dp[nx][ny][type] <= dist + a) continue;
			q.erase({{nx, ny}, dp[nx][ny][type], type});
			dp[nx][ny][type] = dist + a;
			q.insert({{nx, ny}, dp[nx][ny][type], type});
		}
	}
}

ll ans;

void make_ans() {
	ans = dp[p[n - 1].x][p[n - 1].y][4];
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