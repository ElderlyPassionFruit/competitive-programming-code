#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int MAXLOG = 21;
const int N = 1 << MAXLOG;
const int MAXN = N + 5;
int rev[MAXN];
int w[MAXN];
int fa[MAXN];
int a[MAXN];
int fans[MAXN];
int n, m;

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
	//cout <<  "g = " << g << endl;
	w[0] = 1;
	//set<int> used;
	//used.insert(1);
	for (int i = 1; i < N; i++) {
		//w[i] = cd(cos(2 * PI * i / N), sin(2 * PI * i / N));
		w[i] = mul(w[i - 1], g);
	//	assert(!used.count(w[i]));
	//	used.insert(w[i]);
	}
	//assert(mul(w[N - 1], g) == 1);
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

void sq() {
	for (int i = 0; i < N; i++) {
		fa[i] = a[i];
	}
	FFT(fa);
	for (int i = 0; i < N; i++) {
		fa[i] = mul(fa[i], fa[i]);
	}
	FFT(fa);
	int d = inv(N);
	for (int i = 0; i < N; i++) {
		fans[i] = mul(fa[i], d);
	}
	reverse(fans + 1, fans + N);
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	initFFT();
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		a[x]++;
	}
	sq();
	int cnt = 0;
	for (int i = 1; i <= m; i++) {
		if (!a[i] && fans[i]) {
			cout << "NO\n";
			return 0;
		}
		if (a[i] && !fans[i]) {
			cnt++;
		}
	}
	cout << "YES\n";
	cout << cnt << "\n";
	for (int i = 1; i <= m; i++) {
		if (a[i] && !fans[i]) {
			cout << i << " ";
		}
	}
	cout << "\n";
	return 0;
}