#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 110;
int n, m;
char a[MAXN][MAXN];
int dp[MAXN][MAXN];

void read() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> a[i][j];
		}
	}
}

const int INF = 1e9 + 10;



void build() {
	for (int i = 0; i < MAXN; i++)
		for (int j = 0; j < MAXN; j++)
			dp[i][j] = INF;
}

int used[MAXN][MAXN];

vector<int> dx = {-1, 0};
vector<int> dy = {0, -1};

bool check(int x, int y) {
	return x >= 1 && x <= n && y >= 1 && y <= m;
}

void build(int x, int y, int c) {
	used[x][y] = c;
	queue<pair<int, int>> q;
	q.push({x, y});
	while (!q.empty()) {
		x = q.front().first;
		y = q.front().second;
		q.pop();
		for (int i = 0; i < 2; i++) {
			int nx = x + dx[i], ny = y + dy[i];
			if (!check(nx, ny)) continue;
			if (used[nx][ny] == c) continue;
			if (a[nx][ny] == '.') continue;
			used[nx][ny] = c;
			q.push({nx, ny});
		}
	}
}

void calc() {
	dp[0][0] = dp[0][1] = dp[1][0] = 0;
	int c = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (a[i][j] == '.') {
				dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]);
			}
			else {
				build(i, j, c);
				for (int x = 1; x <= i; x++) {
					for (int y = 1; y <= j; y++) {
						//if (x == i && y == j) continue;
						if (a[x][y] == '.') continue;
						if (used[x][y] != c) continue;
						chkmin(dp[i][j], dp[x - 1][y] + 1);
						chkmin(dp[i][j], dp[x][y - 1] + 1);
					}
				}
				c++;
			}
		}
	}
	/*cout << "dp = " << endl;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cout << dp[i][j] << " ";
		}
		cout << endl;
	}*/
}

int ans;

void run() {
	build();
	calc();
	ans = dp[n][m];
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