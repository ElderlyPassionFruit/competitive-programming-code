#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

#define int ll

int get(int x) {
	int base = 2;
	int it = 1;
	while (base + it + 2 * (it + 1) <= x) {
		base = base + it + 2 * (it + 1);
		it++;
	}
	return base;
}

void solve() {
	int n;
	cin >> n;
	int ans = 0;
	while (n >= 2) {
		n -= get(n);
		ans++;
	}
	cout << ans << endl;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}