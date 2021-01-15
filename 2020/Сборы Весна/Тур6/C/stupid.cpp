#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
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

const int MAXN = 5e5 + 10;
int n, m;
vector<int> g[MAXN];

void read() {
	cin >> n >> m;
	if (n == 1) {
		assert(m == 0);
		cout << 0 << "\n";
		return;
	}
	for (int i = 0; i < n; i++) g[i].clear();
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	/*assert(n == m + 1);
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		assert((int)g[i].size() <= 2);
		assert((int)g[i].size() >= 1);
		cnt += (int)g[i].size() == 1;
	}
	assert(cnt == 2);*/
}

int dp[MAXN];
int sum_dp[MAXN];
int ans_dp[MAXN];

void run() {
	if (n == 1) return;
	dp[0] = 0;
	for (int i = 2; i <= n; i++) {
		dp[i] = 0;
		dp[i] = add(dp[i], i - 2);
		dp[i] = add(dp[i], ans_dp[i - 2]);
		sum_dp[i] = add(sum_dp[i - 1], dp[i]);
		ans_dp[i] = add(ans_dp[i - 1], sum_dp[i]);
	}
	//for (int i = n; i >= 1; i--)
	//	cout << dp[i] << " ";
	//cout << endl;
	cout << add(sum_dp[n], 1) << "\n";
}

void write() {
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t--) {
		read();
		run();
		write();
	}
	return 0;
}