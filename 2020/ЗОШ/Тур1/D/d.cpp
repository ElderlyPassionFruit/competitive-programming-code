#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
#define int ll
const int MAXN = 510;
int table[MAXN][MAXN];
int n, m;
int x, y;

void read() {
	//cout << "puhh" << endl;
	cin >> n >> m;
	//cout << "puhh" << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> table[i][j];
		}
	}
	//cout << "puhh" << endl;
	cin >> x >> y;
	x--;
	y--;
}

ll ans;

const int INF = 1e18;
int dp[MAXN][MAXN];

void build() {

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			dp[i][j] = INF;
		}
	}
}

vector<int> dx = {-1, -1, -1, 0, 1, 1, 1, 0};
vector<int> dy = {-1, 0, 1, 1, 1, 0, -1, -1};

bool check(int x, int y) {
	return x >= 0 && x < n && y >= 0 && y < m;
}

struct event{
	int x, y, dist;
	event() {}
	event(int a, int b, int c) {
		x = a, y = b, dist = c;
	} 
};

bool operator<(const event & a, const event & b) {
	return tie(a.dist, a.x, a.y) < tie(b.dist, b.x, b.y);
}

void djkstra(int x, int y) {
	set<event> q;
	q.insert({x, y, table[x][y]});
	dp[x][y] = table[x][y];
	while (!q.empty()) {
		auto v = *q.begin();
		q.erase(q.begin());
		//cout << v.x << " " << v.y << " " << v.dist << endl;
		for (int i = 0; i < 8; i++) {
			int fx = v.x + dx[i];
			int fy = v.y + dy[i];
			if (!check(fx, fy)) continue;
			if (table[fx][fy] >= 0) continue;
			if (dp[fx][fy] <= max(v.dist, table[fx][fy])) continue;
			q.erase({fx, fy, dp[fx][fy]});
			dp[fx][fy] = max(v.dist, table[fx][fy]);
			q.insert({fx, fy, dp[fx][fy]});
		}
	}
}

void make_ans() {
	ans = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (dp[i][j] == INF) continue;
			ans -= dp[i][j];
		}
	}
}

void run() {
	//cout << "puhh" << endl;
	build();
	//cout << "puhh" << endl;
	//cout << "n = , m = " << n << " " << m << endl;
	//cout << endl;
	djkstra(x, y);
	make_ans();
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