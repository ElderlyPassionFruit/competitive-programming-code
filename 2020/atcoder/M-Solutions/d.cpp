#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

#define int ll

const int N = 80;
int n;
int a[N];

void read() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
}

int now = 1000;
int ans = 1000;
int cnt = 0;

void run() {
	for (int i = 0; i + 1 < n; i++) {
		if (a[i] < a[i + 1]) {
			cnt += now / a[i];
			now %= a[i];
		} else {
			now += a[i] * cnt;
			cnt = 0;
		}
		chkmax(ans, now);
	}
	now += a[n - 1] * cnt;
	chkmax(ans, now);
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