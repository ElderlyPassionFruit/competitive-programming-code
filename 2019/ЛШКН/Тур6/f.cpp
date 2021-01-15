#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
int n, m;
vector<int> a1, a2, a3;
void read() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		int w, c;
		cin >> w >> c;
		if (w == 1)
			a1.push_back(c);
		if (w == 2)
			a2.push_back(c);
		if (w == 3)
			a3.push_back(c);
	}
	sort(a1.begin(), a1.end());
	reverse(a1.begin(), a1.end());
	sort(a2.begin(), a2.end());
	reverse(a2.begin(), a2.end());
	sort(a3.begin(), a3.end());
	reverse(a3.begin(), a3.end());
}

const int MAXM = 3e5 + 10;
int dp[MAXM][2];
int cost[MAXM];
int ans;
void run() {
	for (int i = 0; i <= m; i++) {
		if (dp[i][0] < a1.size()) {
			if (cost[i + 1] < cost[i] + a1[dp[i][0]]) {
				dp[i + 1][0] = dp[i][0] + 1;
				dp[i + 1][1] = dp[i][1];
				cost[i + 1] = cost[i] + a1[dp[i][0]];
			}
		}
		if (dp[i][0] > 0 && dp[i][1] < a2.size()) {
			if (cost[i + 1] < cost[i] - a1[dp[i][0] - 1] + a2[dp[i][1]]) {
				dp[i + 1][0] = dp[i][0] - 1;
				dp[i + 1][1] = dp[i][1] + 1;
				cost[i + 1] = cost[i] - a1[dp[i][0] - 1] + a2[dp[i][1]];	
			}
		}
		if (dp[i][1] < a2.size()) {
			if (cost[i + 2] < cost[i] + a2[dp[i][1]]) {
				dp[i + 2][0] = dp[i][0];
				dp[i + 2][1] = dp[i][1] + 1;
				cost[i + 2] = cost[i] + a2[dp[i][1]];	
			}
		}
 	}

 	for (int i = 1; i <= m; i++)
 		cost[i] = max(cost[i], cost[i - 1]);

 	ans = cost[m];

 	int sum = 0;
 	for (int i = 0; i < a3.size() && m - (i + 1) * 3 >= 0; i++) {
 		sum += a3[i];
 		chkmax(ans, cost[m - (i + 1) * 3] + sum);
 	}
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