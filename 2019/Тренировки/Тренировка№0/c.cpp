#include <bits/stdc++.h>

using namespace std;
#define int long long
#define double long double
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct point{
	double x, y;
	point() {
		x = 0, y = 0;
	}
	point(double a, double b) {
		x = a, y = b;
	} 
};

point operator-(point a, point b) {
	return point(a.x - b.x, a.y - b.y);
}

int operator^(point a, point b) {
	return a.x * b.y - a.y * b.x;
}

int operator*(point a, point b) {
	return a.x * b.x + a.y * b.y;
}

int sq(int x) {
	return x * x;
}

double dist(point a) {
	return sq(a.x) + sq(a.y);
}

double dist(point a, point b) {
	return sqrt(dist(a - b));
}

point p0;

bool cmp(point a, point b) {
	a = a - p0;
	b = b - p0;
	if ((a ^ b) == 0)
		return dist(a) < dist(b);
	return (a ^ b) > 0;
}

vector<point> convex_hull(vector<point> g) {
	int n = g.size();
	for (int i = 0; i < n; i++) {
		if (tie(g[i].y, g[i].x) < tie(g[0].y, g[0].x))
			swap(g[0], g[i]);
	}
	p0 = g[0];
	sort(g.begin() + 1, g.end(), cmp);
	vector<point> hull;
	for (int i = 0; i < n; i++) {
		while (hull.size() >= 2) {
			int last = hull.size() - 1;
			point v1 = hull[last] - hull[last - 1];
			point v2 = g[i] - hull[last];
			if ((v1 ^ v2) > 0)
				break;
			hull.pop_back();
		}
		hull.push_back(g[i]);
	}
	return hull;
}

int n, m;
vector<point> g, gr;

void read() {
	cin >> n;
	g.resize(n);
	for (auto &i : g)
		cin >> i.x >> i.y;
	g = convex_hull(g);
	n = g.size();

	cin >> m;
	gr.resize(m);
	for (auto &i : gr)
		cin >> i.x >> i.y;
	gr = convex_hull(gr);
	m = gr.size();
}

const double EPS = 1e-12;

bool check(point a, point b, point x) {
	return abs(dist(a, b) - dist(a, x) - dist(b, x)) < EPS;
}

bool slow_check(point x, vector<point> g) {
	double ans = 0;
	int n = g.size();
	for (int i = 0; i < n; i++) {
		point a = g[i];
		point b = g[(i + 1) % n];
		if (check(a, b, x))
			return true;
		a = a - x;
		b = b - x;
		ans += atan2(a ^ b, a * b);
	}
	return abs(ans) > 3;
}

bool fast_check(point x, vector<point> & g) {
	int n = g.size();
	point v1 = g[1] - g[0];
	point v2 = g[n - 1] - g[0];
	point v3 = x - g[0];
	if ((v3 ^ v2) <= 0 || (v3 ^ v1) >= 0)
		return false;

	p0 = g[0];
	int pos = (--upper_bound(g.begin() + 1, g.end(), x, cmp)) - g.begin();
	if (check(g[pos], g[(pos + 1) % n], x))
		return false;
	if (tie(x.x, x.y) == tie(g[0].x, g[0].y))
		return false;
	return slow_check(x, {g[0], g[pos], g[(pos + 1) % n]});
}

bool ans;

void run() {
	ans = true;
	for (auto i : gr) {
		ans &= fast_check(i, g);
	}
}

void write() {
	if (ans) {
		cout << "YES\n";
	}
	else {
		cout << "NO\n";
	}
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



