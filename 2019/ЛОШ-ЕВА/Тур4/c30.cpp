#include <bits/stdc++.h>

using namespace std;
#define int long long

const int MAXC = 21, MAXN = 1e5 + 10;
int dp[MAXC];
int n, c;
vector<pair <int, int> > a;

void read() {
	cin >> n >> c;
	a.resize(n);
	for (auto &i : a)
		cin >> i.first;
	for (auto &i : a)
		cin >> i.second;
}

vector<int> ans;
const int MOD = 10007;

int recalc(int pos, int a1, int b1) {
	pos--;
	a[pos] = {a1, b1};
	for (int i = 0; i < MAXC; i++)
		dp[i] = 0;
	
	dp[0] = 1;

	for (int i = 1; i <= n; i++) {
		
		dp[c] = dp[c] * (a[i - 1].second + a[i - 1].first) + dp[c - 1] * a[i - 1].first;
		dp[c] %= MOD;

		for (int j = c - 1; j >= 1; j--) {
			dp[j] = dp[j] * a[i - 1].second + dp[j - 1] * a[i - 1].first;
			dp[j] %= MOD;
		}

		dp[0] = dp[0] * a[i - 1].second;
		dp[0] %= MOD; 
	}

	return dp[c];
}

void run() {
	int q;
	cin >> q;
	for (int test = 0; test < q; test++) {
		int pos, a1, b1;
		cin >> pos >> a1 >> b1;
		int fans = recalc(pos, a1, b1);
		ans.push_back(fans);
	}
}

void write() {
	for (auto i : ans)
		cout << i << "\n";
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