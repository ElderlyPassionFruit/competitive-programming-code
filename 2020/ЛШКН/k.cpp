#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 2e5 + 10;
int n;
int s[MAXN], f[MAXN], t[MAXN];

void solve() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> s[i] >> f[i] >> t[i];
	}
	vector<int> order(n);
	iota(all(order), 0);
	sort(all(order), [&] (int a, int b) {return f[a] + s[a] < f[b] + s[b];});
	int r = -1e9;
	for (auto i : order) {
		chkmax(r, s[i]);
		if (r + t[i] > f[i]) {
			cout << "0\n";
			return;
		}
		r += t[i];
	}
	cout << "1\n";	
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