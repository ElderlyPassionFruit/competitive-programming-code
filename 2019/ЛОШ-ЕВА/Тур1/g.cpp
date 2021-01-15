#include <bits/stdc++.h>

using namespace std;
#define int long long
int n, m;
const int MAXN = 1010;
int table[MAXN][MAXN];

void read() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			cin >> table[i][j];
}

bool have[MAXN][MAXN][2];

void run() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (table[i][j] == 0) continue;
			int cnt = have[i - 1][j][0] + have[i - 1][j + 1][0] + have[i - 1][j][1];
			if (cnt == 1) {
				have[i][j][1] = true;
				table[i][j]--;
				table[i][j + 1]--;
			}
			if (table[i][j]) {
				have[i][j][0] = true;
				table[i][j]--;
				table[i + 1][j]--;
			}
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= 2 * m - 1; j++) {
			if (j % 2 == 1)
				if (have[i][(j + 1) / 2][0])
					cout << "_";
				else
					cout << ".";
			else
				if (have[i][(j + 1) / 2][1])
					cout << "|";
				else
					cout << ".";
		}
		cout << endl;
	}

}

void write() {

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