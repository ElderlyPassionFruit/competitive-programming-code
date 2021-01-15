#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

typedef vector<vector<int> > matrix;

bool check(matrix & table) {
	int n = table.size();
	int m = table[0].size();
	for (int j = 0; j < m - 1; j++) {
		bool flag = false;
		for (int i = 0; i < n; i++) {
			if (table[i][j] == 1) {
				flag = true;
				break;
			}
		}
		if (flag)
			continue;
		return false;
	}

	for (int i = 0; i < n - 1; i++) {
		bool flag = false;
		for (int j = 0; j < m; j++) {
			if (table[i][j] == 2) {
				flag = true;
				break;
			}
		}
		if(flag)
			continue;
		return false;
	}
	return true;
}

void read() {

}

void run() {

}

void write() {

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