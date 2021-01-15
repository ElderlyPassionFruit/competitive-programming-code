#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()
#define int ll

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct pt{
	int x, y;
	pt() {}
	pt(int a, int b) {
		x = a, y = b;
	}
};

bool operator<(const pt & a, const pt & b) {
	return tie(a.x, a.y) < tie(b.x, b.y);
}

struct event{
	int dist, dir;
	pt a;
	event(int x, int y, pt z) {
		dist = x, dir = y, a = z;
	}
};

bool operator<(const event & a, const event & b) {
	return tie(a.dist, a.dir, a.a) < tie(b.dist, b.dir, b.a);
}

const int MAXN = 510;
char table[MAXN][MAXN];
int n, m;
pt s, f;

void read() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> table[i][j];
			if (table[i][j] == 'S')
				s = {i, j};
			if (table[i][j] == 'F')
				f = {i, j};
		}
	}
}

pt Next[MAXN][MAXN][4];

void build_up() {
	for (int j = 0; j < m; j++) {
		Next[0][j][0] = {-1, -1};
		for (int i = 1; i < n; i++) {
			Next[i][j][0] = Next[i - 1][j][0];
			if (table[i - 1][j] == '#') 
				Next[i][j][0] = {i, j};
			if (table[i][j] == 'X' || table[i][j] == '#')
				Next[i][j][0] = {-1, -1};
		}
	}
}

void build_down() {
	for (int j = 0; j < m; j++) {
		Next[n - 1][j][2] = {-1, -1};
		for (int i = n - 2; i >= 0; i--) {
			Next[i][j][2] = Next[i + 1][j][2];
			if (table[i + 1][j] == '#') Next[i][j][2] = {i, j};
			if (table[i][j] == 'X' || table[i][j] == '#')
				Next[i][j][2] = {-1, -1};
		}
	}
}

void build_left() {
	for (int i = 0; i < n; i++) {
		Next[i][0][3] = {-1, -1};
		for (int j = 1; j < m; j++) {
			Next[i][j][3] = Next[i][j - 1][3];
			if (table[i][j - 1] == '#') Next[i][j][3] = {i, j};
			if (table[i][j] == 'X' || table[i][j] == '#') 
				Next[i][j][3] = {-1, -1};
		}
	}
}

void build_right() {
	for (int i = 0; i < n; i++) {
		Next[i][m - 1][1] = {-1, -1};
		for (int j = m - 2; j >= 1; j--) {
			Next[i][j][1] = Next[i][j + 1][1];
			if (table[i][j + 1] == '#') Next[i][j][1] = {i, j};
			if (table[i][j] == 'X' || table[i][j] == '#') 
				Next[i][j][1] = {-1, -1};
		}
	}
}

void build() {
	build_up();
	build_down();
	build_left();
	build_right();
}

const int INF = 1e9;
int ans;
int dp[MAXN][MAXN][4];

set<event> q;
vector<int> dx = {-1, 0, 1, 0};
vector<int> dy = {0, 1, 0, -1};

bool check(pt a) {
	return a.x >= 0 && a.x < n && a.y >= 0 && a.y < m && 
	table[a.x][a.y] != 'X' && table[a.x][a.y] != '#';
}

void recalc(int dist, int dir, pt a) {
	if (!check(a)) return;
	if (dp[a.x][a.y][dir] <= dist) return;
	q.erase({dp[a.x][a.y][dir], dir, a});
	dp[a.x][a.y][dir] = dist;
	q.insert({dp[a.x][a.y][dir], dir, a});
}

int get_dist(pt a, pt b) {
	return abs(a.x - b.x) + abs(a.y - b.y);
}

void calc() {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			for (int k = 0; k < 4; k++)
				dp[i][j][k] = INF;
	for (int k = 0; k < 4; k++) {
		dp[s.x][s.y][k] = 0;
		q.insert({0, k, s});
	}

	while (!q.empty()) {
		auto x = *q.begin();
		q.erase(q.begin());
		pt a = x.a;
		int dist = x.dist;
		int dir = x.dir;
		recalc(dist + 1, dir, {a.x + dx[dir], a.y + dy[dir]});
		if (!check(Next[a.x][a.y][dir])) continue;

		pt b = Next[a.x][a.y][dir];
		if (table[b.x + dx[dir]][b.y + dy[dir]] != '#') continue;
		
		dist += get_dist(a, b) + 1;

		for (int k = 0; k < 4; k++) {
			if (dir == k) continue;
			if (!check(Next[a.x][a.y][k])) continue;
			recalc(dist, k ^ 2, Next[a.x][a.y][k]);
		}
	}
}

void make_ans() {
	ans = INF;
	for (int k = 0; k < 4; k++)
		chkmin(ans, dp[f.x][f.y][k]);
	if (ans == INF) ans = -1;
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