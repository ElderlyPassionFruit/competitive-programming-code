#include <bits/stdc++.h>
using namespace std;

#define int long long
#define vec point

const double EPS = 1e-6;
struct point {
	int x, y;
	point () {
		x = y = 0;
	}
	point (int a, int b) {
		x = a, y = b;
	}
};

struct line {
	int a, b, c;
	line() {
		a = b = c = 0;
	}
	line(int x, int y, int z) {
		a = x, b = y, c = z;
	}
};

point operator-(point a, point b) {
	return point(a.x - b.x, a.y - b.y);
}
double operator^(point a, point b) {
	return a.x * b.y - a.y * b.x;
}

double operator*(point a, point b) {
	return a.x * b.x + a.y * b.y;
}

double sq(double x) {
	return x * x;
}

double dist(vec a) {
	return sqrt(sq(a.x) + sq(a.y));
}

double dist(point a, point b) {
	return dist(a - b);
}

bool check(point a, point b, point x) {
	return abs(dist(a, b) - dist(a, x) - dist(b, x)) < EPS;
}

bool check(vector <point> p, point a) {
	int n = p.size();
	for (int i = 0; i < n; i++) {
		point x = p[i];
		point y = p[(i + 1) % n];
		if (check(x, y, a)) 
			return true;
	}

	double ans = 0;
	for (int i = 0; i < n; i++) {
		vec x = p[i] - a;
		vec y = p[(i + 1) % n] - a;
		ans += atan2(x ^ y, x * y);
	}
	return abs(ans) > EPS;
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

vector <point> convex_hull(vector <point> g) {
	int n = g.size();
	for (int i = 0; i < n; i++) {
		if (g[i].y < g[0].y || (g[i].y == g[0].y && g[i].x < g[0].x))
			swap(g[i], g[0]);
	}
	p0 = g[0];
	sort(g.begin() + 1, g.end(), cmp);
	vector <point> hull;
	hull.push_back(p0);
	for (int i = 1; i < n; i++) {
		while (hull.size() >= 2) {
			int last = hull.size() - 1;
			vec v1 = hull[last] - hull[last - 1];
			vec v2 = g[i] - hull[last];
			if ((v1 ^ v2) > 0) break;
			hull.pop_back();
		}
		hull.push_back(g[i]);
	}
	return hull;
}

double area(vector <point> g) {
	int n = g.size();
	double ans = 0;
	for (int i = 0; i < n; i++) {
		ans += (g[i] ^ g[(i + 1) % n]);
	}
	ans = abs(ans) / 2;
	return ans;
}

bool check_fast(const vector <point> & p, point x) {
	int n = p.size();
	vec x1 = p[1] - p[0];
	vec x2 = p[n - 1] - p[0];
	vec x3 = x - p[0];
	if ((x1 ^ x2) * (x1 ^ x3) < 0) {
		return false;
	}
	if ((x2 ^ x1) * (x2 ^ x3) < 0){
		return false;
	}

	p0 = p[0];
	int pos = --upper_bound(p.begin() + 1, p.end(), x, cmp) - p.begin();
	
	x1 = p[pos] - p[0];
	if ((x1 ^ x3) == 0) {
		return dist(x1) >= dist(x3);
	}

	return check({p[0], p[pos], p[(pos + 1) % n]}, x);
}


bool help_cmp(const pair <double, vector <point> > & a, const pair <double, vector <point> > & b) {
	return a.first < b.first;
}

bool half(point a) {
	return a.y > 0 || (a.y == 0 && a.x > 0);
}

bool cmp_for_lines(point a, point b) {
	if (half(a) != half(b))
		return half(a) > half(b);
	return (a ^ b) > 0;
}

bool check(int a, int b, int x){
	return a <= x && b >= x;
}

bool check(const vector <point> & g, const vector <point> & p, line l) {
	vec v1 = vec(-l.b, l.a);
	vec v2 = vec(l.b, -l.a);


	int pos1 = lower_bound(g.begin(), g.end(), v1, cmp_for_lines) - g.begin();
	int pos2 = lower_bound(g.begin(), g.end(), v2, cmp_for_lines) - g.begin();

	pos1 %= p.size();
	pos2 %= p.size();

	point p1 = p[pos1];
	point p2 = p[pos2];

	int c1 = -l.a * p1.x - l.b * p1.y;
	int c2 = -l.a * p2.x - l.b * p2.y;

	/*cout << "new test" << endl;
	cout << "g = " << endl;
	for (auto i : g)
		cout << i.x << " " << i.y << endl;
	cout << endl;
	cout << "p = " << endl;
	for (auto i : p)
		cout << i.x << " " << i.y << endl;
	cout << endl;
	cout << "l = " << l.a << " " << l.b << " " << l.c << endl;
	cout << "pos1 = " << pos1 << endl;
	cout << "pos2 = " << pos2 << endl;
	cout << c1 << " " << l.c << " " << c2 << endl;
	cout << endl;*/
	return check(c1, c2, l.c) || check(c2, c1, l.c);
}



signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cout.precision(20);
	int n, m;
	cin >> n >> m;
	vector <line> l(n);
	for (int i = 0; i < n; i++) {
		cin >> l[i].a >> l[i].b >> l[i].c;
	}
	vector <point> p(m);
	for (int i = 0; i < m; i++) {
		cin >> p[i].x >> p[i].y;
	}
	p = convex_hull(p);


/*	cout << endl;

	cout << "p = " << endl;
	cout << p.size() << endl;
	for (auto i : p) {
		cout << i.x << " " << i.y << endl;
	}

	cout << endl;*/

	m = p.size();
	vector <point> g(m);
	for (int i = 0; i < m; i++) {
		g[i] = p[(i + 1) % m] - p[i];
	}

	vector <int> ans;
	for (int i = 0; i < n; i++) {
		if (check(g, p, l[i]))
			ans.push_back(i + 1);
	}
	cout << ans.size() << endl;
	for (auto i : ans)
		cout << i << " ";
	cout << endl;

	return 0;
}