#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 25;

struct pt{
	int x, y;
	pt() {}
	pt(int a, int b) {
		x = a, y = b;
	}
};

int n, m;
char table[MAXN][MAXN];
deque<pt> q;
string s;
void read() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> table[i][j];
			if (table[i][j] == 'S') {
				q.push_back({i, j});
			}
		}
	}
	cin >> s;
}

bool check(int x, int y) {
	return x >= 0 && x < n && y >= 0 && y < m && table[x][y] != 'S';
}

void no() {
	cout << "Epic Fail" << endl;
	exit(0);
}

void run() {
	for (int i = 0; i < (int)s.size(); i++) {
		char x = s[i];
		int dx = 0, dy = 0;
		if (x == 'U') dx = -1;
		if (x == 'D') dx = 1;
		if (x == 'L') dy = -1;
		if (x == 'R') dy = 1;
		pt a = q[0];
		if (!check(a.x + dx, a.y + dy))
			no();
		a.x += dx;
		a.y += dy;
		if (table[a.x][a.y] == '.') {
			pt b = q.back();
			q.pop_back();
			table[b.x][b.y] = '.';
			table[a.x][a.y] = 'S';
			q.push_front(a);
		}
		else {
			table[a.x][a.y] = 'S';
			q.push_front(a);
		}
	}
}

void write() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << table[i][j];
		}
		cout << "\n";
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