#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()
#define abs abs229
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}


const ld EPS = 1e-9;

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
	return sign(a.y) == 1 || (abs(a.y) < EPS && (a.x > EPS || abs(a.x) < EPS));
}

bool operator<(const point & a, const point & b) {
	if (half(a) != half(b)) return half(a);
	if (sign(a ^ b) == 0) {
		return dist(a) < dist(b);
	}
	return sign(a ^ b) == 1;
}

point p0;
bool cmp(point a, point b) {
	a = a - p0;
	b = b - p0;
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

bool check(vector<point> p, point x) {
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

struct convex_hull{
	set<point> p;
	set<pair<point, point>> sorted;
	point base;
	convex_hull() {}

	void wr() {
		cout << "p = " << endl;
		for (auto i : p) {
			cout << "(" << i.x << ", " << i.y << ")" << endl;
		}
		cout << endl;
		cout << "sorted = " << endl;
		for (auto i : sorted) {
			cout << i.first.x << " " << i.first.y << " " << i.second.x << " " << i.second.y << endl;
		}
		cout << endl;
	}

	void add(point a, point b) {
		sorted.insert({b - a, a});
	}

	void del(point a, point b) {
		sorted.erase({b - a, a});
	}

	void del(set<point>::iterator pos) {
		if (pos == p.begin()) pos = p.end();
		--pos;
		point a = *pos;
		
		pos++;
		if (pos == p.end()) pos = p.begin();
		point b = *pos;
		
		pos++;
		if (pos == p.end()) pos = p.begin();
		point c = *pos;
		
		del(a, b);
		del(b, c);
		add(a, c);
	}

	set<point>::iterator get_pos(point a) {
		int n = p.size();
		if (n < 3) {
			p.insert(a);
			auto it = p.find(a);
			if (n == 1) {
				add(*p.begin(), *(--p.end()));
				add(*(--p.end()), *p.begin());
			}
			return it;
		}
		a = a - base;
		p.insert(a);
		auto it = p.find(a);
		//int i = lower_bound(all(p), a, cmp) - p.begin();
		if (it == p.begin()) it = p.end();
		it--;
		point L = *it;
		it++;
		if (it == p.end()) it = p.begin();
		it++;
		if (it == p.end()) it = p.begin();
		point R = *it;
		del(L, R);
		add(L, a);
		add(a, R);
		return it;
	}

	bool check_good(set<point>::iterator pos) {
		if (p.size() <= 3) return true;

		if (pos == p.begin()) pos = p.end(); 
		--pos;
		point a = *pos;
		
		pos++; if (pos == p.end()) pos = p.begin();
		point b = *pos;

		pos++; if (pos == p.end()) pos = p.begin();
		point c = *pos;
		
		if (check({a, {0, 0}, c}, b)) return false;
		return true;
	}

	bool relax(set<point>::iterator pos) {
		if (p.size() <= 3) return false;
		if (!check_good(pos)) {
			del(pos);	
			p.erase(pos);
			return false;
		}
		pos++;
		if (pos == p.end()) pos = p.begin();

		if (!check_good(pos)) {
			del(pos);
			p.erase(pos);
			return true;
		}
		
		if (pos == p.begin()) pos = p.end();
		pos--;
		if (pos == p.begin()) pos = p.end();
		pos--;

		if (!check_good(pos)) {
			del(pos);
			p.erase(pos);
			return true;
		}
		return false;
	}

	void add(point a) {
		if (p.size() <= 2 && p.count(a)) return;
		if (p.size() >= 3 && p.count(a - base)) return;
		set<point>::iterator pos = get_pos(a);
		if (p.size() <= 2) return;
		if (p.size() == 3) {
			auto p0 = *p.begin();
			p.erase(p.begin());
			auto p1 = *p.begin();
			p.erase(p.begin());
			auto p2 = *p.begin();
			p.erase(p.begin());

			base = point((p0.x + p1.x + p2.x) / 3, (p0.y + p1.y + p2.y) / 3);
			//cout << "p.size() = " << p.size() << endl;
			p.insert(p0 - base);
			p.insert(p1 - base);
			p.insert(p2 - base);
			
			sorted.clear();
			auto it0 = p.begin();
			auto it1 = it0;
			it1++;
			auto it2 = it1;
			it2++;
			add(*it0, *it1);
			add(*it1, *it2);
			add(*it2, *it0);
		}
		while (relax(pos)) {
			pos = p.lower_bound(a);
		}
	}

	ld get(line l) {
		if (p.size() <= 1) return 0;
		vec v1 = vec(-l.b, l.a);
		vec v2 = vec(l.b, -l.a);

		auto it1 = sorted.lower_bound({v1, {0, 0}});
		if (it1 == sorted.end()) it1 = sorted.begin();

		auto it2 = sorted.lower_bound({v2, {0, 0}});
		if (it2 == sorted.end()) it2 = sorted.begin();

		ld Min = dist(l, it1->second);
		ld Max = dist(l, it2->second);
		return abs(Max - Min);
	}
};
