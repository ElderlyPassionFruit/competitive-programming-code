#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n, k;
vector<int> a;

void read() {
	cin >> n >> k;
	a.resize(n);
	for (auto &i : a)
		cin >> i;
	sort(all(a));
}

ll ans;

void run() {
	vector<int> d;
	for (int i = 0; i + 1 < n; i++) {
		d.push_back(a[i + 1] - a[i]);
	}
	sort(all(d));
	ans = k;
	k--;
	while (k && !d.empty()) {
		d.pop_back();
		k--;
	}
	for (auto i : d) {
		ans += i;
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