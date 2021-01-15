#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

#define int ll

struct point{
	int x, y;
	point() {}
	point(int _x, int _y) {
		x = _x, y = _y;
	}
};

point operator-(const point & a, const point & b) {
	return point(a.x - b.x, a.y - b.y);
}

int operator^(const point & a, const point & b) {
	return a.x * b.y - a.y * b.x;
}

int sq(int x) {
	return x * x;
}

int dist(point a) {
	return sq(a.x) + sq(a.y);
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

vector<point> convex_hull(vector<point> p) {
	if (p.empty()) return p;
	int n = p.size();
	for (int i = 0; i < n; i++) {
		if (tie(p[i].x, p[i].y) < tie(p[0].x, p[0].y)) {
			swap(p[i], p[0]);
		}
	}
	p0 = p[0];
	sort(p.begin() + 1, p.end(), cmp);
	p.push_back(p[0]);
	vector<point> hull;
	for (int i = 0; i <= n; i++) {
		while (hull.size() >= 2) {
			int last = hull.size() - 1;
			vec v1 = hull[last] - hull[last - 1];
			vec v2 = p[i] - hull[last];
			if ((v1 ^ v2) > 0) break;
			hull.pop_back();
		}
		hull.push_back(p[i]);
	}
	hull.pop_back();
	return hull;
}

void no() {
	cout << -1 << endl;
	exit(0);
}

int n, m, s;

int read() {
	ld s;
	cin >> s;
	int ans = s * 2;
	if (abs(ans - 2 * s) > 1e-9) no();
	return ans;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n >> m;
	s = read();
	if (n * m * 2 < s) no();
	while (true) {
		if ((n - 1) * m * 2 >= s) {
			n--;
			continue;
		}
		if (n * (m - 1) * 2 >= s) {
			m--;
			continue;
		}
		break;
	}
	int y1 = -1, y2 = -1;
	for (int y = 0; y <= m; y++) {
		if ((n * m * 2 - y) >= s) {
			y1 = y;
		}
	}
	for (int y = m; y >= 0; y--) {
		if ((n * m * 2 - y1 - (m - y)) >= s) {
			y2 = y;
		}
	}
	vector<point> p;
	p.push_back({1, 0});
	p.push_back({0, y1});
	p.push_back({0, m});
	p.push_back({n - 1, m});
	p.push_back({n, y2});
	p.push_back({n, 0});
	p = convex_hull(p);
	reverse(all(p));
	cout << p.size() << endl;
	for (auto i : p) {
		cout << i.x << " " << i.y << endl;
	}
	return 0;
}