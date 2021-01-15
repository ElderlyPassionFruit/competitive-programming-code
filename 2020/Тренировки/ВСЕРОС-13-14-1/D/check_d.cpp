#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,avx,avx2,mmx,abm")
#pragma GCC optimize("fast-math")
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()
#define abs abs229
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const ld EPS = 1e-10;

ld abs(ld x) {
	if (x < -EPS) return -x;
	if (x > EPS) return x;
	return 0;
}

int sign(ld x) {
	if (abs(x) < EPS) return 0;
	if (x >= EPS) return 1;
	return -1;
}

struct point{
	ld x, y;
	point() {}
	point(ld _x, ld _y) {
		x = _x, y = _y;
	}
};

bool operator==(const point & a, const point & b) {
	return sign(a.x - b.x) == 0 && sign(a.y - b.y) == 0;
}

bool operator!=(const point & a, const point & b) {
	return !(a == b);
}

point operator-(const point & a, const point & b) {
	return point(a.x - b.x, a.y - b.y);
}

ld operator^(const point & a, const point & b){
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

struct line{
	ld a, b, c;
	line() {}
	line(ld _a, ld _b, ld _c) {
		a = _a, b = _b, c = _c;
	}
	line(point x, point y) {
		a = y.y - x.y;
		b = x.x - y.x;
		c = x.y * y.x - x.x * y.y;
		ld d = dist(point(a, b));
		a /= d;
		b /= d;
		c /= d;
		if (sign(a) == -1) {
			a *= -1, b *= -1, c *= -1;
		}
		if (sign(a) == 0&& sign(b) == -1) {
			a *= -1, b *= -1, c *= -1;
		}
	}
};

bool check_cross(line l, line m) {
	ld d = l.b * m.a - l.a * m.b;
	return sign(d) != 0;
}

point cross(line l, line m) {
	ld d = l.b * m.a - l.a * m.b;
	ld dx = m.b * l.c - m.c * l.b;
	ld dy = l.a * m.c - l.c * m.a;
	return {dx / d, dy / d};
}

ld dist(line l, point a) {
	return (l.a * a.x + l.b * a.y + l.c) / sqrt(sq(l.a) + sq(l.b));
}

int half(point a) {
	return sign(a.y) == 1 || (sign(a.y) == 0 && sign(a.x) >= 0);
}

bool operator<(const point & a, const point & b) {
	if (half(a) != half(b)) return half(a);
	if (sign(a ^ b) == 0) {
		return dist(a) < dist(b);
	}
	return sign(a ^ b) == 1;
}

#define vec point

bool check(point a, point b, point x) {
	if (a == b) return a == x;
	vec v1, v2;
	v1 = b - a, v2 = x - a;
	if (sign(v1 * v2) == -1) return false;
	if (sign(v1 ^ v2)) return false;
	v1 = a - b, v2 = x - b;
	if (sign(v1 * v2) == -1) return false;
	return true;
}

bool check_angle(point a, point b, point c, point x) {
	vec v1 = b - a;
	vec v2 = c - a;
	if (sign(v1 ^ v2) == 0) return check(a, b, x) || check(a, c, x) || check(b, c, x);
	if (sign(v1 ^ v2) == -1) swap(v1, v2);
	vec v3 = x - a;
	return sign(v1 ^ v3) >= 0 && sign(v3 ^ v2) >= 0; 
}

bool check(point a, point b, point c, point x) {
//	if (check(a, b, x)) return true;
//	if (check(a, c, x)) return true;
//	if (check(c, b, x)) return true;
//	if (sign((b - a) ^ (c - a)) == 0) return false;
	return check_angle(a, b, c, x) && check_angle(b, a, c, x) && check_angle(c, a, b, x);
	vector<point> p = {a, b, c};
	int n = p.size();
	ld ans = 0;
	for (int i = 0; i < n; i++) {
		point a = p[i];
		point b = p[(i + 1) % n];
		if (check(a, b, x)) return true;
		a = a - x;
		b = b - x;
		ans += atan2(a ^ b, a * b);
	}
	return abs(ans) > EPS;
}
bool check1(point a, point b, point c, point x) {
	vector<point> p = {a, b, c};
	int n = p.size();
	ld ans = 0;
	for (int i = 0; i < n; i++) {
		point a = p[i];
		point b = p[(i + 1) % n];
		if (check(a, b, x)) return true;
		a = a - x;
		b = b - x;
		ans += atan2(a ^ b, a * b);
	}
	return abs(ans) > EPS;
}

mt19937 rnd(time(0));

point get() {
	return point(rnd() % 100000, rnd() % 1000000);
}

signed main() {
	for (int i = 0; i < 1e9; i++) {
		point a, b, c, x;
		a = get(), b = get(), c = get(), x = get();
		if (check(a, b, c, x) != check1(a, b, c, x)) {
			cout << check(a, b, c, x) << " " << check1(a, b, c, x) << endl;
			cout << a.x << " " << a.y << endl;
			cout << b.x << " " << b.y << endl;
			cout << c.x << " " << c.y << endl;
			cout << x.x << " " << x.y << endl;
			break;
		}
		cout << "OK " << i << endl;
	}
	return 0;
}
