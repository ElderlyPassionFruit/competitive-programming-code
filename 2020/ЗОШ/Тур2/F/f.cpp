#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n;
vector<int> a;

void read() {
	cin >> n;
	a.resize(n);
	for (auto &i : a)
		cin >> i;
}

int ans;

void run() {
	ans = 0;
	int fans = 0;
	for (int i = 0; i < n - 1; i++) {
		fans = __gcd(fans, a[i + 1] - a[i]);
	}
	set<int> have;
	for (int i = 0; i < n; i++)
		have.insert(a[i]);
	int x = a[0];
	while (x < a[n - 1]) {
		x += fans;
		if (!have.count(x))
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