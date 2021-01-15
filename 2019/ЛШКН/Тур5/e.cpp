#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MOD = 1e9 + 7;

int mul(int a, int b) {
	return a * b % MOD;
}

int binpow(int a, int n) {
	if (n == 0)
		return 1;
	if (n % 2 == 0) {
		int x = binpow(a, n / 2);
		return mul(x, x);
	}
	else {
		int x = binpow(a, n - 1);
		return mul(x, a);
	}
}

int D(int a, int b) {
	return mul(a, binpow(b, MOD - 2));
}

const int MAXN = 1e5 + 10;

int fact[MAXN];

void build() {
	fact[0] = 1;
	for (int i = 1; i < MAXN; i++) {
		fact[i] = fact[i - 1] * i % MOD;
	}
}

int c_n_k(int n, int k) {
	return D(fact[n], mul(fact[k], fact[n - k]));
}

int f, w, h;

void read() {
	cin >> f >> w >> h;
}

int ans = 0;

void run() {
	build();
	int cnt_good = 0;
	if (w == 0)
		cnt_good++;
	for (int i = 1; w - i * (h + 1) >= 0 && f - (i - 1) >= 0; i++) {
		int n1 = w - i * (h + 1);
		int k1 = i;
		k1--;
		int fans1 = c_n_k(n1 + k1, k1);

		int n2 = f - (i - 1);
		int k2 = i + 1;
		k2--;
		//cout << i << " " << n1 << " " << k1 << " " << n2 << " " << k2 << endl;
		int fans2 = c_n_k(n2 + k2, k2);
		//cout << fans1 << " " << fans2 << endl;
		cnt_good += mul(fans1, fans2);
		cnt_good %= MOD;
	}

	int cnt_all = 0;
	if (w == 0)
		cnt_all++;

	for (int i = 1; i <= w && f - (i - 1) >= 0; i++) {
		int n1 = w - i;
		int k1 = i;
		k1--;
		int fans1 = c_n_k(n1 + k1, k1);

		int n2 = f - (i - 1);
		int k2 = i + 1;
		k2--;
		int fans2 = c_n_k(n2 + k2, k2);
		cnt_all += mul(fans1, fans2);
		cnt_all %= MOD;
	}
	//cout << "cnt_good = " << cnt_good << " cnt_all = " << cnt_all << endl; 
	ans = D(cnt_good, cnt_all);
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