#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 1e3 + 10;
char table[MAXN][MAXN];
int n, m, k;

void read() {
	cin >> n >> m >> k;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> table[i][j];
		}
	}
}

struct pt{
	int x, y;
	pt() {
	}
	pt(int a, int b) {
		x = a, y = b;
	}
};

bool operator==(const pt & a, const pt & b) {
	return tie(a.x, a.y) == tie(b.x, b.y);
}

pt par[MAXN * 2][MAXN * 2];
int sz[MAXN * 2][MAXN * 2];
int cnt[MAXN * 2][MAXN * 2];

pt get_par(pt v) {
	if (par[v.x][v.y] == v) return v;
	return par[v.x][v.y] = get_par(par[v.x][v.y]);
}

void uni(pt a, pt b, int add) {
	a = get_par(a);
	b = get_par(b);
	cnt[a.x][a.y] += add;
	if (a == b) return;
	if (sz[a.x][a.y] < sz[b.x][b.y]) swap(a, b);
	sz[a.x][a.y] += sz[b.x][b.y];
	cnt[a.x][a.y] += cnt[b.x][b.y];
	par[b.x][b.y] = a;
}

void build() {
	for (int i = 0; i < MAXN * 2; i++) {
		for (int j = 0; j < MAXN * 2; j++) {
			par[i][j] = {i, j};
			sz[i][j] = 1;
			cnt[i][j] = 0;
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (table[i][j] == '.') continue;
			pt up = pt(i * 2, j * 2 + 1);
			pt down = pt(i * 2 + 2, j * 2 + 1);
			pt left = pt(i * 2 + 1, j * 2);
			pt right = pt(i * 2 + 1, j * 2 + 2);
			if (table[i][j] == '/') {
				uni(up, left, 1);
				uni(down, right, 1);
			}
			else {
				uni(up, right, 1);
				uni(down, left, 1);
			}
		}
 	}
}

bool check_cycle(pt a) {
	return sz[a.x][a.y] == cnt[a.x][a.y];
}

void calc() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (k == 0) return;
			if (table[i][j] == '.') continue;
			pt up = pt(i * 2, j * 2 + 1);
			up = get_par(up);
			pt down = pt(i * 2 + 2, j * 2 + 1);
			down = get_par(down);
			if (check_cycle(up) || check_cycle(down)) {
				uni(up, down, 0);
				k--;
			}
		}
	}
}

bool operator<(const pt & a, const pt & b) {
	return tie(a.x, a.y) < tie(b.x, b.y);
}

int ans;

void make_ans() {
	ans = 0;
	set<pt> have;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			vector<int> dx = {0, 2, 1, 1};
			vector<int> dy = {1, 1, 0, 2};
			for (int k = 0; k < 4; k++) {
				pt x = pt(dx[k] + 2 * i, dy[k] + 2 * j);
				x = get_par(x);
				if (cnt[x.x][x.y])
					have.insert(x);
			}
		}
	}
	ans = have.size();
	for (auto i : have) {
		if (!k) break;
		if (cnt[i.x][i.y] != sz[i.x][i.y]) continue;
		k--;
		ans--;
	}
}

void run() {
	build();
	//calc();
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