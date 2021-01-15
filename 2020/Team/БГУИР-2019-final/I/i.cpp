#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

mt19937 rnd(time(0));

const int MOD = 1e9 + 7;
const int base = rnd() % 1000 + 228 + 1337;

int add(int a, int b) {
	a += b;
	if (a >= MOD)
		a -= MOD;
	return a;
}

int mul(int a, int b) {
	return (ll) a * b % MOD;
}

const int MAXN = 1e6 + 10;

int pows[MAXN];
int pref_hash[MAXN];

void build() {
	pows[0] = 1;
	pref_hash[0] = 0;
	for (int i = 1; i < MAXN; i++) {
		pows[i] = mul(pows[i - 1], base);
		pref_hash[i] = add(pref_hash[i - 1], pows[i]);
	}	
}

int n;
int a[MAXN];
ll ans = 0;

int hash_L[MAXN], hash_R[MAXN];

void solve(int l, int r) {
	if (l + 1 >= r) return;
	int m = (l + r) / 2;
	solve(l, m);
	solve(m, r);
	for (int i = m - 1; i >= l; i--) {
		int pos = (m - 1) - i + 1;
		hash_L[pos] = add(hash_L[pos - 1], pows[a[i]]);
	}
	for (int i = m; i < r; i++) {
		int pos = i - m + 1;
		hash_R[pos] = add(hash_R[pos - 1], pows[a[i]]);
	}
	int mx;

	mx = 0;
	for (int i = m; i < r; i++) {
		int pos = i - m + 1;
		mx = max(mx, a[i]);
		if (mx <= pos) continue;
		int need = mx - pos;
		if (add(hash_L[need], hash_R[pos]) != pref_hash[mx]) continue;
		if (i - mx + 1 < l) continue;
		ans++;
	}

	mx = 0;
	for (int i = m - 1; i >= l; i--) {
		int pos = (m - 1) - i + 1;
		mx = max(mx, a[i]);
		if (mx <= pos) continue;
		int need = mx - pos;
		if (add(hash_L[pos], hash_R[need]) != pref_hash[mx]) continue;
		if (i + mx - 1 >= r) continue;
		ans++;
	}
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	build();
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	solve(0, n);
	for (int i = 0; i < n; i++) {
		if (a[i] == 1) {
			ans++;
		}
	}
	cout << ans << endl;
	return 0;
}
