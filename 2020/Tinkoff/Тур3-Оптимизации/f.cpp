#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int INF = 1e18;
const int MAXN = 1e5 + 10, MAXK = 20;
int dp[MAXN][MAXK];
int n, k;
int a[MAXN];

void read() {
	cin >> n >> k;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
}

int pref1[MAXN], pref2[MAXN];
int cnt[MAXN];

void build() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= k; j++) {
			dp[i][j] = INF;
		} 
	}
}

int cost(int l, int r) {

}

void run() {
	build();
	for (int i = 1; i <= n; i++) {
		dp[i][1] = cost(1, i);
		for (int j = 2; j <= k; j++) {
			for (int x = j - 1; x < i; x++) {
				chkmin(dp[i][j], dp[x][j - 1] + cost(x + 1, j));
			}
		}
	}
}

void write() {
	cout << dp[n][k] << endl;
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
