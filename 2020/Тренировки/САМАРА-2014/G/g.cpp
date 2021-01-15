#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const ld EPS = 1e-9;

int sign(ld x) {
	if (x > EPS) return 1;
	if (x < -EPS) return -1;
	return 0;
}

struct point{
	ld x, y;
	point() {}
	point(ld _x, ld _y) {
		x = _x, y = _y;
	}
};

point operator-(const point & a, const point & b) {
	return point(a.x - b.x, a.y - b.y);
}

point operator+(const point & a, const point & b) {
	return point(a.x + b.x, a.y + b.y);
}

ld sq(ld x) {
	return x * x;
}

ld dist(point a) {
	return sqrt(sq(a.x) + sq(a.y));
}

ld dist(point a, point b) {
	return dist(a - b);
}

struct line{
	ld a, b, c;
	line() {}
	line(ld _a, ld _b, ld _c) {
		a = _a, b = _b, c = _c;
	}
};

bool check(line l, point a) {
	return sign(l.a * a.x + l.b * a.y + l.c) == 0;
}

ld dist(line l, point a) {
	return abs(l.a * a.x + l.b * a.y + l.c) / sqrt(l.a * l.a + l.b * l.b);
}

struct circle{
	ld r;
	point o;
	circle() {}
};

bool check(circle o, point a) {
	return sign(o.r - dist(o.o, a)) >= 0;
}

#define vec point

void norm(vec & v, ld d) {
	ld D = dist(v);
	v.x /= D;
	v.y /= D;
	v.x *= d;
	v.y *= d;
}

vector<point> cross(circle o, line l) {
	if (sign(o.r - dist(l, o.o)) == -1) return {};
	vec v = vec(l.a, l.b);
	norm(v, dist(l, o.o));
	point a = o.o + v;
	if (!check(l, a)) a = o.o - v;
	assert(check(l, a));
	if (sign(o.r - dist(l, o.o)) == 0) return {a};
	ld d = sqrt(sq(o.r) - sq(dist(l, o.o)));
	v = vec(-l.b, l.a);
	norm(v, d);
	return {a + v, a - v};
}

vector<point> cross(circle a, circle b) {
	if (sign(a.r + b.r - dist(a.o, b.o)) == -1) return {};
	if (a.r < b.r) swap(a, b);
	if (sign(a.r - (b.r + dist(a.o, b.o))) == 1) return {};
	return cross(a, line(2 * (b.o.x - a.o.x), 2 * (b.o.y - a.o.y), sq(a.o.x) + sq(a.o.y) + sq(b.r) - sq(b.o.x) - sq(b.o.y) - sq(a.r)));
}


void add(vector<point> & have, circle a, circle b) {
	auto now = cross(a, b);
	for (auto i : now) {
		have.push_back(i);
	}
}

bool check(point x, circle a, circle b, circle c) {
	return check(a, x) && check(b, x) && check(c, x);
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	ld r;
	circle a, b, c;
	cin >> r >> a.o.x >> a.o.y >> b.o.x >> b.o.y >> c.o.x >> c.o.y;
	a.r = r, b.r = r, c.r = r;
	vector<point> have;
	add(have, a, b);
	add(have, a, c);
	add(have, b, c);
	cout.precision(20);
	cout.setf(ios::fixed);
	for (auto i : have) {
		if (check(i, a, b, c)) {
			cout << "YES\n";
			cout << i.x << " " << i.y << "\n";
			return 0;
		}
	}
	cout << "NO\n";
	return 0;
}