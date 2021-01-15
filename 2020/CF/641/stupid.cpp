#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(), (x).end()
template <typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

int n, m, q;
vector<vector<char>> a;

void read() {
	cin >> n >> m >> q;
	a.resize(n, vector<char> (m, ' '));
	for (auto &i : a) {
		for (auto &j : i) {
			cin >> j;
		}
	}
}

vector<int> dx = {-1, 0, 1, 0}, dy = {0, 1, 0, -1};

bool check(int x, int y) {
	return x >= 0 && x < n && y >= 0 && y < m;
}

void make(vector<vector<char>> & a) {
	vector<vector<char>> na = a;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			for (int it = 0; it < 4; it++) {
				int nx = i + dx[it], ny = j + dy[it];
				if (!check(nx, ny)) continue;
				if (a[i][j] != a[nx][ny]) continue;
				na[i][j] = 1 - (a[i][j] - '0') + '0';
			}
		}
	}
	a = na;
}

char get(vector<vector<char>> a, int x, int y, int it) {
	while (it--) make(a);
	return a[x][y];
} 

void run() {
	/*for (int i = 0; i < 10; i++) {
		cout << "it = " << i << endl;
		make(a);
		for (auto x : a) {
			for (auto y : x) {
				cout << y;
			}
			cout << endl;
		}
		cout << endl;
	}
	exit(0);*/
	while(q--) {
		int x, y, it;
		cin >> x >> y >> it;
		x--;
		y--;
		cout << get(a, x, y, it) << "\n";
	}
}

void write() {

}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.setf(ios::fixed), cout.precision(20);
    read();
    run();
    write();
    return 0;
}