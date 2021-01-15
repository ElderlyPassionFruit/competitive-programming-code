#include <bits/stdc++.h>

using namespace std;
#define int long long
#define vec point

struct point {
	int x, y;
	point() {
		x = y = 0;
	}
	point(int a, int b) {
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
	line(point x, point y) {
		a = y.y - x.y;
		b = x.x - y.x;
		c = x.y * y.x - x.x * y.y;
	}
};


point operator-(point a, point b) {
	return point(a.x - b.x, a.y - b.y);
}

double operator^(point a, point b) {
	return a.x * b.y - a.y * b.x;
}

double sq(double x) {
	return x * x;
}

double dist(vec a) {
	return sqrt(sq(a.x) + sq(a.y));
}

point p0;

bool cmp_angle(point a, point b) {
	a = a - p0;
	b = b - p0;
	if ((a ^ b) == 0) {
		return dist(a) < dist(b);
	}
	return (a ^ b) > 0;
}

vector <point> convex_hull(vector <point> g) {
	int n = g.size();
	for (int i = 0; i < n; i++) {
		if ((g[i].y < g[0].y) || ((g[i].y == g[0].y) && (g[i].x	< g[0].x)))
			swap(g[0], g[i]);
	}

	p0 = g[0];
	sort(g.begin() + 1, g.end(), cmp_angle);

	vector <point> hull;
	hull.push_back(p0);
	for (int i = 1; i < n; i++) {
		while (hull.size() >= 2) {
			int last = hull.size() - 1;
			vec v0 = hull[last] - hull[last - 1];
			vec v1 = g[i] - hull[last];
			if ((v0 ^ v1) > 0)
				break;
			hull.pop_back();
		}
		hull.push_back(g[i]);
	}
	return hull;
}



const int MAXN = 1e5 + 10;
line lines[MAXN];
vector <point> hull;
vector <point> fans;

int n, m;
void read() {
	cin >> n;
	cin >> m;

	for (int i = 0; i < n; i++) {
		cin >> lines[i].a >> lines[i].b >> lines[i].c;
	}
	hull.resize(m);
	for (int i = 0; i < m; i++) {
		cin >> hull[i].x >> hull[i].y;
	}
	hull = convex_hull(hull);
	m = hull.size();

	for (int i = 0; i < m; i++) {
		fans.push_back(hull[(i + 1) % m] - hull[i]);
	}
	cerr << "hull = " << endl;
	for (auto i : hull) {
		cerr << i.x << " " << i.y << endl;
	}
	cerr << "fans = " << endl;
	for (auto i : fans) {
		cerr << i.x << " " << i.y << endl;
	}
	cerr << endl;
}

int half(point a) {
	if ((a.y > 0) || (a.y == 0 && a.x > 0))
		return 0;
	return 1;
}

bool cmp_lower(const point & a, const point & b) {
	if (half(a) != half(b))
		return half(a) < half(b);
	return (a ^ b) > 0;
}

bool check(line l) {
	int ind1 = lower_bound(fans.begin(), fans.end(), vec(-l.b, l.a), cmp_lower) - fans.begin();
	int ind2 = lower_bound(fans.begin(), fans.end(), vec(l.b, -l.a), cmp_lower) - fans.begin();
	if (ind1 > ind2) swap(ind1, ind2);
 	ind1 %= m;
 	ind2 %= m;
	point p1 = hull[ind1];
	point p2 = hull[ind2];
	int c1 = -l.a*p1.x - l.b*p1.y;
	int c2 = -l.a*p2.x - l.b*p2.y;
	if (c1 > c2) swap(c1, c2);
	return c1 <= l.c && c2 >= l.c;

	/*cerr << "l = " << l.a << " " << l.b << " " << l.c << endl;
	cerr << "v1 = " << -l.b << " " << l.a << endl;
	cerr << "v2 = " << l.b << " " << -l.a << endl; 
	cerr << "ind1 = " << ind1 << " ind2 = " << ind2 << endl;
	cerr << "p1 = " << p1.x << " " << p1.y << endl;
	cerr << "p2 = " << p2.x << " " << p2.y << endl;
	cerr << "c1 = " << c1 << " c2 = " << c2 << " l.c = " << l.c << endl;
	cerr << endl;*/

}

vector <int> ans;
void run() {

	for (int i = 0; i < n; i++) {
		if (check(lines[i])) {
			ans.push_back(i);
		}
	}
}

void write() {
	cout << ans.size() << endl;
	for (auto i : ans) {
		cout << i + 1 << " ";
	}
	cout << endl;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cout.precision(20);
	read();
	run();
	write();
	return 0;
}