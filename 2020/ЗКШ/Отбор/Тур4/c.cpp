#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct point{
	ld x, y;
	point() {}
	point(ld a, ld b) {
		x = a, y = b;
	}
};

bool operator<(const point & a, const point & b) {
	return tie(a.x, a.y) < tie(b.x, b.y);
}

point operator+(const point & a, const point & b) {
	return point(a.x + b.x, a.y + b.y);
}

point operator-(const point & a, const point & b) {
	return point(a.x - b.x, a.y - b.y);
}

ld operator^(const point & a, const point & b) {
	return a.x * b.y - a.y * b.x;
}

ld operator*(const point & a, const point & b) {
	return a.x * b.x + a.y * b.y;
}

ld sq(ld x) {
	return x * x;
}

#define vec point

ld dist(const vec & a) {
	return sqrt(sq(a.x) + sq(a.y));
}

ld dist(point & a, point b) {
	return dist(a - b);
}

const ld EPS = 1e-9;

bool operator==(const point & a, const point & b) {
	return abs(a.x - b.x) < EPS && abs(a.y - b.y) < EPS;
}

void Unique(vector<point> & p) {
	int n = p.size();
	vector<point> ans;
	for (int i = 0; i < n; i++) {
		bool flag = true;
		for (int j = i + 1; j < n; j++) {
			if (p[i] == p[j]) {
				flag = false;
			}
		}
		if (flag)
			ans.push_back(p[i]);
	}
	p = ans;
}

point p0;

bool cmp(point a, point b) {
	a = a - p0;
	b = b - p0;
	if (abs(a ^ b) < EPS) {
		return dist(a) < dist(b);
	}
	return (a ^ b) > 0;
}

vector<point> convex_hull(vector<point> p) {
	Unique(p);
	int n = p.size();
	if (n == 0) return {};
	for (int i = 0; i < n; i++) {
		if (p[i] < p[0])
			swap(p[i], p[0]);
	}
	vector<point> ans;
	p0 = p[0];
	p.erase(p.begin());
	ans.push_back(p0);
	while (!p.empty()) {
		p0 = ans.back();
		int pos = 0;
		for (int i = 0; i < p.size(); i++) {
			if (cmp(p[i], p[pos]))
				pos = i;
		}
		ans.push_back(p[pos]);
		p.erase(p.begin() + pos);
	}

	return ans;
}

struct line{
	ld a, b, c;
	line() {}
	line(point x, point y) {
		a = y.y - x.y;
		b = x.x - y.x;
		c = x.y * y.x - x.x * y.y;
	}
};

ld dist(const point & a, const line & l) {
	return abs(l.a * a.x + l.b * a.y + l.c) / sqrt(sq(l.a) + sq(l.b));
}

void norm(vec & a, ld d) {
	ld have = dist(a);
	a.x /= have;
	a.y /= have;
	a.x *= d;
	a.y *= d;
}

struct circle{
	point o;
	ld r;
	circle() {}
	circle(point a, ld b) {
		o = a, r = b;
	}
};

bool check(point a, line l) {
	return dist(a, l) < EPS;
}

vector<point> cross(circle o, line l) {
	ld d = dist(o.o, l);
	if (d >= o.r - EPS) return {};
	vec v = vec(l.a, l.b);
	norm(v, d);
	if (!check(o.o + v, l))
		v = vec(-v.x, -v.y);
	point a = o.o + v;
	d = sqrt(sq(o.r) - sq(d));
	v = vec(-l.b, l.a);
	norm(v, d);
	return {a + v, a - v};
}

bool check(point a, point b, point x) {
	return abs(dist(a, b) - dist(a, x) - dist(b, x)) < EPS;
}

bool check(point a, circle o) {
	return abs(dist(a, o.o) - o.r) < EPS;
}

bool check_del(point a, circle o) {
	return !check(a, o) && o.r > dist(a, o.o);
}

const ld PI = acos(-1);

ld get_dist(circle o, point a, point b) {
	a = a - o.o;
	b = b - o.o;
	ld x = atan2(a ^ b, a * b);
	if (x < 0) x = 2 * PI + x;
	return x * o.r;
}

int n;
vector<point> a;
circle o;

void read() {
	n = 4;
	ld x1, y1, x2, y2;
	cin >> x1 >> y1 >> x2 >> y2;
	a.push_back({x1, y1});
	a.push_back({x2, y1});
	a.push_back({x2, y2});
	a.push_back({x1, y2});
	cin >> o.o.x >> o.o.y >> o.r;
}

ld ans;

void run() {

	vector<point> p;
	for (int i = 0; i < n; i++) {
		if (check_del(a[i], o)) continue;
		p.push_back(a[i]);
	}
	for (int i = 0; i < n; i++) {
		point x = a[i];
		point y = a[(i + 1) % n];
		vector<point> add = cross(o, line(x, y));
		for (auto j : add) {
			if (!check(x, y, j)) continue;
			if (check_del(j, o)) continue;
			p.push_back(j);
		}
	}
	p = convex_hull(p);
	if (p.size() <= 1) {
		ans = 2 * PI * o.r;
		return;
	}
	int n = p.size();
	ans = 0;
	ld add = 0;
	for (int i = 0; i < n; i++) {
		point x = p[i];
		point y = p[(i + 1) % n];

		if (check(x, o) && check(y, o)) {
			add += get_dist(o, x, y);
		}
		else {
			ans += dist(x, y);
		}
	}
	ans += abs(add);
}

void write() {
	cout << ans << endl;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cout.setf(ios::fixed);
	cout.precision(20);
	read();
	run();
	write();
	return 0;
} 