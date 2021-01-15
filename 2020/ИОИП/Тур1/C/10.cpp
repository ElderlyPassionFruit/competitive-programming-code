#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 510;

char table[MAXN][MAXN];
int n;

void read() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> table[i][j];
		}
	}
}

bool check(int x, int y) {
	return x >= 0 && x < n && y >= 0 && y < n && table[x][y] == '+';
}

vector<int> dx = {1, 0, -1, 0}, dy = {0, 1, 0, -1};
vector<char> c = {'|', '-'};
void solve(int x, int y, int ind) {
	x += dx[ind];
	y += dy[ind];
	if (!check(x, y)) return;
	table[x][y] = c[ind % 2];
	solve(x, y, ind);
}

void solve(int x, int y) {
	for (int i = 0; i < 4; i++)
		solve(x, y, i);
}

void run() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (table[i][j] == 'O') {
				solve(i, j);
			}
		}
	}
}

void check() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (table[i][j] == '+') {
				cout << "No" << endl;
				exit(0);
			}
		}
	}
}

void write() {
	check();
	cout << "Yes" << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << table[i][j];
		}
		cout << endl;
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