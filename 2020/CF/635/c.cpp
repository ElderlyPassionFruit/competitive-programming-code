#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MOD = 998244353;

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
	return (ll) a * b % MOD;
}

int n, m;
string s, t;

void read() {
	cin >> s >> t;
	n = s.size();
	m = t.size();
	while (t.size() < n) {
		t += "?";
	}
}

const int MAXN = 3010;
int dp[MAXN][MAXN];

void build() {
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= n; j++) {
			dp[i][j] = 0;
		}
	}
	dp[0][0] = 1;
}

void calc() {

}

int ans;

void make_ans() {

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