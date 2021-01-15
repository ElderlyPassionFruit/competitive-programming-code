#include <bits/stdc++.h>

using namespace std;
#define int long long

struct point{
	int x, y;
	point() {
		x = 0, y = 0;
	}
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

point p0;

double dist(point a) {
	return sqrt(a.x * a.x + a.y * a.y);
}

bool cmp_for_hull(point a, point b) {
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
		if (g[i].y < g[0].y || (g[i].y == g[0].y && g[i].x < g[0].x))
			swap(g[0], g[i]);
	}
	p0 = g[0];
	sort(g.begin() + 1, g.end(), cmp_for_hull);

	vector <point> hull;
	hull.push_back(p0);

	for (int i = 1; i < n; i++) {
		while (hull.size() >= 2) {
			int last = hull.size() - 1;
			point x = hull[last] - hull[last - 1];
			point y = g[i] - hull[last];

			if ((x ^ y) > 0)
				break;
			hull.pop_back();
		}
		hull.push_back(g[i]);
	}

	return hull;
}

struct line {
	int a, b, c;
	line() {
		a = 0, b = 0, c = 0;
	}
	line(int x, int y, int z) {
		a = x, b = y, c = z;
	}
};

int hull(const point & a) {
	if (a.y > 0 || (a.y == 0 && a.x >= 0))
		return 1;
	return 0;
}

bool cmp_for_lines(point a, point b) {
	if (hull(a) != hull(b))
		return hull(a) > hull(b);
	return (a ^ b) > 0;
}

bool check(line l, const vector <point> & g, const vector <point> & h) {
	point x1 = point(-l.b, l.a);
	point x2 = point(l.b, -l.a);

	int pos1 = lower_bound(g.begin(), g.end(), x1, cmp_for_lines) - g.begin();
	int pos2 = lower_bound(g.begin(), g.end(), x2, cmp_for_lines) - g.begin();

	pos1 %= g.size();
	pos2 %= g.size();

	point p1 = h[pos1];
	point p2 = h[pos2];

	int c1 = - l.a * p1.x - l.b * p1.y;
	int c2 = - l.a * p2.x - l.b * p2.y;

	if (c1 > c2)
		swap(c1, c2);
	return c1 <= l.c && c2 >= l.c;
}

bool check(line l, const vector <point> & g, const vector <point> & help, const vector <point> & h) {
	if (check(l, g, h))
		return true;
	
	int correct = l.a * h[0].x + l.b * h[0].y + l.c;
	for (auto i : help) {
		int incorrect = l.a * i.x + l.b * i.y + l.c;
		if (incorrect == 0)
			return true;
		if (correct > 0 && incorrect < 0)
			return true;
		if (correct < 0 && incorrect > 0)
			return true;
	}
	return false;
}

vector <point> g, help, vec;

void rebuild() {
	for (auto i : help)
		g.push_back(i);

	help.clear();
	g = convex_hull(g);

	vec.resize(g.size());
	int sz = g.size();
	for (int i = 0; i < sz; i++) {
		vec[i] = g[(i + 1) % sz] - g[i];
	}
}

int n, q;

void read() {
	cin >> n >> q;
	g.resize(n);
	help = {};
	vec = {};
	for (int i = 0; i < n; i++)
		cin >> g[i].x >> g[i].y;
	rebuild();
}

vector <string> ans;

void run() {
	int help_sz = sqrt(n * log2(n));
	for (int test = 0; test < q; test++) {
		int type;
		cin >> type;
		if (type == 1) {
			point a;
			cin >> a.x >> a.y;
			help.push_back(a);
			if (help.size() > help_sz)
				rebuild();
		}
		else {
			line l;
			cin >> l.a >> l.b >> l.c;
			l.c *= -1;
			if (check(l, vec, help, g))
				ans.push_back("NO");
			else
				ans.push_back("YES");
		}
	}
}

void write() {
	for (auto i : ans)
		cout << i << '\n';
}

signed main() {
    freopen("fencing.in", "r", stdin);
    freopen("fencing.out", "w", stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}