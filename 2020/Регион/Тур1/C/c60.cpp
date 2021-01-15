#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MOD = 1e9 + 7;

int add(int a, int b) {
	a += b;
	if (a >= MOD)
		a -= MOD;
	return a;
}

int mul(int a, int b) {
	return (ll) a * b % MOD;
}

int n, m, k;

void read() {
	cin >> n >> m >> k;
}

const int MAXN = 510;

int ans;
int dp[MAXN][MAXN];

vector<int> fact(int n) {
	vector<int> ans;
	ans.push_back(n);
	for (int i = 2; i * i <= n; i++) {
		if (n % i == 0) {
			ans.push_back(i);
			ans.push_back(n / i);
		}
	}
	sort(all(ans));
	ans.resize(unique(all(ans)) - ans.begin());
	return ans;
}


void run() {
	for (int i = 1; i <= k; i++)
		dp[1][i % m] += 1;
	for (int i = 1; i < n; i++) {
		for (int x = 0; x < m; x++) {
			for (int j = 1; j <= k; j++) {
				dp[i + 1][j * x % m] = add(dp[i + 1][j * x % m], dp[i][x]);
			}
		}
	}
	/*cout << "dp = " << endl;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < m; j++) {
			cout << dp[i][j] << " ";
		}
		cout << endl;
	}*/
	ans = dp[n][0];
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