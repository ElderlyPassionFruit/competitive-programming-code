#include <bits/stdc++.h>

using namespace std;
#define int long long

const int MAXN = 1010;
int table[MAXN][MAXN];
int n, m;

void read() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			char x;
			cin >> x;
			table[i][j] = x - 'a' + 1;
		}
	}
}

int h1[MAXN][MAXN], h2[MAXN][MAXN], len_r[MAXN][MAXN], min1[MAXN][MAXN], min2[MAXN][MAXN];

void build() {
	for (int j = 1; j <= m; j++) {
		for (int i = 1; i <= n; i++) {
			if (table[i][j] == table[i - 1][j])
				h1[i][j] = h1[i - 1][j] + 1;
			else
				h1[i][j] = 1;
		}

		for (int i = n; i >= 1; i--) {
			if (table[i][j] == table[i + 1][j])
				h2[i][j] = h2[i + 1][j] + 1;
			else
				h2[i][j] = 1;
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = m; j >= 1; j--) {
			if (table[i][j] == table[i][j + 1])
				len_r[i][j] = len_r[i][j + 1] + 1;
			else
				len_r[i][j] = 1;
		}
	}

	for (int j = 1; j <= m; j++) {
		for (int i = 1; i <= n; i++) {
			if (table[i][j] == table[i - 1][j])
				min1[i][j] = min(min1[i - 1][j], len_r[i][j]);
			else
				min1[i][j] = len_r[i][j];
		}

		for (int i = n; i >= 1; i--) {
			if (table[i][j] == table[i + 1][j])
				min2[i][j] = min(min2[i + 1][j], len_r[i][j]);
			else
				min2[i][j] = len_r[i][j];
		}
	}
}

int ans;

void run() {
	build();
	ans = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (table[i][j] != table[i - 1][j]) {
				int h = h2[i][j];				
				int check1 = h1[i - 1][j];
				int check2 = h2[i + h][j];
				if (check1 < h || check2 < h) continue;
				int fans = 1e9;
				fans = min(fans, min2[i][j]);
				fans = min(fans, min2[i - h][j]);
				fans = min(fans, min1[i + 2 * h - 1][j]);
				ans += fans;
			}
		}
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