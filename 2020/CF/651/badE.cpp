#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n;
string a, b;

void read() {
	cin >> n >> a >> b;
}

int ans;

void run() {
	a = a + a;
	b = b + b;
	ans = 0;
	char last = '2';
	int cnt = 0;
	for (int i = 0; i < 2 * n; i++) {
		if (a[i] == b[i]) continue;
		if (last != a[i]) {
			last = a[i];
			cnt = 0;
		}
		cnt++;
		chkmax(ans, cnt);
	}
	sort(all(a));
	sort(all(b));
	if (a != b) {
		ans = -1;
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