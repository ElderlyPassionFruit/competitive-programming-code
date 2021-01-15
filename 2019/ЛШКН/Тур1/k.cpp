#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 510;
bool dp[MAXN][MAXN][MAXN];

int n, k;
int a[MAXN];

void read() {
	cin >> n >> k;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	sort(a + 1, a + n + 1);
	/*cout << "a = " << endl;
	for (int i = 1; i <= n; i++)
		cout << a[i] << " ";
	cout << endl;*/
}

vector<int> ans;

void run() {
	dp[0][0][0] = 1;
	
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= k; j++) {
			for (int sum = 0; sum <= j; sum++) {
				dp[i][j][sum] = dp[i - 1][j][sum];
				if (j >= a[i])
					chkmax(dp[i][j][sum], dp[i - 1][j - a[i]][sum]);
				if (sum >= a[i])
					chkmax(dp[i][j][sum], dp[i - 1][j - a[i]][sum - a[i]]);		
			}
		}
	}

	/*cout << "dp = " << endl;
	for (int i = 1; i <= n; i++) {
		cout << "i = " << i << endl;
		for (int j = 0; j <= k; j++) {
			for (int sum = 0; sum <= k; sum++) {
				cout << dp[i][j][sum] << " ";
			}
			cout << endl;
		}
	}*/

	for (int i = 0; i <= k; i++) {
		if (dp[n][k][i] == 1) {
			ans.push_back(i);
		}
	}
}

void write() {
	cout << ans.size() << "\n";
	for (auto i : ans)
		cout << i << " ";
	cout << endl;
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