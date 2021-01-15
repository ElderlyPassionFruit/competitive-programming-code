#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()
#define y1 y228
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

char x1, x2;
int y1, y2;

void read() {
	cin >> x1 >> y1 >> x2 >> y2;
	y1--;
	y2--;
}

bool check(char x, int y) {
	int type = abs(x - 'f');
	return x >= 'a' && x <= 'k' && y <= 10 - type && y >= 0; 
}

const int MAXN = 11;
bool g[MAXN][MAXN][MAXN][MAXN];

bool check_move(char x1, int y1, char x2, int y2) {
	if (!check(x1, y1)) return false;
	if (!check(x2, y2)) return false;
	return g[x1 - 'a'][y1][x2 - 'a'][y2];
}

void add(vector<pair<char, int>> a) {
	for (auto i : a) {
		for (auto j : a) {
			if (i == j) continue;
			g[i.first - 'a'][i.second][j.first - 'a'][j.second] = 1;
			g[j.first - 'a'][j.second][i.first - 'a'][i.second] = 1;
		}
	}
}

void build() {
	for (int i = 0; i < MAXN; i++)
		for (int j = 0; j < MAXN; j++)
			for (int k = 0; k < MAXN; k++)
				for (int l = 0; l < MAXN; l++)
					g[i][j][k][l] = 0;
	for (int i = 0; i < MAXN; i++) {
		vector<pair<char, int>> fadd;
		for (int j = 0; j < MAXN; j++) {
			if (check(i + 'a', j)) {
				fadd.push_back({i + 'a', j});
			}
		}
		add(fadd);
	}
	int cntx = 0;
	for (int i = 0; i < MAXN; i++) {
		vector<pair<char, int>> fadd;
		if (i >= 6) {
			cntx++;
		}
		int cnty = 0;
		for (int j = 0; j < MAXN - abs(5 - i); j++) {
			if (i < 6) {
				if (j >= 6) {
					cnty++;
				}
			} else {
				if (j >= 11 - i) {
					cnty++;
				}
			}
			fadd.push_back({'a' + j + cntx,  i - cnty});
		}
		add(fadd);
		for (auto &x : fadd) {
			x.first = MAXN - 1 - (x.first - 'a') + 'a';
		}
		add(fadd);
	}
}

int ans;

void calc() {
	ans = 0;
	for (int i = 0; i < MAXN; i++) {
		for (int j = 0; j < MAXN; j++) {
			if (!check_move(x1, y1, i + 'a', j)) continue;
			if (!check_move(x2, y2, i + 'a', j)) continue;
			ans++;
		}
	}
}

void run() {
	build();
	calc();
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