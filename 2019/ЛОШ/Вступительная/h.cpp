#include <bits/stdc++.h>

using namespace std;
#define int long long

const int MAXN = 210;
int arr[MAXN];
int n;

void read() {
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> arr[i];
}

bool check(int a, int b, int c) {
	if (a < b && c < b) return true;
	if (a > b && c > b) return true;
	return false;
}

int last[MAXN][MAXN];
int dp[MAXN][MAXN];
int fans[MAXN][MAXN];
const int INF = 1e9 + 10;
vector <int> ans;

void del_all(int a, int b) {
	if (last[a][b] < 0)
		return;
	if (last[a][b] == a) return;
	del_all(a, last[a][b]);
	del_all(last[a][b], b);
	ans.push_back(last[a][b] + 1);
}

void get_ans(int a, int b) {
	//cout << "a = " << a << " b = " << b << " fans[a][b] = " << fans[a][b] << endl;
	if (fans[a][b] < 0)
		return;
	if (fans[a][b] == a) {
		del_all(a, b);
		return;
	}
	get_ans(a, fans[a][b]);
	get_ans(fans[a][b], b);
}

void run() {

	for (int i = 0; i < MAXN; i++) {
		for (int j = 0; j < MAXN; j++) { 
			dp[i][j] = INF, fans[i][j] = -1, last[i][j] = -1;
		}
	}
	for (int i = 0; i < n - 1; i++)
		last[i][i + 1] = i;
	
	for (int i = 0; i < n; i++) {
		for (int j = i - 2; j >= 0; j--) {
			last[j][i] = -1;
			for (int pos = j + 1; pos < i; pos++) {
				if (last[j][pos] >= 0 && last[pos][i] >= 0 && check(arr[j], arr[pos], arr[i])) {
					last[j][i] = pos;
					break;
				}
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = i - 1; j >= 0; j--) {
			if (arr[i] < arr[j]) continue;
			if (last[j][i] >= 0) {
				dp[j][i] = i - j - 1;
				fans[j][i] = j;
			}

			for (int pos = j + 1; pos < i; pos++) {
				if (arr[pos] >= arr[j] && arr[pos] <= arr[i]) {
					int fhelp = dp[j][pos] + dp[pos][i];
					if (fhelp < dp[j][i]) {
						dp[j][i] = fhelp;
						fans[j][i] = pos;
					}
				}
			}
		}
	}

	if (dp[0][n - 1] == INF) {
		cout << -1 << endl;
		exit(0);
	}

	get_ans(0, n - 1);
}

void write() {
	cout << ans.size() << endl;
	for (auto i : ans)
		cout << i << endl;
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