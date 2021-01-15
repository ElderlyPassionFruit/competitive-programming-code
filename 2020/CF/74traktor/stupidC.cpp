#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int get(vector<int> a) {
	vector<int> last(a.size(), -1e9);
	int ans = 1e9;
	for (int i = 0; i < (int)a.size(); i++) {
		chkmin(ans, i - last[a[i]] - 1);
		last[a[i]] = i;
	}
	return ans;
}

void solve() {
	int n;
	cin >> n;
	vector<int> a(n);
	for (auto &i : a) {
		cin >> i;
		i--;
	}
	sort(all(a));
	int ans = 0;
	do {
		chkmax(ans, get(a));
	} while (next_permutation(all(a)));
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