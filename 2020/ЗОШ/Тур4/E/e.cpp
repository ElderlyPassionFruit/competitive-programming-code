#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
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
	line(ld x, ld y, ld z) {
		a = x, b = y, c = z;
	}
	line(point x, point y) {
		a = y.y - x.y;
		b = x.x - y.x;
		c = x.y * y.x - x.x * y.y;
	}
};

ld dist(point a, line l) {
	return (ld)abs(l.a * a.x + l.b * a.y + l.c) / sqrt(sq(l.a) + sq(l.b));
} 

struct circle{
	point o;
	ld r;
	circle() {}
	circle(point a, ld x) {
		o = a, r = x;
	}
};

const ld EPS = 1e-9;
#define vec point

vec norm(vec a, ld need) {
	ld d = dist(a);
	a.x /= d;
	a.y /= d;
	a.x *= need;
	a.y *= need;
	return a;
}

bool check(point a, line l) {
	return abs(l.a * a.x + l.b * a.y + l.c) < EPS;
}

vector<point> cross(circle o, line l) {
	ld d = dist(o.o, l);
	if (d > o.r || abs(d - o.r) < EPS)
		return {};
	vec x = vec(l.a, l.b);
	x = norm(x, d);
	if (!check(o.o + x, l))
		x = norm(vec(-l.a, -l.b), d);
	point a = o.o + x;
	ld need = sqrt(sq(o.r) - sq(d));
	x = norm(vec(-l.b, l.a), need);
	return {a + x, a - x};
}

vector<point> cross(circle a, circle b) {
	line l = line(2 * (b.o.x - a.o.x), 2 * (b.o.y - a.o.y), sq(a.o.x) + sq(a.o.y) - sq(a.r) - sq(b.o.x) - sq(b.o.y) + sq(b.r));
	return cross(a, l);
}

point p0;

bool cmp(point a, point b) {
	a = a - p0;
	b = b - p0;
	if (abs(a ^ b) < EPS)
		return dist(a) < dist(b);
	return (a ^ b) > 0;
}

ld area(vector<point> p) {
	p0 = p[0];
	for (auto i : p) {
		if (tie(i.x, i.y) < tie(p0.x, p0.y))
			p0 = i;
	}
	sort(all(p), cmp);
	
	/*cout << "p = " << endl;
	for (auto i : p) {
		cout << i.x << " " << i.y << endl;
	}*/

	int n = p.size();
	//assert(n == 4);
	ld ans = 0;
	for (int i = 0; i < n; i++) {
		vec v1 = p[i];
		vec v2 = p[(i + 1) % n];
		ans += v1 ^ v2;
	}
	//cout << "dist = " << dist(p[0], p[1]) * dist(p[0], p[1]) << endl;
	//cout << "area = " << abs(ans) / 2 << endl;
	return abs(ans) / 2;
} 

ld area(circle a, vector<point> have) {
	if (have.size() <= 1) return 0;
	//cout << "have.size() = " << have.size() << endl;
	assert(have.size() == 2);
	vec v1 = have[0] - a.o;
	vec v2 = have[1] - a.o;
	ld ans = abs(atan2(v1 ^ v2, v1 * v2)) * a.r * a.r / 2 - abs(v1 ^ v2) / 2;
	//cout << "fans = " << ans << endl;
	return ans;
}

const ld PI = acos(-1);

bool check(circle o, point a) {
	return abs(o.r - dist(a, o.o)) < EPS;
}

vector<point> get(vector<point> x, ll w, ll h) {
	vector<point> ans;
	for (auto i : x) {
		if (i.x >= 0 && i.x <= w && i.y >= 0 && i.y <= h)
			ans.push_back(i);
	}
	return ans;
}

void merge(vector<point> & a, vector<point> b) {
	for (auto i : b)
		a.push_back(i);
}

ld zero(ld x) {
	if (abs(x) < EPS)
		return 0;
	return x;
}

bool operator==(const point & a, const point & b) {
	return abs(a.x - b.x) < EPS && abs(a.y - b.y) < EPS;
}

void Unieque(vector<point> & a) {
	//sort(all(a), [&] (point i, point j) {return tie(i.x, i.y) < tie(j.x, j.y);});
	vector<point> ans;
	for (int i = 0; i < a.size(); i++) {
		bool flag = false;
		for (int j = i + 1; j < a.size(); j++) {
			if (a[i] == a[j]) {
				flag = true; 
				break;
			}
		}
		if (!flag)
			ans.push_back(a[i]);
	}
	a = ans;
}

bool check_in(circle a, point x) {
	return a.r - dist(x, a.o) >= 0 || abs(a.r - dist(x, a.o)) < EPS;
}

bool check(ld r, ll w, ll h, ll need) {
	circle a = circle({0, 0}, r);
	circle b = circle({0, (ld)h}, r);
	circle d = circle({(ld)w, 0}, r);
	circle c = circle({(ld)w, (ld)h}, r);
	
	vector<circle> have = {a, b, c, d};

	//cout << "a, b = " << a.o.x << " " << a.o.y << " " << a.r << " " << b.o.x << " " << b.o.y << " " << b.r << endl;
	vector<point> good;
	int n = have.size();
	vector<line> l;
	for (int i = 0; i < n; i++) {
		l.push_back(line(have[i].o, have[(i + 1) % n].o));
	}

	for (int i = 0; i < n; i++) {
		merge(good, get(cross(have[i], have[(i + 1) % n]), w, h));
		for (int x = 1; x <= 2; x++) {
			merge(good, get(cross(have[(i) % n], l[(i + x) % n]), w, h));
		}
	}

	vector<point> kek;
	for (auto i : good) {
		bool flag = true;
		for (auto j : have)
			flag &= check_in(j, i);
		if (flag)
			kek.push_back(i);
	}
	good = kek;

	Unieque(good);
	/*cout << "r = " << r << endl;
	cout << "good = " << endl;
	for (auto i : good)
		cout << "(" << zero(i.x) << ", " << zero(i.y) << ")" << endl;
	cout << endl;*/

	ld ans = area(good);
	//cout << ans << endl;


	for (auto i : have) {
		vector<point> need;
		for (auto j : good)
			if (check(i, j))
				need.push_back(j);
		ans += area(i, need);
		/*cout << "i = " << i.o.x << " " << i.o.y << " " << i.r << endl;
		cout << "need = " << endl;
		for (auto i : need)
			cout << i.x << " " << i.y << endl;
		cout << endl;*/
	}
	//cout << "check_ans = " << ans << " need = " << need << endl;

	return ans >= need || abs(ans - need) < EPS;
}

void solve() {
	ld w, h, s;
	cin >> w >> h >> s;
	if (!w && !h && !s) exit(0);
	ld x = dist(point(0, 0), point(w, h));
	ld l = x / 2, r = x;
	//cout << check(13.52081728298995985, w, h, s) << endl;
	//return;
	//cout << "l = " << l << " r = " << r << endl;

	while (abs(r - l) > EPS) {
		ld mid = (l + r) / 2;
		bool flag = check(mid, w, h, s); 
		if (flag)
			r = mid;
		else
			l = mid;
		//cout << mid << " " << l << " " << r << " " << flag << endl;
	}
	cout.precision(20);
	//cout << r << endl;
	ld ans = r * r * 4;
	cout << /*r << " " << */ ans << "\n";
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cout.precision(20);
	while (true)
		solve();
	return 0;
}