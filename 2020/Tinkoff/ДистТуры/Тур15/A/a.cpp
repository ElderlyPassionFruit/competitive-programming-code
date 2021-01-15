#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
#define int ll
int n, m;
vector<vector<int> > a;

void read() {
	cin >> n >> m;
	a.resize(n, vector<int> (m, 0));
	for (auto &i : a)
		for (auto &j : i)
			cin >> j;
}

const int MOD = 1e9 + 7;

int add(int a, int b) {
	return (a + b) % MOD;
	a += b;
	if (a >= MOD)
		a -= MOD;
	return a;
}

void run() {
	int k;
	cin >> k;
	while (k--) {
		int x, y;
		cin >> x >> y;
		x--;
		y--;
		for (int i = 0; i < m; i++) {
			a[x][i] = add(a[x][i], a[y][i]);
		}
	}
}

void write() {
	for (auto i : a) {
		for (auto j : i) {
			cout << j << " ";
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