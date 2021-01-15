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

using cd = complex<double>;
const ld PI = acos(-1);
const int MAXLOG = 16;
const int N = 1 << MAXLOG;
const int MAXN = N + 228;
cd w[MAXN];
int rev[MAXN];
int fact[MAXN], rfact[MAXN];

void initFFT() {
	for (int i = 0; i < N; i++) {
		w[i] = cd(cos(2 * PI * i / N), sin(2 * PI * i / N));
	}
	rev[0] = 0;
	for (int i = 1; i < N; i++) {
		rev[i] = (rev[i >> 1] >> 1) ^ ((i & 1) << (MAXLOG - 1));
	}
}	

void FFT(cd * a, int n) {
	int k = 0;
	while ((1 << (k + 1)) <= n) k++;
	assert((1 << k) == n);
	for (int i = 0; i < n; i++) {
		if (i < (rev[i] >> (MAXLOG - k))) {
			swap(a[i], a[rev[i] >> (MAXLOG - k)]);
		}
	}
	for (int lvl = 0; lvl < k; lvl++) {
		int len = 1 << lvl;
		for (int st = 0; st < n; st += len << 1) {
			for (int i = 0; i < len; i++) {
				cd x = a[st + i], y = a[st + i + len] * w[i << (MAXLOG - 1 - lvl)];
				a[st + i] = x + y;
				a[st + i + len] = x - y;
			}
		}
	}
}

const int B = 1009;
int powsB[5];
cd fa[3][MAXN], fb[3][MAXN];
cd fans[MAXN];

void mul(int * a, int * b, int sz) {
	int n = 2 * sz;
	while ((n & (n - 1))) n++;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < n; j++) {
			fa[i][j] = 0;
			fb[i][j] = 0;
		}
	}
	for (int i = 0; i < sz; i++) {
		int x = a[i];
		for (int j = 0; j < 3; j++) {
			fa[j][i] = x % B;
			x /= B;
		}
		assert(x == 0);
	}
	for (int i = 0; i < sz; i++) {
		int x = b[i];
		for (int j = 0; j < 3; j++) {
			fb[j][i] = x % B;
			x /= B;
		}
		assert(x == 0);
	}
	for (int i = 0; i < 3; i++) {
		FFT(fa[i], n);
		FFT(fb[i], n);
	}
	fill(a, a + n, 0);
	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			for (int i = 0; i < n; i++) {
				fans[i] = fa[x][i] * fb[y][i];
			}
			FFT(fans, n);
			reverse(fans + 1, fans + n);
			for (int i = 0; i < n; i++) {
				a[i] = add(a[i], mul(powsB[x + y], (ll) (fans[i].real() / n + 0.5) % MOD));
			}
		}
	}
	for (int i = sz; i < n; i++) {
		a[i] = 0;
	}
}

void merge(int * a, int * b, int len, int sz) {
	for (int i = 0; i < len; i++) {
		a[i] = mul(a[i], binpow(2, i * sz));
		a[i] = mul(a[i], rfact[i]);
	}
	for (int i = 0; i < len; i++) {
		b[i] = mul(b[i], rfact[i]);
	}
	mul(a, b, len);
	for (int i = 0; i < len; i++) {
		a[i] = mul(a[i], fact[i]);
	}
}

void initCnk() {
	fact[0] = rfact[0] = 1;
	for (int i = 1; i < MAXN; i++) {
		fact[i] = mul(fact[i - 1], i);
		rfact[i] = inv(fact[i]);
	}
	powsB[0] = 1;
	for (int i = 1; i <= 4; i++) {
		powsB[i] = mul(B, powsB[i - 1]);
	}
}

int cnk(int n, int k) {
	if (n < k || k < 0) return 0;
	return mul(fact[n], mul(rfact[k], rfact[n - k]));
}

int ans[MAXN], now[MAXN];

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	initCnk();
	initFFT();
	ll n, k;
	cin >> n >> k;
	if (n > k) {
		cout << 0 << endl;
		exit(0);
	}	

	ans[0] = 1;
	fill(now, now + k + 1, 1);
	now[0] = 0;
	int sz = 1;

	while (n) {
		if (n & 1) {
			merge(ans, now, k + 1, sz);
		}
		merge(now, now, k + 1, sz);
		n >>= 1;
		sz <<= 1;
	}
	int fout = 0;
	for (int i = 0; i <= k; i++) {
		fout = add(fout, mul(ans[i], cnk(k, i)));
	}
	cout << fout << endl;
	return 0;
}