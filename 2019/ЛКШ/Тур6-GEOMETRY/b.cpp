#include <bits/stdc++.h>

using namespace std;
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct point{
	long long x, y;
	point() {
		x = 0, y = 0;
	}
	point(long long a, long long b) {
		x = a, y = b;
	}
};
 
point operator-(point a, point b) {
	return point(a.x - b.x, a.y - b.y);
}

point operator+(point a, point b) {
	return point(a.x + b.x, a.y + b.y);
}

long long operator^(point a, point b) {
	return a.x * b.y - a.y * b.x;
}

long long operator*(point a, point b) {
	return a.x * b.x + a.y * b.y;
}

long double sq(long double x) {
	return x * x;
}
 
long double dist(point a) {
	return sqrt(sq(a.x) + sq(a.y));
}

long double dist(point a, point b) {
	return dist(a - b);
}

point p0;
bool cmp(point a, point b) {
	a = a - p0;
	b = b - p0;
	if ((a ^ b) == 0) {
		return dist(a) < dist(b);
	}
	return (a ^ b) > 0;
}

#define vec point

vector<point> convex_hull(vector<point> g) {
	int n = g.size();
	for (int i = 0; i < n; i++) {
		if (g[0].y > g[i].y || (g[0].y == g[i].y && g[0].x > g[i].y))
			swap(g[0], g[i]);
	}
	p0 = g[0];
	sort(g.begin() + 1, g.end(), cmp);
	vector<point> hull;
	for (int i = 0; i < n; i++) {
		while (hull.size() >= 2) {
			int last = hull.size() - 1;
			vec v1 = hull[last] - hull[last - 1];
			vec v2 = g[i] - hull[last];
			if ((v1 ^ v2) > 0)
				break;
			hull.pop_back();	
		}
		hull.push_back(g[i]);
	}
	return hull;
}

const long double EPS = 1e-9;

bool check(point a, point b, point x) {
	return abs(dist(a, b) - dist(a, x) - dist(b, x)) < EPS;
}

bool slow_check(point a, vector<point> g) {
	long double ans = 0;
	int n = g.size();
	for (int i = 0; i < n; i++) {
		point x = g[i];
		point y = g[(i + 1) % n];
		if (check(x, y, a)) return true;
		x = x - a;
		y = y - a;
		ans += atan2(x ^ y, x * y);
	}
	return abs(ans) > EPS;
}

bool fast_check(point a, const vector<point> & g) {
	int n = g.size();

	vec v1 = g[1] - g[0];
	vec v2 = g[n - 1] - g[0];
	vec x = a - g[0];
	if ((x ^ v2) < 0 || (x ^ v1) > 0) return false;

	p0 = g[0];
	int pos = (--upper_bound(g.begin() + 1, g.end(), a, cmp)) - g.begin();

	return slow_check(a, {g[0], g[pos], g[(pos + 1) % n]});
}

int n, m, k;
vector<point> g;

void read() {
	cin >> n >> m >> k;
	for (int i = 0; i < n; i++) {
		point x;
		cin >> x.x >> x.y;
		g.push_back(x);
	}
	g = convex_hull(g);
	assert(n == g.size());
}

int ans;

void run() {
	ans = 0;
	for (int i = 0; i < m; i++) {
		point x;
		cin >> x.x >> x.y;
		ans += fast_check(x, g);
	}
}

void write() {
	if (ans >= k) {
		cout << "YES" << endl;
	}
	else {
		cout << "NO" << endl;
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