#include <bits/stdc++.h>

using namespace std;

//#define int long long

const int MAXL = 310;
char table[MAXL][MAXL];
int mt[MAXL][MAXL][2];
bool used[MAXL][MAXL];

bool dfs(int x, int y) {
	if (used[x][y]) return false;
	used[x][y] = true;

	int dx = 0, dy = 0;

	dx = 1, dy = 0;
	if (table[x + dx][y + dy] == '*') {
		if (mt[x + dx][y + dy][0] == -1 || dfs(mt[x + dx][y + dy][0], mt[x + dx][y + dy][1])) {
			mt[x + dx][y + dy][0] = x;
			mt[x + dx][y + dy][1] = y;
			return true;
		}
	}
	dx = -1, dy = 0;
	if (table[x + dx][y + dy] == '*') {
		if (mt[x + dx][y + dy][0] == -1 || dfs(mt[x + dx][y + dy][0], mt[x + dx][y + dy][1])) {
			mt[x + dx][y + dy][0] = x;
			mt[x + dx][y + dy][1] = y;
			return true;
		}
	}
	dx = 0, dy = 1;
	if (table[x + dx][y + dy] == '*') {
		if (mt[x + dx][y + dy][0] == -1 || dfs(mt[x + dx][y + dy][0], mt[x + dx][y + dy][1])) {
			mt[x + dx][y + dy][0] = x;
			mt[x + dx][y + dy][1] = y;
			return true;
		}
	}
	dx = 0, dy = -1;
	if (table[x + dx][y + dy] == '*') {
		if (mt[x + dx][y + dy][0] == -1 || dfs(mt[x + dx][y + dy][0], mt[x + dx][y + dy][1])) {
			mt[x + dx][y + dy][0] = x;
			mt[x + dx][y + dy][1] = y;
			return true;
		}
	}

	return false;
}
int n, m, a, b;
int cnt;
void read() {
	cin >> n >> m >> a >> b;
	cnt = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) 
		{
			cin >> table[i][j];
			mt[i][j][0] = -1;
			if (table[i][j] == '*')
				cnt++;
		}
	}
}

void clear() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			used[i][j] = false;
		}
	}
}

void run() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (i % 2 == j % 2)
			if (table[i][j] == '*')
			{
				clear();
				dfs(i, j);
			}
		}
	}
}

void write() {
	if (b * 2 <= a) {
		cout << cnt * b << endl;
	}
	else {
		int cnt2 = 0;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				if (mt[i][j][0] != -1) {
					cnt2++;
				}
			}
		}
	//	cnt2 /= 2;
		cout << cnt2 * a + (cnt - cnt2 * 2) * b << endl;
//		cout << cnt << " " << cnt2 << endl;
	}
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