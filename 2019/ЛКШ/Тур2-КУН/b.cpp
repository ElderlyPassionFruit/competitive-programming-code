#include <bits/stdc++.h>

using namespace std;
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 310;
char table[MAXN][MAXN];
int a, b;
int n, m;

void read() {
	cin >> n >> m >> a >> b;
	for (int i = 0; i < MAXN; i++) {
		for (int j = 0; j < MAXN; j++) {
			table[i][j] = '.';
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> table[i][j];
		}
	}
}

pair <int, int> used[MAXN][MAXN], mt[MAXN][MAXN];

vector<int> dx = {-1, 0, 1, 0}, dy = {0, 1, 0, -1};

bool dfs(int x, int y, pair <int, int> c);

bool check1(int x, int y, pair <int, int> c) {
	if (x >= 1 && x <= n && y >= 1 && y <= m && table[x][y] == '*')
		return mt[x][y] == make_pair(-1, -1);
	return false;
}

bool check2(int x, int y, pair <int, int> c) {
	if (x >= 1 && x <= n && y >= 1 && y <= m && table[x][y] == '*')
		return dfs(mt[x][y].first, mt[x][y].second, c);
	return false;
}

bool dfs(int x, int y, pair <int, int> c) {
	if (used[x][y] == c) return false;
	used[x][y] = c;
	for (int i = 0; i < 4; i++) {
		if (check1(x + dx[i], y + dy[i], c)) {
			mt[x + dx[i]][y + dy[i]] = {x, y};
			return true; 
		}
	}
	for (int i = 0; i < 4; i++) {
		if (check2(x + dx[i], y + dy[i], c)) {
			mt[x + dx[i]][y + dy[i]] = {x, y};
			return true;
		}
	}
	return false;
}

int ans;

void run() {
	int cnt = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cnt += table[i][j] == '*';
		}
	}

	if (b * 2 <= a) {
		ans = cnt * b;
		return;
	}

	for (int i = 0; i < MAXN; i++) {
		for (int j = 0; j < MAXN; j++) {
			used[i][j] = {-1, -1};
			mt[i][j] = {-1, -1};
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if ((table[i][j] == '*') && ((i + j) % 2 == 0)) {
				dfs(i, j, {i, j});
			}
		}
	}

	ans = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (mt[i][j] != make_pair(-1, -1)) {
				ans += a;
				cnt -= 2;
			}
		}
	} 
	ans += cnt * b;
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