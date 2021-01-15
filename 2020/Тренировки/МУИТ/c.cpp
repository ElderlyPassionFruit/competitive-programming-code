#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
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

int sub(int a, int b) {
	a -= b;
	if (a < 0) 
		a += MOD;
	return a;
}

const int MAXN = 5e3 + 10;
string s;
int n, m;
vector<pair<int, int>> a;
void read() {
	cin >> n >> s >> m;
	a.resize(m);
	for (auto &i : a) {
		cin >> i.first >> i.second;
	}
	sort(all(a));
}

int dp[MAXN];
int ans;

void run() {
	dp[0] = 1;
	for (int i = 0; i < n && s[i] == '1'; i++) {
		dp[i + 1] = 1;
	}
	for (auto [l, r] : a) {
		for (int i = r + 1; i <= n && s[i - 1] == '1'; i++) {
			dp[i] = add(dp[i], dp[l - 1]);
		}
		for (int i = r; i >= l; i--) {
			dp[i] = add(dp[i], dp[l - 1]);
		}
	}
	ans = dp[n];
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