#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 1e5 + 10;
int dp[MAXN][4][4][4][4];
int cost[4][4][4];
int n;
int arr[MAXN];

void read() {
	cin >> n;
	string s;
	cin >> s;
	for (int i = 0; i < n; i++) {
		if (s[i] == 'B')
			arr[i] = 1;
		else if (s[i] == 'M')
			arr[i] = 2;
		else  if (s[i] == 'F')
			arr[i] = 3;
	}
}

const int INF = -1e9;

int get(int a, int b, int c) {
	return cost[a][b][c];
}

void build() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				set<int> have;
				have.insert(i);
				have.insert(j);
				have.insert(k);
				have.erase(0);
				cost[i][j][k] = have.size();
			}
		}
	}
	for (int i = 0; i < MAXN; i++)
		for (int a1 = 0; a1 < 4; a1++)
			for (int a2 = 0; a2 < 4; a2++)
				for (int b1 = 0; b1 < 4; b1++)
					for (int b2 = 0; b2 < 4; b2++)
						dp[i][a1][a2][b1][b2] = INF;
	for (int i = 0; i < MAXN; i++)
		dp[i][0][0][0][0] = 0;
}
 
int ans;

void calc() {
	for (int i = 1; i <= n; i++) {
		for (int a1 = 0; a1 < 4; a1++) {
			for (int a2 = 0; a2 < 4; a2++) {
				for (int b1 = 0; b1 < 4; b1++) {
					for (int b2 = 0; b2 < 4; b2++) {
						if (b1 == 0 && b2 > 0) continue;
						if (a1 == 0 && a2 > 0) continue;
						chkmax(dp[i][arr[i - 1]][a1][b1][b2], dp[i - 1][a1][a2][b1][b2] + get(arr[i - 1], a1, a2));
						chkmax(dp[i][a1][a2][arr[i - 1]][b1], dp[i - 1][a1][a2][b1][b2] + get(arr[i - 1], b1, b2));
					}
				}
			}
		}
	}
	ans = 0;
	for (int i = 0; i < MAXN; i++)
		for (int a1 = 0; a1 < 4; a1++)
			for (int a2 = 0; a2 < 4; a2++)
				for (int b1 = 0; b1 < 4; b1++)
					for (int b2 = 0; b2 < 4; b2++)
						chkmax(ans, dp[i][a1][a2][b1][b2]);
}

void run() {
	build();
	calc();
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