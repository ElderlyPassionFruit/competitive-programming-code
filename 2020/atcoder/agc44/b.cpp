#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 510;
int n;
int p[MAXN * MAXN];

void read() {
	cin >> n;
	for (int i = 0; i < n * n; i++) {
		cin >> p[i];
		p[i]--;
	}
}

int ans;

int dist[MAXN][MAXN];
bool used[MAXN][MAXN];

void build() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			used[i][j] = false;
			dist[i][j] = n;
			chkmin(dist[i][j], i);
			chkmin(dist[i][j], n - i - 1);
			chkmin(dist[i][j], j);
			chkmin(dist[i][j], n - j - 1);
		}
	}
}

vector<int> dx = {1, 0, -1, 0}, dy = {0, 1, 0, -1};

bool checkCell(int x, int y) {
	return x >= 0 && x < n && y >= 0 && y < n;
}

void upd(int x, int y) {
	//cout << "x, y = " << x << " " << y << endl;
	ans += dist[x][y];
	//cout << "dist[x][y] = " << dist[x][y] << endl;
	queue<pair<int, int>> q;
	q.push({x, y});
	used[x][y] = true;
	while (!q.empty()) {
		auto v = q.front();
		x = v.first;
		y = v.second;
		q.pop();
		for (int it = 0; it < 4; it++) {
			int nx = x + dx[it], ny = y + dy[it];
			if (!checkCell(nx, ny)) continue;
			int nd = dist[x][y];
			if (!used[x][y]) nd++;
			//cout << "x, y = " << x << " " << y << " used[x][y] = " << used[x][y] << endl;
			if (dist[nx][ny] <= nd) continue;
			dist[nx][ny] = nd;
			//cout << "nx, ny = " << nx << " " << ny << " nd = " << nd << endl;
			q.push({nx, ny});
		}
	}
}

void wr() {
	cout << "dist = " << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << dist[i][j] << " ";
		}
		cout << endl;
	}
	cout << "used = " << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << used[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void run() {
	build();
	//wr();
	ans = 0;
	for (int i = 0; i < n * n; i++) {
		upd(p[i] / n, p[i] % n);
	//	wr();
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