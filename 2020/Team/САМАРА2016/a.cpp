#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int MAXN = 51;
char table[MAXN][MAXN];
int n, m;


bool check(int x, int y) {
	return x >= 0 && y >= 0 && x < n && y < m && table[x][y] != '#';
}

struct pt{
	int x, y;
	pt() {}
	pt(int a, int b) {
		x = a, y = b;
	}
};


bool operator==(const pt & a, const pt & b) {
	return tie(a.x, a.y) == tie(b.x, b.y);
}

bool operator<(const pt & a, const pt & b) {
	return tie(a.x, a.y) < tie(b.x, b.y);
}

pt par[MAXN][MAXN];
int sz[MAXN][MAXN];

pt get_par(pt v) {
	if (v == par[v.x][v.y]) return v;
	return par[v.x][v.y] = get_par(par[v.x][v.y]);
}


void uni(pt a, pt b) {
	a = get_par(a);
	b = get_par(b);
	if (a == b) return;
	if (sz[a.x][a.y] < sz[b.x][b.y]) swap(a, b);
	par[b.x][b.y] = a;
	sz[a.x][a.y] += sz[b.x][b.y];
}


vector<int> dx = {-1, 0, 1, 0};
vector<int> dy = {0, 1, 0, -1};

void make() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			par[i][j] = {i, j};
			sz[i][j] = 1;
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (!check(i, j)) continue;
			if (table[i][j] != '.') continue;
			for (int k = 0; k < 4; k++) {
				int x = i + dx[k];
				int y = j + dy[k];
				if (!check(x, y)) continue;
				if (table[x][y] != '.') continue;
				uni({i, j}, {x, y});
			}
		}
	}
}

bool check() {
	set<pt> pts;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (table[i][j] == '.')
				pts.insert(get_par({i, j}));
		}
	}
	return pts.size() == 1;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n >> m;
	vector<pt> have;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> table[i][j];
			if (table[i][j] == '?')
				have.push_back({i, j});
		}
	}
	
	vector<bool> used(have.size(), false);
	make();

	for (int j = 0; j < have.size(); j++)
	for (int i = 0; i < have.size(); i++) {
		if (used[i]) continue;
		int cnt = 0;
		for (int k = 0; k < 4; k++) {
			int nx = have[i].x + dx[k];
			int ny = have[i].y + dy[k];
			if (!check(nx, ny)) continue;
			if (table[nx][ny] != '.') continue;
			pt a = get_par({nx, ny});
			cnt++;
			uni(a, have[i]);
		}
		if (cnt) {
			used[i] = true;
			table[have[i].x][have[i].y] = '.';
		}
	}

	set<pt> pts;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (table[i][j] == '.')
				pts.insert(get_par({i, j}));
		}
	}

	if (pts.size() > 1) {
		cout << "Impossible";
		return 0;
	}

	for (int i = 0; i < have.size(); i++) {
		if (!used[i]) continue;
		table[have[i].x][have[i].y] = '#';
		make();
		if (check()) {
			cout << "Ambiguous";
			return 0;
		}
		table[have[i].x][have[i].y] = '.';
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (table[i][j] == '?')
				cout << '#';
			else
				cout << table[i][j];
		}
		cout << endl;
	}
	return 0;
}











//сосать


