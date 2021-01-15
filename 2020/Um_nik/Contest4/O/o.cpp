#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int MOD = 1e9 + 7;

int add(int a, int b) {
	a += b;
	if (a >= MOD) {
		a -= MOD;
	}
	return a;
}

int sub(int a, int b) {
	a -= b;
	if (a < 0) {
		a += MOD;
	}
	return a;
}

int mul(int a, int b) {
	return (ll) a * b % MOD;
}

int binpow(int a, int n) {
	int ans = 1;
	while (n) {
		if (n & 1) {
			ans = mul(ans, a);
		}
		a = mul(a, a);
		n >>= 1;
	}
	return ans;
}

int inv(int a) {
	return binpow(a, MOD - 2);
}

int n;
string s;

void xorConvolution(vector<int> & a) {
	int n = 1;
	while ((1 << (n + 1)) <= a.size()) n++;
	for (int k = 0; k < n; k++) {
		for (int mask = 0; mask < (1 << n); mask++) {
			if ((mask >> k) & 1) continue;
			int x = a[mask], y = a[mask ^ (1 << k)];
			a[mask] = add(x, y);
			a[mask ^ (1 << k)] = sub(x, y);
		}
	}
}

vector<int> xorConvolution(string & a) {
	vector<int> fa(a.size());
	for (int i = 0; i < (int)a.size(); i++) {
		fa[i] = a[i] - '0';
	}
	xorConvolution(fa);
	for (int i = 0; i < (int)fa.size(); i++) {
		fa[i] = mul(fa[i], fa[i]);
	}
	xorConvolution(fa);
	int myInv = inv(fa.size());
	for (int i = 0; i < (int)fa.size(); i++) {
		fa[i] = mul(fa[i], myInv);
	}
	return fa;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n >> s;
	auto have = xorConvolution(s);
	int ans = 0;
	for (int i = 0; i < (1 << n); i++) {
		ans = add(ans, mul(1 << (n - __builtin_popcount(i)), have[i]));
	}
	cout << mul(ans, 3) << endl;
	return 0;
}