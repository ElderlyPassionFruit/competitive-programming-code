#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

void read() {
	int n, m;
	cin >> n >> m;
	vector<int> a(n);
	int sum = 0;
	for (auto &i : a) {
		cin >> i;
		sum += i;
	}
	sort(all(a));
	reverse(all(a));
	for (int i = 0; i < m; i++) {
		if (sum > a[i] * (4 * m)) {
			cout << "No\n";
			return;
		}
	}
	cout << "Yes\n";
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