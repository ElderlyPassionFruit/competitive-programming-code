#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()
#define int ll
int nxt(int x) {
	return x ^ (x >> 1);
}

int get(int x) {
	int now = nxt(x);
	int ans = 1;
	while (now != x) {
		now = nxt(now);
		ans++;
	}
	return ans;
}

const int MOD = 1e9 + 7;

int mul(int a, int b) {
	return (ll) a * b;
}

int sub(int a, int b) {
	return (a - b + MOD) % MOD;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int x;
	cin >> x;
	int cnt = 0;
	while (x % 2 == 0) {
		cnt++;
		x /= 2;
	}
	int ans = 2;
	for (int i = 0; i < cnt; i++) {
		ans = mul(ans, ans);
	}
	cout << sub(ans, 1);
	return 0;
}