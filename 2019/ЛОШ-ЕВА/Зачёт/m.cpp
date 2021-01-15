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

double operator^(point a, point b) {
	return a.x * b.y - a.y * b.x;
}

double operator*(point a, point b) {
	return a.x * b.x + a.y * b.y;
}

point operator+(point a, point b) {
	return point(a.x + b.x, a.y + b.y);
}

point operator-(point a, point b) {
	return point(a.x - b.x, a.y - b.y);
}

const double EPS = 1e-6;

double sq(double x) {
	return x * x;
}

double dist(point a) {
	return sqrt(sq(a.x) + sq(a.y));
}

double dist(point a, point b) {
	return dist(a - b);
}

bool check(point a, point b, point x) {
	return abs(dist(a, b) - dist(a, x) - dist(b, x)) < EPS;
}

#define vec point

bool check(vector<point> & g, point x) {
	double ans = 0;
	int n = g.size();
	for (int i = 0; i < n; i++) {
		if (check(g[i], g[(i + 1) % n], x)) return true;
		vec a = g[i] - x;
		vec b = g[(i + 1) % n] - x;
		ans += atan2(a ^ b, a * b);
	}
	return abs(ans) > EPS;
}

const int INF = 1e8;

struct line{
	double a, b, c;
	line() {
		a = b = c = 0;
	}
	line(double x, double y, double z) {
		a = x, b = y, c = z;
	}
	line(point x, point y) {
		a = y.y - x.y;
		b = x.x - y.x;
		c = x.y * y.x - y.y * x.x;
	}
};

point cross(line a, line b) {
	double help = a.b * b.a - a.a * b.b;
	if (abs(help) < EPS) return point(INF, INF);
	point ans;
	ans.x = b.b * a.c - a.b * b.c;
	ans.y = b.c * a.a - a.c * b.a;
	ans.x /= help;
	ans.y /= help;
	return ans;
}

line perp(point a, point b) {
	line ans;
	point x = a + b;
	x.x /= 2;
	x.y /= 2;
	vec h = a - b;
	vec w = vec(-h.y, h.x);
	ans = line(x, x + w);
	return ans;
}

int n;
vector<point> g;
int m;
vector<point> p;

void read() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		point a;
		cin >> a.x >> a.y;
		g.push_back(a);
	}
	cin >> m;
	for (int i = 0; i < m; i++) {
		point a;
		cin >> a.x >> a.y;
		p.push_back(a);
	}
}

pair <double, point> ans;

void relax(point x) {
	if (!check(g, x)) return;
	double len = INF;
	for (auto i : p)
		chkmin(len, dist(i, x));
	if (len > ans.first) {
		ans.first = len;
		ans.second = x;
	}
}

void run() {
	ans.first = 0;
	vector<point> check;
	for (auto i : g)
		check.push_back(i);

	for (int i = 0; i < m; i++) {
		for (int j = i + 1; j < m; j++) {
			for (int k = j + 1; k < m; k++) {
				auto x = perp(p[i], p[j]);
				auto y = perp(p[j], p[k]);
				check.push_back(cross(x, y));
			}
		
			for (int k = 0; k < n; k++) {
				auto x = perp(p[i], p[j]);
				auto y = line(g[k], g[(k + 1) % n]);
				check.push_back(cross(x, y));
			}
		}
	}

	for (auto i : check)
		relax(i);
}

void write() {
	cout << fixed << setprecision(2) << ans.first << endl;
	cout << fixed << setprecision(2) << ans.second.x << " " << ans.second.y << endl;
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