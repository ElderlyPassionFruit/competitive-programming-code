#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MOD = 1e9 + 7;

int mul(int a, int b) {
	return (ll) a * b % MOD;
} 

int add(int a, int b) {
	a += b;
	if (a >= MOD) 
		a -= MOD;
	return a;
}

int sub(int a, int b) {
	a -= b;
	if (a < 0)
		a += MOD;
	return a;
}

int binpow(int a, int n) {
	int res = 1;
	while (n) {
		if (n & 1)
			res = mul(res, a);
		a = mul(a, a);
		n >>= 1;
	}
	return res;
}

int inv(int a) {
	return binpow(a, MOD - 2);
}

int n;

void read() {
	cin >> n;
	if (n < 5) {
		cout << 0 << endl;
		exit(0);
	}
}

int ans;

void run() {
	ans = mul(n, n - 4);
	ans = mul(ans, inv(8));
	for (int i = 1; i < n; i++)
		ans = mul(ans, i);
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