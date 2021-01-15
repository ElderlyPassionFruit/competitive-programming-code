#include <bits/stdc++.h>

using namespace std;
#define int long long
int r, c;
const int MAXN = 60;
char table[MAXN][MAXN];

void read() {
	for (int i = 0; i < MAXN; i++) {
		for (int j = 0; j < MAXN; j++) {
			table[i][j] = '.';
		}
	}

	cin >> r >> c;
	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= c; j++) {
			cin >> table[i][j];
		}
	}
}

int color[MAXN][MAXN];

bool check_color(int x, int y) {
	return (table[x][y] == 'X') && (color[x][y] == 0);
}

vector <int> d = {0, 1, -1};

void dfs_color(int x, int y, int c) {
	color[x][y] = c;

	for (auto dx : d) {
		for (auto dy : d) {
			if (dx != 0 && dy != 0)
				continue;
			if (dx == 0 && dy == 0)
				continue;

			if (check_color(x + dx, y + dy)) {
				dfs_color(x + dx, y + dy, c);
			}
		}
	}
}

int full_color = 1;

void make_color() {
	for (int i = 0; i < MAXN; i++) {
		for (int j = 0; j < MAXN; j++) {
			color[i][j] = 0;
		}
	}
	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= c; j++) {
			if (check_color(i, j)) {
				dfs_color(i, j, full_color++);
			}
		}
	}
	full_color--;
}

vector <vector <int> > g;

int check_can(int x, int y) {
	if (table[x][y] == 'X')
		return 0;
	if (table[x][y] == 'S')
		return 1;
	return 1e9;
}

vector <vector <int> > get_dp(int x, int y) {
	vector <vector <int> > dp(r + 10, vector <int> (c + 10, 1e9));
	dp[x][y] = 0;

	set <pair <int, pair <int, int> > > q;
	q.insert({0, {x, y}});
	while (!q.empty()) {
		auto p = *q.begin();
		q.erase(q.begin());

		int pos_x = p.second.first;
		int pos_y = p.second.second;
		for (auto dx : d) {
			for (auto dy : d) {
				if (dx != 0 && dy != 0)
					continue;
				if (dx == 0 && dy == 0)
					continue;

				int dist = check_can(pos_x + dx, pos_y + dy);
				if (dp[pos_x + dx][pos_y + dy] > dp[pos_x][pos_y] + dist) {
					q.erase({dp[pos_x + dx][pos_y + dy], {pos_x + dx, pos_y + dy}});
					dp[pos_x + dx][pos_y + dy] = dp[pos_x][pos_y] + dist;
					q.insert({dp[pos_x + dx][pos_y + dy], {pos_x + dx, pos_y + dy}});
				}

			}
		}
	}
	return dp;
}

void make_g() {
	g.assign(full_color, vector <int> (full_color, 1e9));
	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= c; j++) {
			color[i][j]--;
		}
	}
	
	vector <bool> used(full_color, false);

	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= c; j++) {
			if (color[i][j] != -1) {
	
				if (!used[color[i][j]]) {
					used[color[i][j]] = true;
					auto dp = get_dp(i, j);

					for (int x = 1; x <= r; x++) {
						for (int y = 1; y <= c; y++) {
							if (color[x][y] != -1) {
								g[color[i][j]][color[x][y]] = min(g[color[i][j]][color[x][y]], dp[x][y]);
							}
						}
					}
	
				}
			}
		}
	}
}

int ans = 0;

int dp[1 << 16][16];

void find_dist() {
	for (int i = 0; i < (1 << 16); i++)
		for (int j = 0; j < 16; j++)
			dp[i][j] = 1e9;
	for (int i = 0; i < 16; i++) {
		dp[1 << i][i] = 0;
	}
	
	for (int mask = 1; mask < (1 << full_color); mask++) {
		for (int i = 0; i < full_color; i++) {
			if (!((mask >> i) & 1))
				continue;
			
		//	cout << "mask = " << mask << " i = " << i << endl;

			int pred = mask ^ (1 << i);
			
			for (int j = 0; j < full_color; j++) {
				if (!((pred >> j) & 1))
					continue;

				dp[mask][i] = min(dp[mask][i], dp[pred][j] + g[j][i]);
			}
		}
	}
}

void run() {
	make_color();
	make_g();
	find_dist();
	ans = 1e9;
	/*for (int i = 0; i < (1 << full_color); i++) {
		for (int j = 0; j < full_color; j++) {
			cout << dp[i][j] << " ";
		}
		cout << endl;
	}*/

	for (int i = 0; i < full_color; i++) {
		ans = min(ans, dp[(1 << full_color) - 1][i]);
	}
/*	cout << "color = " << endl;
	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= c; j++) {
			cout << color[i][j] << " ";
		}
		cout << endl;
	}

	cout << "g = " << endl;
	for (int i = 0; i < full_color; i++) {
		for (int j = 0; j < full_color; j++) {
			cout << g[i][j] << " ";
		}
		cout << endl;
	}*/
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