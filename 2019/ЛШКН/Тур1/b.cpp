#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n, k;
vector<int> a;
void read() {
	cin >> n >> k;
	a.resize(n);
	for (auto &i : a)
		cin >> i;
	sort(a.begin(), a.end());
}

const int MAXN = 5e3 + 10;
int dp[MAXN][MAXN];

const int INF = 1e18 + 10;

int ans;

void run() {
	int cnt1 = k - n % k;
	int cnt2 = n % k;

	int sz1 = n / k;
	int sz2 = (n + k - 1) / k;

	for (int i = 0; i <= cnt1; i++) {
		for (int j = 0; j <= cnt2; j++) {
			if (i == 0 && j == 0)
				continue;
			dp[i][j] = INF;
			if (i > 0)
				chkmin(dp[i][j], dp[i - 1][j] + a[i * sz1 + j * sz2 - 1] - a[(i - 1) * sz1 + j * sz2]);
			if (j > 0)
				chkmin(dp[i][j], dp[i][j - 1] + a[i * sz1 + j * sz2 - 1] - a[i * sz1 + (j - 1) * sz2]);
		}
	}
	ans = dp[cnt1][cnt2];
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