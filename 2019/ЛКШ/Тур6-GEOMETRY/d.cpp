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

long long operator^(point a, point b) {
	return a.x * b.y - a.y * b.x;
}

long long operator*(point a, point b) {
	return a.x * b.x + a.y * b.y;
}

long long sq(long long x) {
	return x * x;
}

long long dist(point a) {
	return sq(a.x) + sq(a.y);
}

long long dist(point a, point b) {
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
		if (g[i].y < g[0].y || (g[i].y == g[0].y && g[i].x < g[0].x))
			swap(g[i], g[0]);
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

int n;
vector<point> g;
void read() {
	cin >> n;
	g.resize(n);
	for (auto &i : g)
		cin >> i.x >> i.y;
	g = convex_hull(g);
	n = g.size();
}

long double ans;

void relax(point a, point b) {
	chkmax(ans, dist(a, b));
}

void run() {
	ans = 0;
	if (n == 1) return;
	if (n == 2) {
		ans = dist(g[0], g[1]);
		return;
	}
	int pos = 0;
	for (int i = 0; i < n; i++) {
		relax(g[i], g[pos]);
		vec v1 = g[(i + 1) % n] - g[i];
		v1 = vec(-v1.y, v1.x);
		vec v2 = g[(pos + 1) % n] - g[pos];
		while ((v1 * v2) >= 0) {
			pos++;
			pos %= n;
			relax(g[i], g[pos]);
			v2 = g[(pos + 1) % n] - g[pos];
		}
	}
}

void write() {
	ans = sqrt(ans);
	cout.precision(20);
	cout << ans << "\n";
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