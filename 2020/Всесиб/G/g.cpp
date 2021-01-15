#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
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

const int MAXN = 310;
int n, m;
char table[MAXN][MAXN];
pt s;
int cost[6];
int dp[MAXN][MAXN][6];

void read() {
	cin >> n >> m >> s.x >> s.y; 
	s.x--, s.y--;
	for (int i = 0; i < 6; i++) {
		cin >> cost[i];
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			cin >> table[i][j];
}

const int INF = 1e9 + 10;

void build() {
	for (int i = 0; i < MAXN; i++)
		for (int j = 0; j < MAXN; j++)
			for (int k = 0; k < 6; k++)
				dp[i][j][k] = INF;
}

struct event{
	pt a;
	int type;
	int dist;
	event() {}
	event(pt _a, int _type, int _dist) {
		a = _a;
		type = _type;
		dist = _dist;
	}
};

bool operator<(const event & a, const event & b) {
	return tie(a.dist, a.type, a.a) < tie(b.dist, b.type, b.a);
}

bool check(pt a) {
	return a.x >= 0 && a.x < n && a.y >= 0 && a.y < m && table[a.x][a.y] == '.';
}

set<event> q;

void recalc(pt a, int type, int dist) {
	if (dp[a.x][a.y][type] <= dist) return;
	q.erase({a, type, dp[a.x][a.y][type]});
	dp[a.x][a.y][type] = dist;
	q.insert({a, type, dp[a.x][a.y][type]});
}

void recalc(pt a, int dx, int dy, int op, int type, int dist) {
	if (op < 0) return;
	if (!check(a)) return;
	recalc(a, type, dist);
	recalc({a.x - dx, a.y - dy}, dx, dy, op - 1, type, dist + 1);
}

struct frecalc{
	int dx, dy, op;
	frecalc() {}
	frecalc(int _dx, int _dy, int _op) {
		dx = _dx, dy = _dy, op = _op;
	}
};

vector<vector<frecalc> > D = {
	{{-1, 0, 1}, {1, 0, 1}, {0, -1, 1}, {0, 1, 1}},
	{{-1, -2, 1}, {-2, -1, 1}, {-2, 1, 1}, {-1, 2, 1}, {1, 2, 1}, {2, 1, 1}, {2, -1, 1}, {1, -2, 1}},
	{{-1, 0, INF}, {1, 0, INF}, {0, -1, INF}, {0, 1, INF}},
	{{-1, -1, INF}, {-1, 1, INF}, {1, -1, INF}, {1, 1, INF}},
	{{-1, 0, INF}, {1, 0, INF}, {0, -1, INF}, {0, 1, INF}, {-1, -1, INF}, {-1, 1, INF}, {1, -1, INF}, {1, 1, INF}},
	{{-1, 0, 1}, {1, 0, 1}, {0, -1, 1}, {0, 1, 1}, {-1, -1, 1}, {-1, 1, 1}, {1, -1, 1}, {1, 1, 1}}
};

void calc() {
	dp[s.x][s.y][0] = 0;
	q.insert({s, 0, 0});
	while (!q.empty()) {
		auto v = *q.begin();
		q.erase(q.begin());
		for (auto i : D[v.type]) {
			recalc(v.a, i.dx, i.dy, i.op, v.type, v.dist);
		}
		for (int i = 0; i < 6; i++) {
			recalc(v.a, i, v.dist + cost[i]);
		}
	}
}

pt ans;
int fans;

void make_ans() {
	fans = -1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (table[i][j] == '#') continue;
			int have = INF;
			for (int k = 0; k < 6; k++) {
				chkmin(have, dp[i][j][k]);
			}
			if (have > fans) {
				fans = have;
				ans = {i + 1, j + 1};
			}
		}
	}
}

void run() {
	build();
	calc();
	make_ans();
}

void write() {
	cout << ans.x << " " << ans.y << " ";
	if (fans == INF)
		cout << "INF" << endl;
	else
		cout << fans << endl;
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