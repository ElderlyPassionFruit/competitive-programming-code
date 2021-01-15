#include <bits/stdc++.h>

using namespace std;
#define int long long

int x, y, d, g;
vector<int> cx, cy;
void read() {
	cin >> x >> y >> d >> g;
	cx.assign(x + 1, 0);
	cy.assign(y + 1, 0);
	for (int i = 0; i < g; i++) {
		int a, b;
		cin >> a >> b;
		cx[a]++;
		cy[b]++;
	}
}

const int MAXN = 210;
const int INF = 1e9;
int dp[MAXN][MAXN];
int ans;
int calc(vector<int> help) {
	for (int i = 0; i < MAXN; i++)
		for (int j = 0; j < MAXN; j++)
			dp[i][j] = INF;

	dp[0][0] = 0;

	int n = help.size() - 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < i; j++) {
			for (int k = 1; k <= min(d, i); k++) {
				dp[i][k] = min(dp[i][k], max(dp[j][k - 1], help[i] - help[j]));
			}
		}
	}
	/*cout << "help = ";
	for (auto i : help)
		cout << i << " ";
	cout << endl;
	cout << "dp = " << endl;
	for (int i = 1; i <= n; i++) {
		for (int k = 1; k <= d; k++)
			cout << dp[i][k] << " ";
		cout << endl;
	}*/

	return dp[n][d];
}

void run() {
	for (int i = 1; i <= x; i++)
		cx[i] = cx[i] + cx[i - 1];
	for (int i = 1; i <= y; i++)
		cy[i] = cy[i] + cy[i - 1];

	ans = min(calc(cx), calc(cy));
}

void write() {
	cout << ans << endl;
}

signed main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}