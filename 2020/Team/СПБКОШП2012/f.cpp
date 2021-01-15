#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x)( x).begin(),(x).end()
#define int ll

vector<int> f(100), rf(100);
const int MOD = 1000000007;

int mul(int a, int b) {
	return a * b % MOD;
}

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

int binpow(int a, int b) {
	int res = 1;
	while(b) {
		if(b & 1) res = mul(res, a);
		b >>= 1;
		a = mul(a, a);
	}
	return res;
}


int inv(int a) {
	return binpow(a, MOD - 2);
}

int cnk(int n, int k) {
	if(k < 0 || n < 0 || n < k) return 0;
	return mul(f[n], mul(rf[k], rf[n - k]));
}

int call(int n, int k) {
	return binpow(n * (n + 1) / 2, k);
}

int have_call[100][100];

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	freopen("init.in", "r", stdin);
	freopen("init.out", "w", stdout);
	int n,m;
	cin >> n >> m;
	f[0] = 1;
	rf[0] = 1;
	for(int j = 1; j < 100; ++j) {
		f[j] = mul(f[j - 1], j);
		rf[j] = inv(f[j]);
	}

	for (int i = 0; i < 100; i++)
		for (int j = 0; j < 100; j++)
			have_call[i][j] = call(i, j);

	vector<vector<int>> dp(n + 1, vector<int> (m + 1));

	for(int j = 1; j <= m; ++j) 
		dp[1][j] = 1;

	for(int j = 1; j <= n; ++j)
		dp[j][1] = 1;
	
	dp[0][0] = 1;
	
	for(int i = 2; i <= n; ++i) {
		for(int j = 2; j <= m; ++j) {
			int calca = have_call[i][j];
			//cout<<i<<' '<< j<<' '<< calca<<endl;
			dp[i][j] = calca;
			for(int kek = 1; kek <= i; ++kek) {
				for(int lol = 0; lol <= j; ++lol) {
					int x = 1;
					x = mul(x, cnk(j, lol));
					x = mul(x, dp[kek - 1][lol]);
					x = mul(x, have_call[i - kek][j - lol]);
					dp[i][j] = sub(dp[i][j], x);	
				}
			}
		}
	}
	cout << dp[n][m];
	return 0;
}
//сосать