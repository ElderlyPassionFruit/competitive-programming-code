#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()
#define int ll

const int MAXLEN = 20, MAXNUM = 10;
ll dp[MAXLEN][MAXNUM];

bool check(int x) {
	assert(x >= 0 && x < 10);
	return x != 1 && x != 2 && x != 3 && x != 5 && x != 8;
}

void build() {
	for (int i = 0; i < MAXLEN; i++)
		for (int j = 0; j < MAXNUM; j++)
			dp[i][j] = 0;
	for (int i = 0; i < MAXNUM; i++) {
		dp[1][i] = check(i);
	}
	for (int len = 2; len < MAXLEN; len++) {
		for (int num = 0; num < MAXNUM; num++) {
			for (int last = 0; last < MAXNUM; last++) {
				if (!check(num)) continue;
				if (!check(last)) continue;
				dp[len][num] += dp[len - 1][last];
			}
		}
	}
}

ll calc(string n, int pos) {
	if (pos == n.size()) return 1;
	ll ans = 0;
	for (int i = 0; i <= 9; i++) {
		if (n[pos] - '0' <= i) break;
		if (!check(i)) continue;
		ans += dp[n.size() - pos][i];
	} 
	if (check(n[pos] - '0'))
	ans += calc(n, pos + 1);
	return ans;
}

void solve() {
	string n;
	cin >> n;
	cout << calc(n, 0) << endl;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	build();
	int t;
	cin >> t;
	while (t--)
		solve();
	return 0;
}