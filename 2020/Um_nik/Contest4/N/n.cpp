#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int MAXLOG = 19;
const int N = 1 << MAXLOG;
const int MAXN = N + 228;

const ld PI = acos(-1);
int w[MAXN];
int rev[MAXN];
 
const int MOD = 998244353;
 
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
 
void initFFT() {
	int g = 2;
	for (;; g++) {
		int y = g;
		for (int i = 0; i < MAXLOG - 1; i++) {
			y = mul(y, y);
		}
		if (y == MOD - 1) {
			break;
		}
	}
	w[0] = 1;
	for (int i = 1; i < N; i++) {
		w[i] = mul(w[i - 1], g);
	}
	rev[0] = 0;
	for (int i = 1; i < N; i++) {
		rev[i] = (rev[i >> 1] >> 1) ^ ((i & 1) << (MAXLOG - 1));
	}
}
 
void FFT(int * a) {
	for (int i = 0; i < N; i++) {
		if (i < rev[i]) {
			swap(a[i], a[rev[i]]);
		}
	}
	for (int lvl = 0; lvl < MAXLOG; lvl++) {
		int len = 1 << lvl;
		for (int st = 0; st < N; st += len << 1) {
			for (int i = 0; i < len; i++) {
				int x = a[st + i], y = mul(a[st + i + len], w[i << (MAXLOG - 1 - lvl)]);
				a[st + i] = add(x, y);
				a[st + len + i] = sub(x, y);
			}
		}
	}
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

int a[MAXN], b[MAXN];
int ans[MAXN];

void mul() {
	FFT(a);
	FFT(b);
	for (int i = 0; i < N; i++) {
		a[i] = mul(a[i], b[i]);
	}
	FFT(a);
	int Inv = inv(N);
	for (int i = 0; i < N; i++) {
		ans[i] = mul(a[i], Inv);
	}
	reverse(ans + 1, ans + N);
}

int n, m, k;
string s, t;
string lett = "ATGC";
bool ok[MAXN];

void solve(char x) {
	for (int i = 0; i < MAXN; i++) {
		a[i] = b[i] = 0;
	}
	int last = -1e9;
	for (int i = 0; i < n; i++) {
		if (s[i] == x) {
			last = i;
		}
		if (i - last <= k) {
			a[i] = 1;
		}
	}
	last = 1e9;
	for (int i = n - 1; i >= 0; i--) {
		if (s[i] == x) {
			last = i;
		}
		if (last - i <= k) {
			a[i] = 1;
		}
	}
	int cnt = 0;
	for (int i = 0; i < m; i++) {
		if (t[i] == x) {
			b[i] = 1;
			cnt++;
		}
	}
	mul();
	for (int i = 0; i < n; i++) {
		ok[i] &= ans[i + m - 1] == cnt;
	}
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	initFFT();
	cin >> n >> m >> k;
	cin >> s >> t;
	reverse(all(t));
	for (int i = 0; i < n; i++) {
		ok[i] = true;
	}
	for (auto i : lett) {
		solve(i);
	}
	int ans = 0;
	for (int i = 0; i < n; i++) {
		ans += ok[i];
	}
	cout << ans << endl;
	return 0;
}