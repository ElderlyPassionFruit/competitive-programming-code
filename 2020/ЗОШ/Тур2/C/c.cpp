#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct event{
	int x, y, cost, have;
	event() {}
	event(int a, int b, int c, int d) {
		x = a, y = b, cost = c, have = d;
	}
};

bool operator<(const event & a, const event & b) {
	return tie(a.cost, a.have, a.x, a.y) < tie(b.cost, b.have, b.x, b.y);
}

const int INF = 1e9 + 10;
const int MAXN = 110, MAXF = 250;
int dp[MAXN][MAXN][MAXF];
int table[MAXN][MAXN];
int n, m, k, f;

void clear() {
	for (int i = 0; i < MAXN; i++) {
		for (int j = 0; j < MAXN; j++) {
			for (int k = 0; k < MAXF; k++) {
				dp[i][j][k] = INF;
				table[i][j] = INF;
			}
		}
	}
}

int readInt() {
	ld x;
	cin >> x;
	return x * 100 + 0.5;
}

void read() {
	cin >> n >> m >> f >> k;
	for (int i = 0; i < k; i++) {
		int x, y;
		cin >> x >> y;
		x--;
		y--;
		table[x][y] = min(table[x][y], readInt());
	}

	/*cout << "n =, m =, k =, f = " << n << " " << m << " " << k << " " << f << endl;
	cout << "table = " << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << table[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;*/
}

bool check(int x, int y) {
	return x >= 0 && x < n && y >= 0 && y < m;
}

vector<int> dx = {-1, 0, 1, 0}, dy = {0, 1, 0, -1};

int ans;

set<event> q;

void relax(int x, int y, int cost, int have) {
	if (dp[x][y][have] <= cost) return;
	q.erase({x, y, dp[x][y][have], have});
	dp[x][y][have] = cost;
	q.insert({x, y, dp[x][y][have], have});
}

void run() {
	if (f >= MAXF) {
		ans = 0;
		return;
	}	
	//cout << "puhh" << endl;
	q.insert({0, 0, 0, f});
	dp[0][0][f] = 0;
	while (!q.empty()) {
		auto v = *q.begin();
		q.erase(q.begin());
		if (table[v.x][v.y] != INF && v.have + 1 <= f)
			relax(v.x, v.y, v.cost + table[v.x][v.y], v.have + 1);
		if (!v.have) continue;
		for (int i = 0; i < 4; i++) {
			int fx = v.x + dx[i];
			int fy = v.y + dy[i];
			if (!check(fx, fy)) continue;
			relax(fx, fy, v.cost, v.have - 1);
		}
	}

	ans = INF;
	for (int i = 0; i < MAXF; i++)
		chkmin(ans, dp[n - 1][m - 1][i]);
}

void write() {
	if (ans == INF) {
		cout << -1 << "\n";
		return;
	}
	if (ans == 0) {
		cout << "0.00" << "\n";
		return;
	}
	int a = ans % 10;
	ans /= 10;
	int b = ans % 10;
	ans /= 10;
	cout << ans << "." << b << a << "\n";
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t--) {
		clear();
		read();
		run();
		write();
	}
	return 0;
}