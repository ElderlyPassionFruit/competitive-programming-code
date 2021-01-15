#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 310;
int table[MAXN][MAXN];
int n, m;

void read() {
	for (int i = 0; i < MAXN; i++) {
		for (int j = 0; j < MAXN; j++) {
			table[i][j] = 1;
		}
	}
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			table[i][j] = table[i - 1][j] + table[i][j - 1] - table[i - 1][j - 1];
			char x;
			cin >> x;
			if (x == '#')
				table[i][j] += 1;
		}
	}
}

int get(int x1, int y1, int x2, int y2) {
	if (x1 < 1 || x1 > n || y1 < 1 || y1 > m || x2 < 1 || x2 > n || y2 < 1 || y2 > m) return 1e9;
	if (x1 > x2)
		swap(x1, x2);
	if (y1 > y2)
		swap(y1, y2);
	return table[x2][y2] - table[x1 - 1][y2] - table[x2][y1 - 1] + table[x1 - 1][y1 - 1];
}

int get(int x, int y) {
	return get(x, y, x, y);
}

bool dp[MAXN][MAXN];

void clear() {
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			dp[i][j] = false;
}

struct event{
	int x, y;
};

deque<event> q;

void upd(int x, int y) {
	if (x < 1 || x > n || y < 1 || y > m || dp[x][y]) return;
	dp[x][y] = true;
	q.push_back({x, y});
}

vector<int> dx = {-1, 0, 1, 0}, dy = {0, 1, 0, -1};

bool check(int len) {
	clear();
	for (int i = 1; i + len - 1 <= n; i++) {
		if (get(i, 1, i + len - 1, 1) == 0) {
			dp[i][1] = 1;
			q.push_back({i, 1});
		}
	}

	while (!q.empty()) {
		auto p = q[0];
		q.pop_front();
		for (int i = 0; i < 4; i++) {
			if (get(p.x, p.y, p.x + len * dx[i], p.y + len * dy[i]) == 0) {
				upd(p.x + dx[i], p.y + dy[i]);
			}
			if (get(p.x, p.y, p.x + (len - 1) * dx[i], p.y + (len - 1) * dy[i]) == 0) {
				upd(p.x + dx[i] * (len - 1), p.y + dy[i] * (len - 1));
			}
		}	
	}

	for (int i = 1; i + len - 1 <= n; i++) {
		if (dp[i][m] && get(i, m, i + len - 1, m) == 0)
			return true;
	}
	return false;
}

int ans;

void run() {
	int l = 0, r = min(n, m) + 1;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (check(mid))
			l = mid;
		else
			r = mid;
	}
	ans = l;
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