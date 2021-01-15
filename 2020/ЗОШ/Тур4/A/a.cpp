#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n, k, mod;

int add(int a, int b) {
	a += b;
	if (a >= mod)
		a -= mod;
	return a;
}

int mul(int a, int b) {
	return (ll) a * b % mod;
}

void read() {
	cin >> n >> k >> mod;
}

int ans;

void run() {
	ans = 0;
	int now = 1;
	int x = sqrt(k);
	
	int fans = 0;
	for (int i = 0; i < x; i++) {
		fans = add(fans, now);
		now = mul(now, n);
	}

	//cout << "x = " << x << " fans = " << fans << " now = " << now << endl;

	int pos = 0;
	int fnow = 1;
	for (int i = 0; i + x <= k - 1; i += x) {
		ans = add(ans, fans);
		fans = mul(fans, now);
		fnow = mul(fnow, now);
		pos += x;
	}

	//cout << "ans = " << ans << " pos = " << pos << " fnow = " << fnow << endl;
	//cout << "k = " << k << endl;
	for (int i = pos; i <= k - 1; i++) {
		ans = add(ans, fnow);
		fnow = mul(fnow, n);
		//cout << i << endl;
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