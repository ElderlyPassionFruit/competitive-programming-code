#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}
#define int ll
int get(int n, int g) {
	return g * (n / g - 1);
}

void solve() {
	int n;
	cin >> n;
	int ans = n;
	int a = 1, b = n - 1;
	for (int i = 2; i * i <= n; i++) {
		if (n % i) continue;
		if (get(n, i) < ans) {
			ans = get(n, i);
			a = i;
			b = (n / i - 1) * i;
		}
		if (get(n, n / i) < ans) {
			ans = get(n, n / i);
			a = n / i;
			b = (i - 1) * n / i;
		}
	}
	cout << a << " " << b << endl;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
	int t;
	cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}