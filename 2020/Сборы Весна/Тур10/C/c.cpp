#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

void no() {
	cout << -1 << endl;
	exit(0);
}

struct edge{
	int to, type;
	edge() {}
	edge(int _to, int _type) {
		to = _to, type = _type;
	}
};

struct rect{
	int r1, c1, r2, c2;
	rect() {}
	rect(int _r1, int _c1, int _r2, int _c2) {
		r1 = _r1, c1 = _c1, r2 = _r2, c2 = _c2;
	}
};

const int MAXN = 1e6 + 10;
int h, w;
vector<vector<int>> a;
vector<vector<char>> type;
vector<edge> g[MAXN];
rect have[MAXN];
vector<vector<char>> my_rect[MAXN];
int n;

void read() {
	cin >> h >> w;
	a.resize(h, vector<int> (w, -1));
	type.resize(h, vector<char> (w, ' '));
	cin >> n;
	for (int i = 0; i < n; i++) {
		int r1, r2, c1, c2;
		cin >> r1 >> c1 >> r2 >> c2;
		r1--; r2--; c1--; c2--;
		have[i] = {r1, c1, r2, c2};
		my_rect[i].resize(r2 - r1 + 1, vector<char> (c2 - c1 + 1, ' '));
		for (int x = r1; x <= r2; x++) {
			for (int y = c1; y <= c2; y++) {
				char have;
				cin >> have;
				my_rect[i][x - r1][y - c1] = have;
				if (a[x][y] != -1) {
					if (have == type[x][y]) {
						g[i].push_back({a[x][y], 0});
						g[a[x][y]].push_back({i, 0});
					} else {
						g[i].push_back({a[x][y], 1});
						g[a[x][y]].push_back({i, 1});
					}
				}
				a[x][y] = i;
				type[x][y] = have;
			}
		}
	}
}

bool used[MAXN];
int color[MAXN];
vector<int> comps[MAXN];
int comp;

void dfs(int v, int c) {
	used[v] = true;
	color[v] = c;
	comps[comp].push_back(v);
	for (auto i : g[v]) {
		int to = i.to;
		int type = i.type;
		int nxt = (type == 0 ? c : 3 - c);
		if (!used[to]) {
			dfs(to, nxt);
		} else {
			if (color[to] != nxt) {
				no();
			}
		}
	}
}

void build() {
	comp = 0;
	for (int i = 0; i < n; i++) {
		if (!used[i]) {
			dfs(i, 1);
			comp++;
		}
	}
}

int ans;

void paint() {
	type.assign(h, vector<char> (w, ' '));
	for (int i = 0; i < comp; i++) {
		int cnt_all = 0, cnt_0 = 0;
		for (auto j : comps[i]) {
			for (int x = have[j].r1; x <= have[j].r2; x++) {
				for (int y = have[j].c1; y <= have[j].c2; y++) {
					char now = my_rect[j][x - have[j].r1][y - have[j].c1];
					if (color[j] == 2) {
						now = (1 - (now - '0')) + '0';
					}
					if (type[x][y] != ' ' && type[x][y] != now) no();
					if (type[x][y] != ' ') continue;
					type[x][y] = now;
					cnt_all++;
					cnt_0 += now == '0';
				}
			}
		}
		if (cnt_all - cnt_0 <= cnt_0) continue;
		for (auto j : comps[i]) {
			for (int x = have[j].r1; x <= have[j].r2; x++) {
				for (int y = have[j].c1; y <= have[j].c2; y++) {
					char now = my_rect[j][x - have[j].r1][y - have[j].c1];
					if (color[j] == 1) {
						now = (1 - (now - '0')) + '0';
					}
					type[x][y] = now;
				}
			}
		}
	}
	for (auto &i : type) {
		for (auto &j : i) {
			if (j == ' ') {
				j = '0';
			}
			ans += j == '0';
		}
	}
}

void run() {
	build();
	paint();
}

void write() {
	cout << ans << "\n";
	for (auto i : type) {
		for (auto j : i) {
			cout << j << " ";
		}
		cout << "\n";
	}
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