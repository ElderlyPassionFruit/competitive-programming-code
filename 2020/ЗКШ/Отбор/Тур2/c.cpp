#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct circle{
	ll x, y, r;
	circle() {}
};

int n;
vector<circle> a;

void read() {
	cin >> n;
	a.resize(n);
	for (auto &i : a) {
		cin >> i.x >> i.y >> i.r;
	}
}

ll sq(ll x) {
	return x * x;
}

ld dist(int i, int j) {
	return sqrt(sq(a[i].x - a[j].x) + sq(a[i].y - a[j].y));
}

bool check_correct(int i, int j, ld d) {
	return dist(i, j) > d + a[i].r + a[j].r;
}

bool check_edge(int i, int j, ld d) {
	return dist(i, j) <= a[i].r + a[j].r + 2 * d;
}

void dfs(int v, vector<vector<int> > & g, vector<int> & color, int c, bool & flag) {
	color[v] = c;
	for (auto i : g[v]) {
		if (!flag) return;
		if (color[i] == 0) {
			dfs(i, g, color, 3 - c, flag);
		} 
		else {
			if (color[i] != 3 - c) {
				flag = false;
				return;
			}
		}
	}
}

bool check(ld d) {
	vector<vector<int> > g(n);
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (!check_correct(i, j, d)) return false;
			if (check_edge(i, j, d)) {
				g[i].push_back(j);
				g[j].push_back(i);
			}
		}
	}

	vector<int> color(n, 0);
	for (int i = 0; i < n; i++) {
		if (!color[i]) {
			bool flag = true;
			dfs(i, g, color, 1, flag);
			if (!flag) return false;
		}
	}
	return true;
}

ld ans;

void run() {
	if (!check(0)) {
		cout << -1 << endl;
		exit(0);
	}
	ld l = 0, r = 1e9;
	while (abs(l - r) > 1e-7) {
		ld m = (l + r) / 2;
		if (check(m))
			l = m;
		else
			r = m;
	}
	ans = l;
}

void write() {
	cout.precision(20);
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