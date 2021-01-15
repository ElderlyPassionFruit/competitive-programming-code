#include <bits/stdc++.h>

using namespace std;

#define int long long
const long double INF = 1e18;
const long double EPS = 1e-6;


long double sq(long double x) {
	return x * x;
}

struct point{
	long double x, y;
	point() {
		x = 0, y = 0;
	}
	point(long double a, long double b) {
		x = a, y = b;
	}
};

point operator+(point a, point b) {
	return point(a.x + b.x, a.y + b.y);
}

point operator-(point a, point b)
{
    return point(a.x - b.x, a.y - b.y);
}

double operator*(point a, point b)
{
    return a.x*a.y + b.x*b.y;
}

struct line{
	long double a, b, c;
	line() {
		a = b = c = 0;
	}
	line(long double a1, long double b1, long double c1) {
		a = a1, b = b1, c = c1;
	}
	line(point x, point y) {
		a = y.y - x.y;
		b = x.x - y.x;
		c = x.y * y.x - y.y * x.x;
	}
};

bool check(point a, point b, point x) {
	if (a.x > b.x)
		swap(a, b);
	if ((x.x > a.x || abs(a.x - x.x) < EPS) && (x.x < b.x || abs(b.x - x.x) < EPS))
		return true;
	return false; 
}

point cross(line a1, line a2) {
	point ans;
	ans.x = a2.b * a1.c - a1.b * a2.c;
	ans.y = a2.c * a1.a - a1.c * a2.a;
	ans.x /= a1.b * a2.a - a2.b * a1.a;
	ans.y /= a1.b * a2.a - a2.b * a1.a;
	return ans;
}

long double dist(point a, point b) {
	return sqrt(sq(a.x - b.x) + sq(a.y - b.y));
}

long double linedist(point a, point b, point x) {
	line help = line(a, b);
	long double fans = help.a * x.x + help.b * x.y + help.c;
	fans /= sqrt(sq(help.a) + sq(help.b));
	fans = abs(fans);
	return fans;
}

long double dist(point a, point b, point c)
{
	if (((c - b)*(a - b)) < 0)
	{
		return dist(a, b);
	}
	if (((b - c)*(a - c)) < 0)
	{
		return dist(a, c);
	}
	return linedist(a, b, c);
}

long double dist(point a, point b, point c, point d) {
	long double ans = INF;
	ans = min(ans, dist(a, b, c));
	ans = min(ans, dist(a, b, d));
	ans = min(ans, dist(c, d, a));
	ans = min(ans, dist(c, d, b));
	return ans;
}

long double dist(vector <point> &p1, vector <point> &p2) {
	long double ans = INF;
	for (int i = 0; i < p1.size(); i++) {
		for (int j = 0; j < p2.size(); j++) {
			point a = p1[i];
			point b = p1[(i + 1) % (int) p1.size()];
			point c = p2[j];
			point d = p2[(j + 1) % (int) p2.size()];
			ans = min(ans, dist(a, b, c, d));
		}
	}
	return ans;
}

signed main() {
	cout.precision(20);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	point a, b, c;
	cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y;
	cout << dist(b, c, a) << endl;
	return 0;
}