#include <bits/stdc++.h>

using namespace std;
//#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 1e5 + 10;
const int INF = -1e9;
int dp[MAXN][4][4][4][4];
int help[4][4][4];
int n;
int arr[MAXN];
void read() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		char x;
		cin >> x;
		if (x == 'B')
			arr[i] = 1;
		if (x == 'M')
			arr[i] = 2;
		if (x == 'F')
			arr[i] = 3;
	}
}

int get(int a, int b, int c) {
	return help[a][b][c];
}

int ans = 0;

void run() {
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			for (int k = 0; k < 4; k++) {
				set<int> a;
				a.insert(i);
				a.insert(j);
				a.insert(k);
				a.erase(0);
				help[i][j][k] = a.size();
			}

	for (int i = 0; i < MAXN; i++)
		for (int a = 0; a < 4; a++)
			for (int b = 0; b < 4; b++)
				for (int c = 0; c < 4; c++)
					for (int d = 0; d < 4; d++)
						dp[i][a][b][c][d] = INF;

	for (int i = 0; i < MAXN; i++)
		dp[i][0][0][0][0] = 0;
	
	for (int i = 1; i <= n; i++) {
		for (int a = 0; a < 4; a++) {
			for (int b = 0; b < 4; b++) {
				for (int c = 0; c < 4; c++) {
					for (int d = 0; d < 4; d++) {

						if (b > 0 && a == 0) continue;
						if (d > 0 && c == 0) continue;


						chkmax(dp[i][arr[i]][a][c][d], dp[i - 1][a][b][c][d] + get(a, b, arr[i]));
						chkmax(dp[i][a][b][arr[i]][c], dp[i - 1][a][b][c][d] + get(c, d, arr[i]));
					}
				}
			}
		}
	}

	for (int i = 0; i < MAXN; i++)
		for (int a = 0; a < 4; a++)
			for (int b = 0; b < 4; b++)
				for (int c = 0; c < 4; c++)
					for (int d = 0; d < 4; d++)
						chkmax(ans, dp[i][a][b][c][d]);
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