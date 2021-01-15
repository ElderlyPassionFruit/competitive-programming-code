#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 1e5 + 10;
int n;
int a[MAXN];
int cnt[MAXN];

void solve() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		a[i]--;
		cnt[a[i]]++;
	}
	int mx = *max_element(cnt, cnt + n);
	int sum = -(mx - 1);
	for (int i = 0; i < n; i++) {
		sum += min(mx - 1, cnt[i]);
	}
	for (int i = 0; i < n; i++) {
		cnt[a[i]]--;
	}
	cout << sum / (mx - 1) << '\n';
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