#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n, m, k;

void read() {
	cin >> n >> m >> k;
	if (k == 1) {
		cout << 1 << endl;
		exit(0);
	}
}

set<vector<vector<int> > > used;
set<vector<vector<int> > > ans;

bool make_r(vector<vector<int> > & table, int x, int y) {
	if (x + k - 1 >= n) return false;
	for (int i = x; i < x + k; i++){
		if (table[i][y] != 0) return false;
			table[i][y] = 1;
	}
	return true;
}

bool make_c(vector<vector<int> > & table, int x, int y) {
	if (y + k - 1 >= m) return false;
	for (int i = y; i < y + k; i++){
		if (table[x][i] != 0) return false;
			table[x][i] = 2;
	}
	return true;
}

void add(vector<vector<int> > table) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (!table[i][j]) return;
		}
	}
	ans.insert(table);
}

void solve(vector<vector<int> > table) {
	if (used.count(table)) return;
	used.insert(table);
	add(table);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			auto a = table;
			bool flag = make_r(a, i, j);
			if (flag) solve(a);
			a = table;
			flag = make_c(a, i, j);
			if (flag) solve(a);
			if (flag) return;
		}
	}
}

void out() {
	for (auto i : ans) {
		for (auto j : i) {
			for (auto k : j) {
				cout << k << " "; 
			}
			cout << endl;
		}
		cout << endl;
	}
}

void run() {
	vector<vector<int> > table;
	table.resize(n, vector<int> (m, 0));
	solve(table);
}

void write() {
	//out();
	cout << ans.size() << endl;
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