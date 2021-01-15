#include <bits/stdc++.h>

using namespace std;
#define pb push_back
#define double long double
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

long long operator^(point a, point b) {
	return a.x * b.y - a.y * b.x;
}

long long operator*(point a, point b) {
	return a.x * b.x + a.y * b.y;
}

long long area(vector<point> g) {
	long long ans = 0;
	long long n = g.size();
	for (long long i = 0; i < n; i++) {
		ans += g[i] ^ g[(i + 1) % n];
	}
	return ans;
}

long long sq(long long a) {
	return a * a;
}

long long dist(point a) {
	return sq(a.x) + sq(a.y);
}

double dist(point a, point b) {
	return sqrt(dist(point(a - b)));
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
	long long n = g.size();
	for (long long i = 0; i < n; i++) {
		if (g[i].y < g[0].y || (g[i].y == g[0].y && g[i].x < g[0].x))
			swap(g[0], g[i]);
	}
	p0 = g[0];
	sort(g.begin() + 1, g.end(), cmp);
	vector<point> hull;
	for (long long i = 0; i < n; i++) {
		while (hull.size() >= 2) {
			long long last = hull.size() - 1;
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

vector<pair <long long, vector<point> > > g;
long long n;

void read() {
	cin >> n;
	for (long long i = 0; i < n; i++) {
		long long sz;
		cin >> sz;
		vector<point> help(sz);
		for (auto &j : help) 
			cin >> j.x >> j.y;
		help = convex_hull(help);
		g.push_back({area(help), help});
	}

	sort(g.begin(), g.end(), [&] (pair <long long, vector<point> > &i, pair <long long, vector<point> > &j) {return i.first < j.first;});
}

const double EPS = 1e-9;

bool check(point a, point b, point x) {
	return abs(dist(a, b) - dist(a, x) - dist(b, x)) < EPS;
}

bool slow_check(point x, vector<point> g) {
	double ans = 0;
	long long n = g.size();
	for (long long i = 0; i < n; i++) {
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

bool check(point a, vector<point> & g) {
	long long n = g.size();

	point v1 = g[1] - g[0];
	point v2 = g[n - 1] - g[0];
	point x = a - g[0];
	if ((x ^ v2) < 0 || (x ^ v1) > 0) return false;

	p0 = g[0];
	long long pos = (--upper_bound(g.begin() + 1, g.end(), a, cmp)) - g.begin();

	return slow_check(a, {g[0], g[pos], g[(pos + 1) % n]});
}

long long get_ind(point x) {
	if (!check(x, g[n - 1].second))
		return n;
	long long l = -1, r = n - 1;
	while (l < r - 1) {
		long long mid = (l + r) / 2;
		if (check(x, g[mid].second))
			r = mid;
		else
			l = mid;
	}
	return r;
}

long long ans;

void run() {
	vector<bool> used(n, false);
	long long m;
	cin >> m;
	for (long long i = 0; i < m; i++) {
		point x;
		cin >> x.x >> x.y;
		long long ind = get_ind(x);
		if (ind > n - 1)
			continue;
		used[ind] = true;
	}
	ans = 0;
	if (used[0])
		ans += g[0].first;
	for (long long i = 1; i < n; i++) {
		if (used[i])
			ans += g[i].first - g[i - 1].first;
	}
}

void write() {
	cout << ans / 2;
	if (ans % 2 == 1)
		cout << ".5";
	cout << endl;
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