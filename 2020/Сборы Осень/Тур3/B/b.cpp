#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()
using ld = long double;

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct point{
	int x, y;
	point() {}
	point(int a, int b) {
		x = a, y = b;
	}
};

point operator-(const point & a, const point & b) {
	return point(a.x - b.x, a.y - b.y);
}

int operator^(const point & a, const point & b) {
	return a.x * b.y - a.y * b.x;
}

int operator*(const point & a, const point & b) {
	return a.x * b.x + a.y * b.y;
}

struct line{
	int a, b, c;
	line() {}
	line(point x, point y) {
		a = y.y - x.y;
		b = x.x - y.x;
		c = x.y * y.x - x.x * y.y;
	}
};

ld sq(ld x) {
	return x * x;
}

#define vec point

ld dist(vec a) {
	return sqrt(sq(a.x) + sq(a.y));
}

ld dist(point a, point b) {
	return dist(a - b);
}

ld dist(line l, point a) {
	return (ld) (abs(l.a * a.x + l.b * a.y + l.c)) / sqrt(sq(l.a) + sq(l.b));
}

const int INF = 1e18;

bool check(point a, point b, point x) {
	vec v1 = x - a, v2 = b - a;
	if (v1 * v2 < 0) return false;
	v1 = x - b, v2 = a - b;
	if (v1 * v2 < 0) return false;
	return true;
}
 
ld dist(point a, point b, point x) {
	ld ans = INF;
	chkmin(ans, dist(a, x));
	chkmin(ans, dist(b, x));
	if (check(a, b, x)) {
		chkmin(ans, dist(line(a, b), x));
	}
	return ans;
}

ld dist(point a, point b, point c, point d) {
	ld ans = INF;
	chkmin(ans, dist(a, b, c));
	chkmin(ans, dist(a, b, d));
	chkmin(ans, dist(c, d, a));
	chkmin(ans, dist(c, d, b));
	return ans;
}

int n, m;
vector<point> a, b;

void read() {
	cin >> n;
	a.resize(n);
	for (auto &i : a)
		cin >> i.x >> i.y;
	cin >> m;
	b.resize(m);
	for (auto &i : b)
		cin >> i.x >> i.y;
}

ld ans = INF;

const int MAXC = 1e9;

void run() {
	a.push_back({a.back().x, MAXC});
	reverse(all(a));
	a.push_back({a.back().x, -MAXC});
	reverse(all(a));
	n = a.size();

	b.push_back({b.back().x, MAXC});
	reverse(all(b));
	b.push_back({b.back().x, -MAXC});
	reverse(all(b));
	m = b.size();

	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < m - 1; j++) {
			chkmin(ans, dist(a[i], a[i + 1], b[j], b[j + 1]));
		}
	}
}

void write() {
	cout << fixed << setprecision(20) << ans << endl;
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