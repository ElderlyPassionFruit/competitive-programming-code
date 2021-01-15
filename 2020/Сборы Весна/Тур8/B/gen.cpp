#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

int get(int l, int r) {
	return rnd() % (r - l + 1) + l;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n = get(1, 100);
	cout << n << endl;
	set<pair<int, int>> have;
	int x = get(-10, 10);
	int y = get(-10, 10);
	cout << x << " " << y << endl;
	have.insert({x, y});
	for (int i = 0; i < n; i++) {
		int x = get(-10, 10);
		int y = get(-10, 10);
		while (have.count({x, y})) {
			x = get(-10, 10);
			y = get(-10, 10);
		}
		cout << x << " " << y << endl;
		have.insert({x, y});	
	}
	return 0;
}