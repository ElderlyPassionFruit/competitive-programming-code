#include <bits/stdc++.h>

using namespace std;
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct event{
	int x, y;
};

vector<event> have;
int n, m, d;
event s, f;

void read() {
	cin >> n >> m >> d;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			char x;
			cin >> x;
			if (x == 'S') {
				s.x = i, s.y = j;
			}
			if (x == 'F') {
				f.x = i, f.y = j;
			}
			if (x == 'M') {
				have.push_back({i, j});
			}
		}
	}
}

bool check(int x, int y) {
	return x >= 0 && x < n && y >= 0 && y < m;
}

vector<int> dx = {-1, 0, 1, 0}, dy = {0, 1, 0, -1};

vector<vector<int> > dist_monstrs;
deque <event> q;
	
void relax(int x, int y, int d) {
	if (dist_monstrs[x][y] <= d)
		return;
	dist_monstrs[x][y] = d;
	q.push_back({x, y});
}

void build() {
	dist_monstrs.assign(n, vector<int> (m, 1e9 + 10));
	for (auto i : have) {
		q.push_back(i);
		dist_monstrs[i.x][i.y] = 0;
	}

	while (!q.empty()) {
		event x = q[0];
		q.pop_front();
		int d = dist_monstrs[x.x][x.y];
		for (int i = 0; i < 4; i++) {
			if (check(x.x + dx[i], x.y + dy[i])) {
				relax(x.x + dx[i], x.y + dy[i], d + 1);
			}
		}
	}
}

vector<vector<int> > dist;

bool check2(int x, int y) {
	return check(x, y) && dist_monstrs[x][y] > d;
}

void relax2(int x, int y, int d) {
	if (dist[x][y] <= d)
		return;
	dist[x][y] = d;
	q.push_back({x, y});
}

const int INF = 1e9 + 10;
int ans;

void run() {
	ans = -1;
	build();
	if (dist_monstrs[s.x][s.y] <= d || dist_monstrs[f.x][f.y] <= d) {
		return;
	}
	
	dist.assign(n, vector<int> (m, INF));
	dist[s.x][s.y] = 0;
	q.push_back(s);

	while (!q.empty()) {
		auto x = q[0];
		q.pop_front();
		for (int i = 0; i < 4; i++) {
			if (check2(x.x + dx[i], x.y + dy[i])) {
				relax2(x.x + dx[i], x.y + dy[i], dist[x.x][x.y] + 1);
			}
		}
	}

	if (dist[f.x][f.y] != INF) {
		ans = dist[f.x][f.y];
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