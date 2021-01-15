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

mt19937 rnd(time(0));

const int base = rnd() % 1000 + 228 + 1337;

int get_hash(string & s, int l, int r) {
	int ans = 0;
	for (int i = l; i <= r; i++) {
		ans = add(mul(ans, base), s[i]);
	}
	return ans;
}

pair<int, int> get_pair_hash(string & s) {
	pair<int, int> ans;
	ans.first = get_hash(s, 0, s.size() - 2);
	ans.second = get_hash(s, 1, s.size() - 1);
	return ans;
}

const int MAXN = 51, MAXK = 1501;

int dp[MAXN][MAXK];
string a[MAXN][MAXK];
int n, k;

void read() {
	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < k; j++) {
			cin >> a[i][j];
		}
	}
}

int hashs[MAXN][MAXK];
pair<int, int> can[MAXN][MAXK];

void build() {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < k; j++)
			dp[i][j] = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < k; j++) {
			hashs[i][j] = get_hash(a[i][j], 0, i);
			can[i][j] = get_pair_hash(a[i][j]);
		}
	}
	for (int i = 0; i < k; i++)
		dp[0][i] = 1;
}

int ans;

void calc() {
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < k; j++) {
			for (int last = 0; last < k; last++) {
				if (can[i][j].first == hashs[i - 1][last] || can[i][j].second == hashs[i - 1][last]) {
					dp[i][j] = add(dp[i][j], dp[i - 1][last]);
				}
			}
		}
	}

	ans = 0;
	for (int i = 0; i < k; i++)
		ans = add(ans, dp[n - 1][i]);
}

void run() {
	build();
	calc();
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