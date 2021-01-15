#include <bits/stdc++.h>

using namespace std;
#define int long long
int c, w, h;
int cost[26];
const int MAXN = 2010;
char table[MAXN][MAXN];

void read() {
	cin >> c;
	for (int i = 0; i < c; i++)
		cin >> cost[i];
	
	cin >> h >> w;
	for (int i = 1; i <= h; i++) {
		for (int j = 1; j <= w; j++) {
			cin >> table[i][j];
		}
	} 
}

int dp_h1[MAXN][MAXN], dp_h2[MAXN][MAXN], dp[MAXN][MAXN];
int dp_w1[MAXN][MAXN], dp_w2[MAXN][MAXN];
int pref[MAXN][MAXN];

void make() {
	for (int i = 1; i <= h; i++) {
		for (int j = 1; j <= w; j++) {
			pref[i][j] = pref[i][j - 1] + cost[table[i][j] - 'a'];
		}
	}

	for (int i = 1; i <= h; i++) {
		for (int j = 1; j <= w; j++) {
			dp_h1[i][j] = max(0LL, dp_h1[i - 1][j] + cost[table[i - 1][j] - 'a']);
		}
	}

	for (int i = h; i >= 1; i--) {
		for (int j = 1; j <= w; j++) {
			dp_h2[i][j] = max(0LL, dp_h2[i + 1][j] + cost[table[i + 1][j] - 'a']);
		}
	}

	for (int i = 1; i <= h; i++) {
		for (int j = 1; j <= w; j++) {
			dp_w1[i][j] = max(0LL, dp_w1[i][j - 1] + cost[table[i][j - 1] - 'a']);
		}
	}

	for (int i = 1; i <= h; i++) {
		for (int j = w; j >= 1; j--) {
			dp_w2[i][j] = max(0LL, dp_w2[i][j + 1] + cost[table[i][j + 1] - 'a']);
		}
	}

	for (int i = 1; i <= h; i++) {
		for (int j = 1; j <= w; j++) {
			dp[i][j] = pref[i][j] + dp_h1[i][j] + dp_h2[i][j] + dp_w2[i][j];
		}
	}

	for (int i = 1; i <= h; i++) {
		for (int j = w - 1; j >= 1; j--) {
			dp[i][j] = max(dp[i][j], dp[i][j + 1]);
		}
	}
}

int solve(int i, int j) {
	int fans = -1e9;
	int ax = dp_h1[i][j] + dp_w1[i][j] - pref[i][j - 1];
	fans = dp[i][j + 1];
	//for (int k = j + 1; k <= w; k++) {
//		fans = max(fans, dp[i][k]);
//	}
	return fans + ax;
}


int ans = -1e9;
void run() {
	make();
	for (int i = 1; i <= h; i++) {
		for (int j = 1; j <= w - 1; j++) {
			ans = max(ans, solve(i, j));
		}
	}
}

void write() {
	cout << ans << endl;
}

signed main() {
//	freopen("submarine.in", "r", stdin);
//	freopen("submarine.out", "w", stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}