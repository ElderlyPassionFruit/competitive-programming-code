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
	a %= MOD;
	b %= MOD;
	a += b;
	if (a >= MOD)
		a -= MOD;
	return a;
}

int sub(int a, int b) {
	a %= MOD;
	b %= MOD;
	a -= b;
	if (a < 0)
		a += MOD;
	return a;
}

int mul(int a, int b) {
	a %= MOD;
	b %= MOD;
	return (ll) a * b % MOD;
}

const int MAXN = 1010;
int n;
int a[MAXN][MAXN];

void read() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> a[i][j];
		}
	}
}

int dp[MAXN][MAXN];

void build() {
	for (int i = 0; i < MAXN; i++) {
		for (int j = 0; j < MAXN; j++) {
			dp[i][j] = 0;
		}
	}
}

void add(int val, int pos, int & fans, int & last, vector<pair<int, int>> & st) {
	if (last == -1) last = pos;
	if (st.empty()) {
		fans = add(fans, val * (pos - last + 1));
		st.push_back({pos, val});
	} else {
		fans = add(fans, val * (pos - st.back().first));
		st.push_back({pos, val});
	}
}

void pop(int & fans, int & last, vector<pair<int, int>> & st) {
	assert(!st.empty());
	if ((int)st.size() == 1) {
		fans = sub(fans, (st.back().first - last + 1) * st.back().second);
		st.pop_back();
	} else {
		int pos = st.back().first;
		int val = st.back().second;
		st.pop_back();
		fans = sub(fans, (pos - st.back().first) * val);
	}
}

int calc(int bit, int type) {
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		int fans = 0;
		int last = -1;
		vector<pair<int, int>> st;
		for (int j = 1; j <= n; j++) {
			if (((a[i][j] >> bit) & 1) == type) {
				dp[i][j] = dp[i - 1][j] + 1;
				while (!st.empty() && st.back().second >= dp[i][j])
					pop(fans, last, st);
				add(dp[i][j], j, fans, last, st);
				ans = add(ans, fans);
			} else {
				dp[i][j] = 0;
				fans = 0;
				last = -1;
				st.clear();
			}
		}
	}
	return ans;
}

int ans1, ans2;

void run() {
	build();
	int full = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			full = add(full, i * j);
		}
	}
	ans1 = 0, ans2 = 0;
	for (int i = 0; i < 31; i++) {
		int fans1 = calc(i, 1);
		ans1 = add(ans1, mul((1 << i) % MOD, fans1));
	}
	for (int i = 0; i < 31; i++) {
		int fans2 = calc(i, 0);
		ans2 = add(ans2, mul((1 << i) % MOD, sub(full, fans2)));
	}
}

void write() {
	cout << ans1 << " " << ans2 << "\n";
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

/*
input = 
3
2 1 2 
2 2 2 
1 2 2 

ans = 
36 87

out = 
40 85
*/