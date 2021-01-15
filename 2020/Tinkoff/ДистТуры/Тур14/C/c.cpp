#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct point{
	int x, y;
	point() {}
	point(int _x, int _y) {
		x = _x, y = _y;
	}
};

point operator-(const point & a, const point & b) {
	return point(a.x - b.x, a.y - b.y);
}

struct circle{
	point o;
	int r;
	circle() {}
	circle(point _o, int _r) {
		o = _o;
		r = _r;
	}
};

ll sq(ll a) {
	return a * a;
}

ld dist(point a) {
	return sqrt(sq(a.x) + sq(a.y));
}

ld dist(point a, point b) {
	return dist(a - b);
}

bool check(circle a, circle b) {
	return dist(a.o, b.o) <= a.r - b.r;
}

struct segment_tree{
	vector<int> tree;
	int n;
	segment_tree() {}
	segment_tree(int sz) {
		n = sz;
		tree.assign(sz, -1);
	}

};

int n;
vector<circle> a;

void read() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		circle o;
		cin >> o.o.x >> o.o.y >> o.r;
		a.push_back(o);
	}
}

const ld PI = acos(-1);

ld ans;

void build() {

}

vector<bool> solve() {
	vector<bool> used(n, 0);

}

void run() {
	build();
	auto used = solve();	
	ans = 0;
	for (int i = 0; i < n; i++) {
		if (used[i]) continue;
		ans += sq(a[i].r);
	}
	ans *= PI;
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