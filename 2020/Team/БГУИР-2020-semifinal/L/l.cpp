#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int MOD = 1e9 + 7;

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

int mul(int a, int b) {
	return (ll) a * b % MOD;
}

int binpow(int a, int n) {
	if (n == 0) return 1;
	if (n & 1) {
		return mul(a, binpow(a, n - 1));
	} else {
		return binpow(mul(a, a), n / 2);
	}
}

int inv(int a) {
	return binpow(a, MOD - 2);
}

int ans = 0;
vector<int> have;

void add(int x) {
	ans = mul(ans, 10);
	ans = add(ans, x);
	have.push_back(x);
}

void pop() {
	ans = sub(ans, have.back());
	ans = mul(ans, inv(10));
	have.pop_back();
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	string s;
	cin >> s;
	for (int i = 0; i < (int)s.size(); i++) {
		add(s[i] - '0');
	}
	int q;
	cin >> q;
	while (q--) {
		char x;
		cin >> x;
		if (x == '-') {
			pop();
		} else {
			int a;
			cin >> a;
			add(a);
		}
		cout << ans << "\n";
	}
	return 0;
}