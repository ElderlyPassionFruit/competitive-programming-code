#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 710;
int h[MAXN][MAXN], v[MAXN][MAXN];
int n;
int ans;

void read() {
/*	cin >> n;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			cin >> h[i][j];

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			cin >> v[i][j];
*/
	n = 700;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			h[i][j] = rand() % ((int) 1e6) + 1;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			v[i][j] = rand() % ((int) 1e6) + 1;
}

struct pt{
	int x, y;
	pt() {

	}
	pt(int a, int b) {
		x = a, y = b;
	}
};

bool operator==(pt a, pt b) {
	return tie(a.x, a.y) == tie(b.x, b.y);
}

struct num{
	int x, y;
	num() {

	}

	num(int a, int b) {
		x = abs(a), y = abs(b);
		if (!x && !y) return;
		if (!x || !y) {
			chkmin(x, 1);
			chkmin(y, 1);
			return;
		}
		int g = __gcd(x, y);
		x /= g;
		y /= g; 
	} 
};

bool operator==(num a, num b) {
	return tie(a.x, a.y) == tie(b.x, b.y);
}

bool operator!=(num a, num b) {
	return !(a == b);
}

bool operator<(num a, num b) {
	return tie(a.x, a.y) < tie(b.x, b.y);
}

struct edge{
	pt a, b;
};

vector<edge> zero;
map <num, vector<edge> > ed;
num good = {0, 0};

void add_edge(pt a, pt b, num t) {
	if (t == good) {
		zero.push_back({a, b});
		return;
	}
	ed[t].push_back({a, b});
}

bool check(int x, int y) {
	return x >= 1 && x <= n && y >= 1 && y <= n;
}

void build_time() {
	vector<int> dx = {0, 1}, dy = {1, 0};
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			for (int k = 0; k < 2; k++) {
				int x = i + dx[k];
				int y = j + dy[k];
				if (!check(i, j) || !check(x, y)) continue;
				int dh = h[i][j] - h[x][y];
				int dv = v[x][y] - v[i][j];
				if (dh != 0 && dv == 0) continue;
				if (dh * dv < 0) continue;
				add_edge({i, j}, {x, y}, {dh, dv});
			}
		}
	}
}

pt par[MAXN][MAXN];
int sz[MAXN][MAXN];

void make() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			par[i][j] = {i, j};
			sz[i][j] = 1;
		}
	}
}

pt get_par(pt v) {
	if (v == par[v.x][v.y]) return v;
	return get_par(par[v.x][v.y]);
}

vector<edge> st; 

void uni(pt a, pt b) {
	if (sz[a.x][a.y] < sz[b.x][b.y])
		swap(a, b);
	par[b.x][b.y] = a;
	sz[a.x][a.y] += sz[b.x][b.y];
	chkmax(ans, sz[a.x][a.y]);
	st.push_back({a, b});
}

void rev() {
	pt a = st.back().a;
	pt b = st.back().b;
	st.pop_back();
	sz[a.x][a.y] -= sz[b.x][b.y];
	par[b.x][b.y] = b;
}

void clear() {
	while (!st.empty()) {
		rev();
	}
}

void solve() {
	ans = 1;
	make();
	for (auto i : zero) {
		pt a = get_par(i.a);
		pt b = get_par(i.b);
		if (a == b) continue;
		uni(a, b);
	}
	st.clear();
	for (auto i : ed) {
		for (auto j : i.second) {
			pt a = get_par(j.a);
			pt b = get_par(j.b);
			if (a == b) continue;
			uni(a, b);
		}
		clear();
	}
}

void run() {
	build_time();
	solve();
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