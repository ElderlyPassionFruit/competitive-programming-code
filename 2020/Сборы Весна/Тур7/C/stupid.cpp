#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
#define int ll
int n;
vector<int> a;
vector<int> w;

void read() {
	cin >> n;
	a.resize(n);
	for (auto &i : a)
		cin >> i;
	w.resize(n);
	for (auto &i : w)
		cin >> i;
}

const int MAXN = 10;
int dp[MAXN][1 << MAXN];
const int INF = -5e18 - 228 - 2337;
int ans;
void run() {
	for (int i = 0; i < MAXN; i++)
		for (int j = 0; j < (1 << MAXN); j++)
			dp[i][j] = INF;
	dp[0][0] = 0;
	for (int i = 1; i <= n; i++) {
		for (int mask = 0; mask < (1 << n); mask++) {
			if (dp[i - 1][mask] == INF) continue;
			for (int x = 0; x < n; x++) {
				if ((mask >> x) & 1) continue;
				if (a[x] == x + 1) continue;
				int nxt = mask;
				nxt |= (1 << x);
				if (a[x] != 0)
					nxt |= (1 << (a[x] - 1));
				chkmax(dp[i][nxt], dp[i - 1][mask] + w[x] * i);
			}
		}
	}
	/*cout << "dp = " << endl;
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j < (1 << n); j++) {
			cout << (dp[i][j] == INF ? -1 : dp[i][j]) << " ";
		}
		cout << endl;
	}
	cout << endl;*/
	ans = dp[n][(1 << n) - 1];
	if (ans == INF) ans = -1;
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