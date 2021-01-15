#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 2e3 + 10;
int n, m;
char table[MAXN][MAXN];

void read() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> table[i][j];
		}
	}
}

struct pt{
	int x, y;
	pt() {}
	pt(int _x, int _y) {
		x = _x, y = _y;
	}
};

bool operator==(const pt & a, const pt & b) {
	return tie(a.x, a.y) == tie(b.x, b.y);
}

pt par[MAXN][MAXN][2];
int min_val[MAXN][MAXN][2], max_val[MAXN][MAXN][2];

void make() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			for (int k = 0; k < 2; k++) {
				par[i][j][k] = {i, j};
			}
			min_val[i][j][0] = i;
			min_val[i][j][1] = j;
			max_val[i][j][0] = i;
			max_val[i][j][1] = j;
		}
	}
}

pt get_par(pt v, int type){
	if (par[v.x][v.y][type] == v) return v;
	return par[v.x][v.y][type] = get_par(par[v.x][v.y][type], type);
}

void uni(pt a, pt b, int type) {
	a = get_par(a, type);
	b = get_par(b, type);
	if (a == b) return;
	par[b.x][b.y][type] = a;
	chkmin(min_val[a.x][a.y][type], min_val[b.x][b.y][type]);
	chkmax(max_val[a.x][a.y][type], max_val[b.x][b.y][type]);
}

vector<int> dx = {-1, 0, 1, 0}, dy = {0, 1, 0, -1};

bool check(int x, int y) {
	return x >= 1 && x <= n && y >= 1 && y <= m;
}

bool check_del(int x, int y) {
	if (!check(x, y)) return false;
	if (table[x][y] == '.') return false;
	if (table[x][y] == 'N') {
		if (x == 1) return true;
		if (table[x - 1][y] != '.') return false;
		pt p = get_par({x - 1, y}, 0);
		return min_val[p.x][p.y][0] == 1;
	}
	else if (table[x][y] == 'S') {
		if (x == n) return true;
		if (table[x + 1][y] != '.') return false;
		pt p = get_par({x + 1, y}, 0);
		return max_val[p.x][p.y][0] == n;
	}
	else if (table[x][y] == 'W') {
		if (y == 1) return true;
		if (table[x][y - 1] != '.') return false;
		pt p = get_par({x, y - 1}, 1);
		return min_val[p.x][p.y][1] == 1;
	}
	else {
		if (y == m) return true;
		if (table[x][y + 1] != '.') return false;
		pt p = get_par({x, y + 1}, 1);
		return max_val[p.x][p.y][1] == m;
	}
}

queue<pt> q;

void build() {
	make();
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (table[i][j] != '.') continue;
			for (int k = 0; k < 4; k++) {
				int nx = i + dx[k];
				int ny = j + dy[k];
				if (!check(nx, ny)) continue;
				if (table[nx][ny] != '.') continue;
				uni({i, j}, {nx, ny}, k % 2);
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (check_del(i, j)) {
				q.push({i, j});
				table[i][j] = '.';
			}
		}
	}
}

int ans;

void solve() {
	ans = 0;
	while (!q.empty()) {
		pt v = q.front();
		ans++;
		q.pop();
		for (int k = 0; k < 4; k++) {
			int nx = v.x + dx[k];
			int ny = v.y + dy[k];
			if (!check(nx, ny)) continue;
			if (table[nx][ny] != '.') continue;				
			uni(v, {nx, ny}, k % 2);			
		}
		pt p;
		int nx, ny;
		p = get_par(v, 0);
		nx = min_val[p.x][p.y][0] - 1, ny = v.y;
		if (check_del(nx, ny)) {
			q.push({nx, ny});
			table[nx][ny] = '.';
		}
		nx = max_val[p.x][p.y][0] + 1;
		if (check_del(nx, ny)) {
			q.push({nx, ny});
			table[nx][ny] = '.';
		}
		p = get_par(v, 1);
		nx = v.x, ny = min_val[p.x][p.y][1] - 1;
		if (check_del(nx, ny)) {
			q.push({nx, ny});
			table[nx][ny] = '.';
		}
		ny = max_val[p.x][p.y][1] + 1;
		if (check_del(nx, ny)) {
			q.push({nx, ny});
			table[nx][ny] = '.';
		}
	}
}

void run() {
	build();
	solve();
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