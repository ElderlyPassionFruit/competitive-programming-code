#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()
#define ceil ceil228
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 1e3 + 10;

int n, m;
char table[MAXN][MAXN];

void read() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> table[i][j];
		}
	}
}

int color[MAXN][MAXN];
vector<int> dx = {1, 0, -1, 0};
vector<int> dy = {0, 1, 0, -1};

bool check(int x, int y) {
	return x >= 0 && x < n && y >= 0 && y < m;
}

int get_type(int x, int y) {
	if (table[x][y] == '?') return 0;
	if (table[x][y] == '+') return 0;
	if (table[x][y] == '#') return 1;
	return 2;
}

vector<pair<int, int>> ceil[MAXN * MAXN];

void paint(int x, int y, int type, int c) {
	color[x][y] = c;
	if (type == 2) {
		ceil[c].push_back({x, y});
	}
	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (!check(nx, ny)) continue;
		if (color[nx][ny]) continue;
		if (type != get_type(nx, ny)) continue;
		paint(nx, ny, type, c);
	}
}

int cnt[2];
int have[MAXN * MAXN][5];

int get_name(int x, int y) {
	if (table[x][y] == 'R') return 1;
	if (table[x][y] == 'Y') return 2;
	if (table[x][y] == 'G') return 3;
	if (table[x][y] == 'B') return 4;
	if (table[x][y] == 'K') return 5;
	return 0; 
}


void build() {
	cnt[0] = cnt[1] = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (color[i][j]) continue;
			int type = get_type(i, j);
			if (!type) continue;
			cnt[type - 1]++;
			paint(i, j, type, cnt[type - 1]);
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int name = get_name(i, j);
			if (!name) continue;
			have[color[i][j]][name - 1]++;
		}
	}
}

int used[MAXN * MAXN];

int points[5];

void calc() {
	fill(used, used + MAXN * MAXN, false);
	for (int i = 1; i <= cnt[1]; i++) {
		int fans = 0;
		for (auto [x, y] : ceil[i]) {
			for (int it = 0; it < 4; it++) {
				int nx = x + dx[it];
				int ny = y + dy[it];
				if (!check(nx, ny)) continue;
				if (get_type(nx, ny) != 1) continue;
				int ind = color[nx][ny];
				fans += used[ind] != i;
				used[ind] = i;
			}
		}

		int need = 0;
		for (int it = 0; it < 5; it++) {
			chkmax(need, have[i][it]);
		}
		if (!need) continue;
		for (int it = 0; it < 5; it++) {
			if (have[i][it] < need) continue;
			points[it] += fans;
		}
	}
}

void run() {
	build();
	calc();
}

void write() {
	int need = 0;
	for (int it = 0; it < 5; it++) {
		chkmax(need, points[it]);
	}
	cout << need * 3 << endl;
	vector<char> fans = {'R', 'Y', 'G', 'B', 'K'};
	for (int it = 0; it < 5; it++) {
		if (points[it] < need) continue;
		cout << fans[it] << " ";
	}
	cout << endl;
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