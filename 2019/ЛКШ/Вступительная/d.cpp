#include <bits/stdc++.h>

using namespace std;
const int MAXN = 510;

int n, m, t;
int table[MAXN][MAXN];
int fans[MAXN][MAXN];
const int INF = 1e9;

vector <pair <int, pair <pair <int, int> , pair <int, int> > > > edges;
pair <int, int> pred[MAXN][MAXN];
int sz[MAXN][MAXN];
int max_num[MAXN][MAXN];
vector <pair <int, int> > have[MAXN][MAXN];
int animals[MAXN][MAXN];

void make_set(int x, int y) {
	pred[x][y].first = x;
	pred[x][y].second = y;
	sz[x][y] = 1; 
	have[x][y] = {{x, y}};
	max_num[x][y] = 0;
}

pair <int, int> get_pred(int x, int y) {
	if (pred[x][y] == make_pair(x, y))
		return {x, y};
	return pred[x][y] = get_pred(pred[x][y].first, pred[x][y].second);
}

void union_set(int x1, int y1, int x2, int y2, int cost) {
	auto a = get_pred(x1, y1);
	x1 = a.first;
	y1 = a.second;
	auto b = get_pred(x2, y2);
	x2 = b.first;
	y2 = b.second;
	if (x1 == x2 && y1 == y2)
		return;

	if (sz[x1][y1] >= t && sz[x2][y2] >= t)
		return;
	
	if (sz[x1][y1] < sz[x2][y2])
			swap(x1, x2), swap(y1, y2);

	if (sz[x1][y1] < t && sz[x2][y2] < t) {
		sz[x1][y1] += sz[x2][y2];
		max_num[x1][y1] = max(max_num[x1][y1], cost);
		pred[x2][y2] = {x1, y1};
		for (auto i : have[x2][y2])
			have[x1][y1].push_back(i);
	}
	else {
		sz[x2][y2] = INF;
		max_num[x2][y2] = cost;
	}
}


void read() {
	for (int i = 0; i < MAXN; i++) {
		for (int j = 0; j < MAXN; j++) {
			table[i][j] = INF; 
			fans[i][j] = 0;
		}
	} 

	cin >> n >> m >> t;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> table[i][j];
		}
	}
	vector <int> d = {0, 1};

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {

			for (auto dx : d) {
				for (auto dy : d) {
					if (dx == 0 && dy == 0) continue;
					if (dx != 0 && dy != 0) continue;
					int cost = abs(table[i][j] - table[i + dx][j + dy]);
					if (cost > 1e7) continue;

					edges.push_back({cost, {{i, j},{i + dx, j + dy}}});
				}
			}

		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> animals[i][j];
		}
	}

	sort(edges.begin(), edges.end());
}

bool used[MAXN][MAXN];
long long ans;
void run() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			make_set(i, j);
		}
	}

	ans = 0;

	for (auto i : edges) {
		int cost = i.first;
		int x1 = i.second.first.first;
		int y1 = i.second.first.second;
		int x2 = i.second.second.first;
		int y2 = i.second.second.second;

		union_set(x1, y1, x2, y2, cost);
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			auto p = get_pred(i, j);
			int x = p.first;
			int y = p.second;
			if (used[x][y])
				continue;
			used[x][y] = true;
			for (auto ed : have[x][y]) {
				fans[ed.first][ed.second] = max_num[x][y];
			} 
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			ans += animals[i][j] * fans[i][j];
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