#define _GLIBCXX_DEBUG
#include <bits/stdc++.h>
 
using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()
 
#define int long long
 
const int MOD = 1e9 + 7;
 
int powmod(int a, int n) {
	if (n == 0)
		return 1;
	if (n % 2 == 0)
		return powmod(a * a % MOD, n / 2);
	return a * powmod(a, n - 1) % MOD;
}
 
int revmod(int a) {
	return powmod(a, MOD - 2);
}
 
int n;
vector<vector<int>> g;
vector<int> dp1;
vector<int> par;
vector<int> dp2;
 
void dfs1(int v, int p = -1) {
	par[v] = p;
	dp1[v] = 1;
	for (int u : g[v]) {
		if (u != p) {
			dfs1(u, v);
			dp1[v] = (dp1[v] * (1 + dp1[u])) % MOD;
		}
	}
}
 
signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n;
	dp1.resize(n);
	dp2.resize(n);
	g.resize(n);
	par.resize(n, -1);
	for (int i = 0; i < n - 1; i++) {
		int a, b;
		cin >> a >> b;
		a--;
		b--;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	dfs1(0);
	int sum1 = 0;
	for (int i = 0; i < n; i++) {
		sum1 += dp1[i];
		sum1 %= MOD;
	}
	cout << sum1 << ' ';
	//cerr << endl;
	int sum2 = 0;
	for (int i = 0; i < n; i++) {
		dfs1(i);
		//cerr << dp1[i] << " ";
		sum2 += dp1[i];
		sum2 %= MOD;
	}
	//cerr << endl;
	cout << sum2 << endl;
	return 0;
}