#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
#define int ll
void read() {
	int k, n;
	cin >> k >> n;
	vector<int> a(n);
	for (auto  &i : a)
		cin >> i;
	sort(all(a));
	int ans = k - a[0] - (k - a[n - 1]);
	for (int i = 1; i < n; i++) {
		chkmin(ans, k - (a[i] - a[i - 1]));
	}
	cout << ans << endl;
}

void run() {

}

void write() {

}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}