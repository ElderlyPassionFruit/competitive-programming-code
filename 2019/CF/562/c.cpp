#include <bits/stdc++.h>

using namespace std;
#define int long long

const int MAXN = 3 * 1e5 + 10;
const int MAXLOG = 20;

int dp[MAXN][MAXLOG];
int help[MAXLOG][MAXLOG];
int n, q;
int a[MAXN];

void read() {
	cin >> n >> q;
	for (int i = 0; i < n; i++)
		cin >> a[i];
}

vector<string> ans;

void run() {
	for (int i = 0; i < MAXN; i++)
		for (int j = 0; j < MAXLOG; j++)
			dp[i][j] = -1;
	
	for (int i = 0; i < MAXLOG; i++) 
		for (int j = 0; j < MAXLOG; j++)
			help[i][j] = -1;

	for (int i = 0; i < n; i++) {
		int x = a[i];
		int pos = 0;
		vector<int> nums;
		while (x) {
			if (x % 2 == 1) {
				nums.push_back(pos);
			}
			x /= 2;
			pos++;
		}

		for (auto x : nums)
			for (auto y : nums)
				help[x][y] = i;

		for (int i = 0; i < MAXLOG; i++) {
			for (int j = 0; j < MAXLOG; j++) {
				for (int k = 0; k < MAXLOG; k++) {
					help[i][j] = max(help[i][j], min(help[i][k], help[k][j]));
				}
			}
		}

		for (int j = 0; j < MAXLOG; j++) {
			for (auto x : nums) {
				dp[i][j] = max(dp[i][j], help[x][j]);
			}
		}
	}

	/*cout << "dp = " << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 3; j++) {
			cout << dp[i][j] << " ";
		}
		cout << endl;
	}*/

	for (int test = 0; test < q; test++) {
		int x, y;
		cin >> x >> y;
		x--;
		y--;


		int num = a[x];
		int pos = 0;
		
		vector<int> nums;
		while (num) {
			if (num % 2) {
				nums.push_back(pos);
			}
			num /= 2;
			pos++;
		}
		
		bool flag = false;

		for (auto i : nums) {
			if (dp[y][i] >= x) {
				flag = true;
				break;
			}
		}

		if (flag)
			ans.push_back("Shi");
		else
			ans.push_back("Fou");
		//cout << ans.back() << endl;
	}
}

void write() {
	//exit(0);
	for (auto i : ans) {
		cout << i << "\n";
	}
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