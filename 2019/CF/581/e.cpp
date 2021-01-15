#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MOD = 998244353;

int add(int a, int b) {
	return (a + b) % MOD;
}

int mul(int a, int b) {
	return a * b % MOD;
}

int binpow(int a, int n) {
	if (n == 0) return 1;
	if (n % 2 == 0) {
		return binpow(mul(a, a), n / 2);
	}
	else {
		return mul(a, binpow(a, n - 1));
	}
}

int DIV(int a, int b) {
	return mul(a, binpow(b, MOD - 2));
}

int n, m;

void read() {
	cin >> n >> m;
}

const int MAXN = 1e5 + 10;
int fact[MAXN], rfact[MAXN];

void build() {
	fact[0] = 1;
	rfact[0] = 1;
	for (int i = 1; i < MAXN; i++) {
		fact[i] = mul(fact[i - 1], i);
		rfact[i] = DIV(rfact[i - 1], i);
	}
}

int c_n_k(int n, int k) {
	return mul(fact[n], mul(rfact[k], rfact[n - k]));
}

int ans;

void run() {
	ans = 0;
	build();
	for (int max_sum = 1; max_sum <= n; max_sum++) {
		for (int cnt_one = max_sum; cnt_one <= n; cnt_one++) {
			cnt_min = cnt_one - max_sum;
			if (cnt_min > m) continue;
			int cnt = c_n_k(cnt_one + cnt_min, cnt_one);
			
		}
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