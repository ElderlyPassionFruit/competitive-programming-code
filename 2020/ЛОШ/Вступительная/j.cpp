#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const ld EPS = 1e-8;

int sign(ld x) {
	if (x > EPS) return 1;
	if (x < -EPS) return -1;
	return 0;
}

struct point{
	ld x, y;
	point() {
		x = 0, y = 0;
	}
	point(ld _x, ld _y) {
		x = _x, y = _y;
	}
};

bool operator==(const point & a, const point & b) {
	return sign(a.x - b.x) == 0 && sign(a.y - b.y) == 0;
}

point operator-(const point & a, const point & b) {
	return point(a.x - b.x, a.y - b.y);
}

point operator+(const point & a, const point & b) {
	return point(a.x + b.x, a.y + b.y);
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

ld dist(point a) {
	return sqrt(sq(a.x) + sq(a.y));
}

ld dist(point a, point b) {
	return dist(a - b);
}

struct line{
	ld a, b, c;
	line() {}
	line(point x, point y) {
		a = y.y - x.y;
		b = x.x - y.x;
		c = x.y * y.x - x.x * y.y;
		ld d = dist(point(a, b));
		a /= d;
		b /= d;
		c /= d;
	}
};

/*
a1 * x + b1 * y + c1 = 0
a2 * x + b2 * y + c2 = 0

a1 * a2 * x + b1 * a2 * y + c1 * a2 = 0
a1 * a2 * x + b2 * a1 * y + c2 * a1 = 0

y = (c2 * a1 - c1 * a2) / (b1 * a2 - b2 * a1)

a1 * x + (b1 * c2 * a1 - c1 * a2 * b1 + c1 * b1 * a2 - b2 * a1 * c1) / (...)  = 0

x + (b1 * c2 - b2 * c1) / (...)  = 0

x = (c1 * b2 - b1 * c2) / (b1 * a2 - b2 * a1)
y = (c2 * a1 - c1 * a2) / (b1 * a2 - b2 * a1)

*/ 

point cross(line l, line m) {
	ld d = (ld)l.b * m.a - (ld)l.a * m.b;
	if (!sign(d)) return {};
	ld dx = (ld)l.c * m.b - (ld)l.b * m.c;
	ld dy = (ld)l.a * m.c - (ld)l.c * m.a;
	ld x = dx / d;
	ld y = dy / d;
	return {x, y};
}

bool check(line l, point a) {
	return sign(l.a * a.x + l.b * a.y + l.c) == 0;
}

#define vec point
ld dist(point a, point b, point x) {
	line l = line(a, b);
	a = x;
	return abs(l.a * a.x + l.b * a.y + l.c) / sqrt(sq(l.a) + sq(l.b));
}

bool check_on_segment(point a, point b, point x) {
	return sign(dist(a, b) - dist(a, x) - dist(b, x)) == 0;
}

bool check_on_ray(point s, point f, point x) {
	if (s == x) return true;
	vec v1 = f - s;
	vec v2 = x - s;
	return sign(v1 ^ v2) == 0 && sign(v1 * v2) == 1;
}

bool check_cross(point s, vec v, point a, point b) {
	point nxt = s + v;
	point have = cross(line(s, nxt), line(a, b));
	if (!check_on_segment(a, b, have)) return false;
	if (!check_on_ray(s, nxt, have)) return false;
	return true;
}

int n;
vector<pair<point, ld>> p;
vec v;

void read() {
	cin >> n;
	p.resize(n);
	for (auto &i : p) {
		cin >> i.first.x >> i.first.y >> i.second;
	}
	cin >> v.x >> v.y;
	assert(sign(v.x) || sign(v.y));
	ld d = dist(v);
	v.x /= d;
	v.y /= d;
	ld x = 0;
	for (auto i : p) {
		chkmax(x, dist(i.first));
	}
	for (auto &i : p) {
		i.first.x /= x;
		i.first.y /= x;
	}
}

int ans;

void make(vec & v, ld d) {
	ld D = dist(v);
	v.x /= D;
	v.y /= D;
	v.x *= d;
	v.y *= d;
}

void run() {
	ans = 0;
	point s;
	ld a = 1;
	while (a >= 0.0001 - EPS) {
		for (auto i : p) {
			if (check_on_ray(s, s + v, i.first)) {
				ans++;
				return;
			}
		}

		bool flag = false;

		for (int i = 0; i < n; i++) {
			point A = p[i].first;
			point B = p[(i + 1) % n].first;
			if (!check_cross(s, v, A, B)) continue;
			point nxt = cross(line(s, s + v), line(A, B));
			if (nxt == s) continue;

			a *= p[i].second;
			vec norm = B - A;
			norm = vec(-norm.y, norm.x);
			vec fv = B - A;
			make(fv, dist(nxt, nxt + norm, s));
			if (!check(line(nxt, nxt + norm), fv + s)) {
				fv.x *= -1;
				fv.y *= -1;
			}
			assert(check(line(nxt, nxt + norm), fv + s));
			v = s + fv + fv - nxt;
			s = nxt;
			flag = true;
			break;
		}

		assert(flag);
		ans++;
	}
}

void write() {
	cout << ans << endl;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cout.precision(20);
	cout.setf(ios::fixed);
	read();
	run();
	write();
	return 0;
}