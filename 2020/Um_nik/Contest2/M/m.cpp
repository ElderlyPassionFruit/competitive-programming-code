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

int n;

int solve(string x) {
	int ans = binpow(2, n - 1);
	int fans = 0;
	for (auto i : x) {
		fans = mul(fans, 2);
		fans = add(fans, i - '0');
	}
	ans = mul(ans, fans);
	return ans;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	string x;
	cin >> x;
	n = x.size();
	cout << solve(x) << endl;
	return 0;
}