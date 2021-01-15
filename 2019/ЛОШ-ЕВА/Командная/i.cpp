#include <bits/stdc++.h>

using namespace std;

#define int long long
#define double long double

const double EPS = 1e-6;

struct point {
	double x, y;
	point() {
		x = 0, y = 0;
	}
	point(int a, int b) {
		x = a, y = b;
	}
};

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
		c = x.y * y.x - x.x * y.y;
	}
};

point cross(line a, line b) {
	point ans;
	ans.x = a.c * b.b - a.b * b.c;
	ans.y = a.a * b.c - a.c * b.a;
	ans.x /= a.b * b.a - b.b * a.a;
	ans.y /= a.b * b.a - b.b * a.a;
	return ans;
}

bool check(line a, line b) {
	return  abs(a.b * b.a - b.b * a.a) > EPS;
}

point operator-(point a, point b) {
	return point(a.x - b.x, a.y - b.y);
}

point operator+(point a, point b) {
	return point(a.x + b.x, a.y + b.y);
}

double operator^(point a, point b) {
	return a.x * b.y - a.y * b.x;
}

double operator*(point a, point b) {
	return a.x * b.x + a.y * b.y;
}


bool check(point a, point b, point c) {
	auto x = a - b;
	auto y = c - b;
	return abs(x ^ y) > EPS; 
}

double sq(double x) {
	return x * x;
}

double dist(point a) {
	return sqrt(sq(a.x) + sq(a.y));
}

double dist(point a, point b) {
	return dist(a - b);
}

bool check_on(point a, point b, point x) {
	return abs(dist(a, x) + dist(b, x) - dist(a, b)) < EPS;
}

bool check(vector<point> g, point x) {
	double ans = 0;
	int n = g.size();
	for (int i = 0; i < n; i++) {
		point a = g[i];
		point b = g[(i + 1) % n];
		if (check_on(a, b, x)) return true;
		a = a - x;
		b = b - x;
		ans += atan2(a ^ b, a * b);
	}
	return abs(ans) > EPS;
}

vector<point> g;
vector<point> p;
int n, m;

void read() {
	cin >> n;
	g.resize(n);
	for (auto &i : g)
		cin >> i.x >> i.y;
	cin >> m;
	p.resize(m);
	for (auto &i : p) 
		cin >> i.x >> i.y;
}

line get_line(point a, point b) {
	point p = a + b;
	p.x /= 2;
	p.y /= 2;
	point v = a - b;
	point u(-v.y, v.x);
	return line(p, p + u);
}

double fans = 0;
point ans;

void run() {
	vector<line> help;
	for (int i = 0; i < m; i++) {
		for (int j = i + 1; j < m; j++) {
			help.push_back(get_line(p[i], p[j]));
		}
	}

	vector<point> fcheck;
	for (int i = 0; i < help.size(); i++) {
		for (int j = i + 1; j < help.size(); j++) {
			if (check(help[i], help[j])) {
				point x = cross(help[i], help[j]);
				if (check(g, x))
					fcheck.push_back(x);
			}
		}
	}

	for (int i = 0; i < help.size(); i++) {
		for (int j = 0; j < n; j++) {
			point a = g[j];
			point b = g[(j + 1) % n];
			line x = line(a, b);
			point y = cross(help[i], x);
			if (check(a, b, y))
				fcheck.push_back(y);
		}
	}

	for (auto i : g)
		fcheck.push_back(i);

	//cout << "fcheck = " << endl;
	//for (auto i : fcheck)
	//	cout << i.x << " " << i.y << endl;

	for (auto i : fcheck) {
		double d = 1e18;
		for (auto j : p) {
			d = min(d, dist(i, j));
		}
		if (d > fans) {
			fans = d;
			ans = i;
		}
	}
}

void write() {
	cout.precision(20);
	cout << fans << endl;
	cout << ans.x << " " << ans.y << endl;
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