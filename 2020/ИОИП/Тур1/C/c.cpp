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

bool nxt[4][MAXN][MAXN];

void build(int x, int y, int ind) {
	
}

void build() {

}

void run() {

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