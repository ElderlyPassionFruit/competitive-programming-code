#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()
 
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

void solve() {
	int n, b;
	cin >> n >> b;
	vector<int> a(n - 1);
	for (auto &i : a)
		cin >> i;
	int Min = 1e9 + 10, Max = -1e9 - 10;
	for (int i = 0; i < b; i++) {
		int now = 0;
		for (int i = 0; i < n; i++) {
			int x;
			cin >> x;
			now += x;
			if (i == n - 1) break;
			now *= a[i];
		} 
		chkmin(Min, now);
		chkmax(Max, now);
	}
	cout << Max - Min << "\n";
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t--)
		solve();
	return 0;
}