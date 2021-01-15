#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

map<pair<int, int>, int> have;

int brute(int n, int k) {
	if (n == 0) return 1;
	if (have.count(make_pair(n, k))) return have[{n, k}];
	for (int i = 0; i < n; i++) {
		have[{n, k}] += brute(i, k);
	}	
	have[{n, k}] *= k;
	have[{n, k}] /= n;
	return have[{n, k}];
}

const int MOD = 998244353;

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

const int MAXN = 1e6 + 10;

int fact[MAXN], rfact[MAXN];

void build() {

	fact[0] = rfact[0] = 1;
	for (int i = 1; i < MAXN; i++) {
		fact[i] = mul(fact[i - 1], i);
		rfact[i] = inv(fact[i]);
	}
}

int c_n_k(int n, int k) {
	return mul(fact[n], mul(rfact[k], rfact[n - k]));
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	/*int n = 10;
	for (int i = 1; i <= n; i++)  {
		int last = 0;
		for (int j = 1; j <= n; j++) {
			//cout << mul(j, binpow(j + 1, i - 1)) << " ";
			cout << brute(i, j) - last << " ";
			//last = brute(i, j);
		}
		cout << endl;
	}

	vector<int> a(n, 1);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j < n; j++)
			a[j] += a[j - 1];
		for (auto j : a)
			cout << j << " ";
		cout << endl;
	}*/
	build();
	int q;
	cin >> q;
	while (q--) {
		int n, k;
		cin >> n >> k;
		cout << c_n_k(n + k - 1, k - 1) << "\n";
		//cout << mul(k, binpow(k + 1, n - 1)) << "\n";
	}
	return 0;
}