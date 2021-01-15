#include <bits/stdc++.h>

using namespace std;
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
	int n = get(1, 10);
	int t = get(1, 10);
	int k = t;
	cout << n << " " << t << " " << k << "\n";
	for (int i = 2; i <= n; i++) {
		int p = get(1, i - 1);
		int cost = get(1, 1);
		cout << i << " " << p << " " << cost << "\n";
	}
	return 0;
}