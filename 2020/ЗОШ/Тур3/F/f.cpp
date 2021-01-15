#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 1e5 + 10;
unordered_set<ll> hashs[MAXN];

const int MOD[2] = {998244353, 1000000007};
int b[2] = {rand() % 1000 + 228, rand() % 1000 + 1337};
int pows[MAXN][2];

int add(int a, int b, int mod) {
	a += b;
	if (a >= mod)
		a -= mod;
	return a;
}

int sub(int a, int b, int mod) {
	a -= b;
	if (a < 0)
		a += mod;
	return a;
}

int mul(int a, int b, int mod) {
	return (ll) a * b % mod;
}

void build() {
	pows[0][0] = pows[0][1] = 1;
	for (int i = 1; i < MAXN; i++) {
		for (int j = 0; j < 2; j++) {
			pows[i][j] = mul(pows[i - 1][j], b[j], MOD[j]);
		}
	}
}

void add_string(string & s) {
	int h[2];
	h[0] = 0;
	h[1] = 0;
	for (int i = 0; i < (int)s.size(); i++) {
		for (int j = 0; j < 2; j++) {
			h[j] = add(mul(h[j], b[j], MOD[j]), s[i], MOD[j]);
		}
		hashs[i + 1].insert((ll)h[0] * 47 + (ll)h[1] * 1001);
	}
}

int n, m;
int mx_len = 0;
void read() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		add_string(s);
		chkmax(mx_len, (int)s.size());
	}
}

const int MAXM = 1e6 + 10;
int Hash[MAXM][2];

void build(string & s) {
	for (int i = 1; i <= s.size(); i++) {
		for (int j = 0; j < 2; j++) {
			Hash[i][j] = add(mul(Hash[i - 1][j], b[j], MOD[j]), s[i - 1], MOD[j]);
		}
	}
}

ll get_hash(int l, int r) {
	l++;
	r++;
	ll ans = 0;
	int fmul[2] = {47, 1001};
	for (int i = 0; i < 2; i++) {
		ans += (ll)fmul[i] * sub(Hash[r][i], mul(pows[r - l + 1][i], Hash[l - 1][i], MOD[i]), MOD[i]);
	}
	return ans;
}

bool check(int pos, int len) {
	return hashs[len].count(get_hash(pos, pos + len - 1));
}

int solve(string & s, int pos) {
	int l = 0, r = min(mx_len, (int)s.size() - pos) + 1;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (check(pos, mid)) {
			l = mid;
		}
		else {
			r = mid;
		}
	}
	return l;
}

void run() {
	cin >> m;
	for (int i = 0; i < m; i++) {
		string s;
		cin >> s;
		build(s);
		for (int j = 0; j < (int)s.size(); j++)
			cout << solve(s, j) << " ";
		cout << "\n";
	}
}

void write() {

}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	build();
	read();
	run();
	write();
	return 0;
}