#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n, s;
vector<int> a;

void read() {
	cin >> n >> s;
	a.resize(n);
	for (auto &i : a)
		cin >> i;
}

int ans;

void run() {
	ans = 0;
	sort(all(a));
	for (int i = 0; i < n; i++) {
		if (i > 0 && a[i] + a[i - 1] > s) break;
		ans++;
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