#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(), (x).end()
template <typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

void solve() {
	int n;
	cin >> n;
	vector<int> a(n);
	for (auto &i : a)
		cin >> i;
	sort(all(a));
	int ans = 0;
	for (int i = 0; i < n; i++) {
		if (a[i] <= i + 1) {
			ans = i + 1;
		}
	}
	cout << ans + 1 << '\n';
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.setf(ios::fixed), cout.precision(20);
    int t;
    cin >> t;
    while (t--) {
    	solve();
    }
    return 0;
}