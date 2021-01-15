#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int INF = 1e9 + 228;
const int MAXN = 1e5 + 10;
const int BUBEN = 1000;
int n, k;

vector<int> have[MAXN];
int dp[2][MAXN];
int posLast[MAXN];

int getCnt(int val, int pos) {
	while (posLast[val] < (int)have[val].size() && have[val][posLast[val]] <= pos) {
		posLast[val]++;
	}
	return (int)have[val].size() - posLast[val];
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n >> k;
	for (int i = 0; i < k; i++) {
		int pos, val;
		cin >> pos >> val;
		pos = n - pos + 1;
		have[val].push_back(pos);
	}

	for (int i = 1; i <= n; i++) {
		sort(all(have[i]));
	}

	for (int i = 0; i < MAXN; i++) {
		dp[0][i] = dp[1][i] = INF;
	}

	dp[0][0] = 0;

	for (int i = 1; i <= n; i++) {
		int val = INF;
		for (int j = 0; j <= min(BUBEN, (n + 1 - i) + 1); j++) {
			val = min(val, dp[0][j]);
		}
		dp[1][0] = val + 3 * getCnt(i, 0);
		for (int j = 1; j <= min(BUBEN, (n + 1 - i)); j++) {
			int now = 3 * getCnt(i, j);
			dp[1][j] = min(dp[1][j], dp[0][j + 1] + now);			
			dp[1][j] = min(dp[1][j], val + now + 2 + (j * (j + 1)) / 2);
		}
		/*cout << "i = " << i << endl;
		for (int j = 0; j <= (n + 1 - i); j++) {
			cout << dp[1][j] << " ";
		}
		cout << endl;*/
		for (int j = 0; j <= min(BUBEN, (n + 1 - i)); j++) {
			dp[0][j] = dp[1][j];
			dp[1][j] = INF;
		}
	}
	cout << min(dp[0][0], dp[0][1]) << endl;
	return 0;
}