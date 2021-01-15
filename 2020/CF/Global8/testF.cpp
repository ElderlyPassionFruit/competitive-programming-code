#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int calc(int n, int x) {
	return n - n / x - (int)(n % x != 0) - (x - 1);
}
	
int findBest(int n) {
	int ans = 2;
	for (int x = 2; x < n; x++) {
		if (calc(n, x) > calc(n, ans)) {
			ans = x;
		}
	}
	return ans;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	//cout << calc(11, 3) << endl;
	for (int n = 1; n <= 100; n++) {
		cout << n << " " << findBest(n) << " " << calc(n, findBest(n)) << endl;
	}
	return 0;
}