#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MOD = 1e9 + 7;
int n, k;
map <int, int> pos;

void read() {
	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		int l, r;
		cin >> l >> r;
		pos[l]++;
		pos[r + 1]--;
	}
}

const int MAXN = 2 * 1e5 + 10;
int fact[MAXN], rfact[MAXN];

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
		return mul(a, x);
	}
}

int D(int a, int b) {
	return mul(a, binpow(b, MOD - 2));
}

void build() {
	fact[0] = 1;
	rfact[0] = 1;
	for (int i = 1; i < MAXN; i++) {
		fact[i] = fact[i - 1] * i % MOD;
		rfact[i] = D(1, fact[i]);
	}
}

int get_c(int n, int k) {
	return mul(fact[n], mul(rfact[k], rfact[n - k]));
}

int ans = 0;

void run() {
	build();
	int l = pos.begin()->first;
	int cnt = 0;
	for (auto i : pos) {
		int dist = i.first - l;
		//cout << "dist = " << dist << " cnt = " << cnt << endl; 
		if (cnt >= k) {
			ans += get_c(cnt, k) * dist % MOD;
			ans %= MOD;
		}
		cnt += i.second;
		l = i.first;
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