#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

int n, d, m;
vector<int> a;

void read() {
	cin >> n >> d >> m;
	a.resize(n);
	for (auto &i : a) {
		cin >> i;
	}
}

int calc(vector<int> a) {
	int ans = 0;
	for (int i = 0; i < n; i++) {
		ans += a[i];
		if (a[i] > m) i += d;
	}
	return ans;
}

int ans;

void run() {
	sort(all(a));
	ans = 0;
	do {
		chkmax(ans, calc(a));
	} while (next_permutation(all(a)));
}

void write() {
	cout << ans << endl;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
	read();
	run();
	write();
	return 0;
}