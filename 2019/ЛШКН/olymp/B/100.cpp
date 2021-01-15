#include <bits/stdc++.h>

using namespace std;
#define int long long
#define double long double
#define all(a) a.begin(), a.end()

template <typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (y > x) x = y;}
template <typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}

int n, k;
vector<int> a;

void read() {
	cin >> n >> k;
	a.resize(n);
	for (auto &i : a)
		cin >> i;
	sort(a.begin(), a.end());
}

int ans;

void run() {
	reverse(a.begin(), a.end());
	ans = 2 * n;
	for (int i = 0; i < n; i += k) {
		ans += 2 * a[i];
	}
}

void write() {
	cout << ans << endl;
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