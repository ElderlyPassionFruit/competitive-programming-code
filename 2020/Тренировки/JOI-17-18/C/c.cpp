#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 3001;
char table[MAXN][MAXN];
vector<int> g[MAXN];
int n, m;

void read() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> table[i][j];
		}
	}
}

bool check_right(int i, int j) {
	return j >= 0 && j + 2 < m && i >= 0 && i < n && table[i][j] == 'R' && table[i][j + 1] == 'G' && table[i][j + 2] == 'W';
}

bool check_down(int i, int j) {
	return j >= 0 && j < m && i >= 0 && i + 2 < n && table[i][j] == 'R' && table[i + 1][j] == 'G' && table[i + 2][j] == 'W';
}

int cnt;

int used[MAXN];
int mt[MAXN];

bool dfs(int v, int c) {
	if (used[v] == c) return false;
	used[v] = c;
	for (auto i : g[v]) {
		if (mt[i] == -1) {
			mt[i] = v;
			return true;
		}
	}

	for (auto i : g[v]) {
		if (dfs(mt[i], c)) {
			mt[i] = v;
			return true;
		}
	}
	return false;
} 


void build() {
	cnt = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cnt += check_right(i, j);
			cnt += check_down(i, j);
		}
	}
}

int ans;

void calc(int s) {
	int i = 0;
	int j = s;
	if (j >= m) {
		j = m - 1;
		i = s - (m - 1);
	}
	int pos = 0;
	for (; i < n && j >= 0; i++, j--, pos++) {
		if (!check_down(i, j)) continue;
		if (check_right(i, j)) {
			g[pos].push_back(pos);
		}
		if(check_right(i + 1, j - 1)) {
			g[pos].push_back(pos + 1);
		}
		if (check_right(i + 2, j - 2)) {
			g[pos].push_back(pos + 2);
		}
	}

	for (int i = 0; i < pos; i++) {
		mt[i] = used[i] = -1;
	}
	int c = 0;
	for (int i = 0; i < pos; i++) {
		dfs(i, c++);
	}
	for (int i = 0; i < pos; i++) {
		if (mt[i] != -1) {
			ans--;
		}
	}
	for (int i = 0; i < pos; i++)
		g[i].clear();
}

void run() {
	build();
	ans = cnt;
	for (int i = 0; i < n + m - 1; i++)
		calc(i);
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