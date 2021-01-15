#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MOD = 1e4;

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
	return a * b % MOD;
}

int binpow(int a, int n) {
	int res = 1;
	while (n) {
		if (n & 1)
			res = mul(res, a);
		a = mul(a, a);
		n >>= 1;
	}
	return res;
}

int n, x;
string s;

void read() {
	cin >> n >> x >> s;
}

vector<int> z_function(string s) {
	int n = s.size();
	int l = 0, r = 0;
	vector<int> z(n, 0);
	for (int i = 1; i < n; i++) {
		if (r >= i) {
			z[i] = min(z[i - l], r - i + 1);
		}
		while (i + z[i] < n && s[z[i]] == s[i + z[i]])
			z[i]++;
		if (i + z[i] - 1 > r)
			l = i, r = i + z[i] - 1;	
	}
	return z;
}

const int MAXN = 2e3 + 10;
int dp[MAXN][MAXN];

int go[MAXN][2];

void build() {
	go[0][0] = (s[0] == '0');
	go[0][1] = (s[0] == '1');
	string now = "";
	for (int i = 1; i < x; i++) {
		now += s[i - 1];
		for (int j = 0; j < 2; j++) {
			now += '0' + j;
			auto fans = z_function(s + "#" + now); 
			go[i][j] = 0;
			for (int k = i + 1; k < fans.size(); k++)
				if (k + fans[k] == fans.size())
					chkmax(go[i][j], fans[k]);
			now.pop_back();
		}
	}
}

void calc() {
	dp[0][0] = 1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= min(i, x - 1); j++) {
			for (int k = 0; k < 2; k++) {
				dp[i + 1][go[j][k]] = add(dp[i + 1][go[j][k]], dp[i][j]);
			}
		}
	}
}

int ans;

void make_ans() {
	ans = 0;
	for (int i = 1; i <= n; i++) {
		ans = add(ans, mul(dp[i][x], binpow(2, n - i)));
	}
}

void run() {
	build();
	calc();
	make_ans();
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