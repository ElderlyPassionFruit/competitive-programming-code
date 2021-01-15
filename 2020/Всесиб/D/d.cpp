#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MOD = 998244353;

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

int Div(int a, int b) {
	return mul(a, binpow(b, MOD - 2));
}

int n;

void read() {
	cin >> n;
	if (n == 3) {
		cout << 3 << endl;
		exit(0);
	}
	if (n % 2 == 0) {
		cout << 0 << endl;
		exit(0);
	}
}

int ans;

vector<int> have;

int solve(int n) {
	if (n <= 2) return 1;
	if (have[n] != -1) return have[n];
	have[n] = Div(
		sub(mul(3, mul(2 * n - 3, solve(n - 1))), mul(n - 3, solve(n - 2))), 
		n
	);	
	return have[n];
}

void run() {
	have.resize(n, -1);
//	for (int i = 1; i <= 10; i += 2)
//		cout << solve(i) << "\n";
	ans = solve((n + 1) / 2 + 1);
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