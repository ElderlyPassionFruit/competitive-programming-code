#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std;
#define pb push_back
#define all(x) x.begin(), x.end()	

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct pt{
	int x, y;
	pt() {
		x = 0, y = 0;
	}
	pt(int a, int b) {
		x = a, y = b;
	}
};

inline pt operator-(const pt & a, const pt & b) {
	return pt(a.x - b.x, a.y - b.y);
}

inline int operator*(const pt & a, const pt & b) {
	return a.x * b.x + a.y * b.y;
}

inline bool operator<(const pt & a, const pt & b) {
	return tie(a.x, a.y) < tie(b.x, b.y);
}

struct line {
	int a, b, c;
	line() {
		a = b = c = 0;
	}
	line(pt x, pt y) {
		a = y.y - x.y;
		b = x.x - y.x;
		c = x.y * y.x - x.x * y.y;
	}
};

inline pt eval_x(const line & l, int x) {
	return pt(x, (-l.a * x - l.c) / l.b);
}

inline pt eval_y(const line & l, int y) {
	return pt((-l.b * y - l.c) / l.a, y);
}

#define vec pt

inline long long sq(long long x) {
	return x * x;
}

inline int check(const line & l, const pt & x, const pt & s, const pt & f) {
	vec v1 = x - s;
	vec v2 = x - f;
	vec x1 = s - f;
	vec x2 = f - s;
	if ((v1 * x2) < 0 || (v2 * x1) < 0) return 0;
	int ans = sqrt(100LL * sq(l.a * x.x + l.b * x.y + l.c) / (sq(l.a) + sq(l.b))) + 1;
	if (ans < 1 || ans > 9) ans = 0;
	return ans;
}

const int MAXN = 510, MAXR = 10;
int n;
int table[MAXN][MAXN][MAXR];

int col;
int used[MAXN][MAXN];

const vector<int> dx = {0, -1, 1, 2};
const vector<int> dy = {0, -1, 1, 2};


void read() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		int x, y, r;
		char c;
		cin >> x >> y >> c >> c >> r;
		table[x][y][r]++;
	}

	for (int x = 1; x < MAXN; x++)
		for (int y = 1; y < MAXN; y++) {
			for (int i = MAXR - 2; i >= 1; i--)
				table[x][y][i] += table[x][y][i + 1];
			assert(table[x][y][1] <= 1);	
		}
}	

inline bool check(pt & x) {
	return x.x >= 1 && x.x <= 500 && x.y >= 1 && x.y <= 500;
}

inline int get(const line & l, const pt & s, const pt & f, pt x) {
	if (!check(x)) return 0;
	if (used[x.x][x.y] == col) return 0;
	used[x.x][x.y] = col;
	int ans = 0;
	ans = table[x.x][x.y][check(l, x, s, f)];
	return ans;
}

inline int stupid_h(const pt & s, const pt & f, const line & l) {
	int sx = s.x;
	int fx = f.x;
	if (fx < sx) swap(sx, fx);
	int ans = 0;
	for (int i = sx; i <= fx; i++) {
		ans += get(l, s, f, pt(i, s.y));
	}
	return ans;
}

inline int solve_h(const pt & s, const pt & f, const line & l) {
	if (l.a == 0) return stupid_h(s, f, l);
	int sy = s.y;
	int fy = f.y;
	if (fy < sy) {
		swap(sy, fy);
	}
	int ans = 0;
	for (int i = sy; i <= fy; i++) {
		pt help = eval_y(l, i);
		for (auto j : dx) {
			help.x += j;
			ans += get(l, s, f, help);
			help.x -= j;
		}
	}
	return ans;
}

inline int stupid_w(const pt & s, const pt & f, const line & l) {
	int sy = s.y;
	int fy = f.y;
	if (fy < s.y) {
		swap(sy, fy);
	}
	int ans = 0;
	for (int i = sy; i <= fy; i++) {
		ans += get(l, s, f, pt(s.x, i));
	}
	return ans;
}

inline int solve_w(const pt & s, const pt & f, const line & l) {
	if (l.b == 0) return stupid_w(s, f, l);
	int sx = s.x;
	int fx = f.x;
	if (fx < sx) {
		swap(sx, fx);
	}
	int ans = 0;
	for (int i = sx; i <= fx; i++) {
		pt help = eval_x(l, i);
		for (auto j : dy) {
			help.y += j;
			ans += get(l, s, f, help);
			help.y -= j;
		}
	}
	return ans;
}

inline int solve() {
	pt s, f;
	cin >> s.x >> s.y >> f.x >> f.y;
	line l(s, f);
	col++;
	return solve_h(s, f, l) + solve_w(s, f, l);
}

vector<int> ans;

inline void run() {
	int q;
	col = 0;
	cin >> q;
	while (q--) {
		cout << solve() << "\n";
	}
}

inline void write() {

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