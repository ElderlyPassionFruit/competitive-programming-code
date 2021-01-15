#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()
 
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

#define int ll
#define vec point

int sign(ll x) {
	if (x > 0) return 1;
	if (x < 0) return -1;
	return 0;
}

struct point{
	int x, y;
	point() {}
	point(int _x, int _y) {
		x = _x, y = _y;
	}
};

bool operator<(const point & a, const point & b) {
	return tie(a.x, a.y) < tie(b.x, b.y);
}

bool operator==(const point & a, const point & b) {
	return tie(a.x, a.y) == tie(b.x, b.y);
}

point operator-(const point & a, const point & b) {
	return point(a.x - b.x, a.y - b.y);
}

point operator+(const point & a, const point & b) {
	return point(a.x + b.x, a.y + b.y);
}

ll operator^(const point & a, const point & b) {
	return (ll) a.x * b.y - (ll) a.y * b.x;
}

ll operator*(const point & a, const point & b) {
	return (ll) a.x * b.x + (ll) a.y * b.y;
}

ll sq(ll x) {
	return x * x;
}

ll dist(point a) {
	return sq(a.x) + sq(a.y);
}

ld dist(point a, point b) {
	return sqrt(dist(a - b));
}

point p0;

bool cmp(point a, point b) {
	a = a - p0;
	b = b - p0;
	if (sign(a ^ b) == 0) {
		return dist(a) < dist(b);
	}
	return sign(a ^ b) == 1;
}

vector<point> convex_hull(vector<point> p) {
	int n = p.size();
	for (int i = 1; i < n; i++) {
		if (p[i] < p[0]) {
			swap(p[i], p[0]);
		}
	}
	p0 = p[0];
	sort(p.begin() + 1, p.end(), cmp);
	vector<point> hull;
	for (int i = 0; i < n; i++) {
		while (hull.size() >= 2) {
			int last = hull.size() - 1;
			vec v1 = hull[last] - hull[last - 1];
			vec v2 = p[i] - hull[last];
			if (sign(v1 ^ v2) == 1) break;
			hull.pop_back();
		}
		hull.push_back(p[i]);
	}
	return hull;
}

const ld EPS = 1e-6;

bool check(point a, point b, point x) {
	return abs(dist(a, x) + dist(b, x) - dist(a, b)) < EPS;
	if (a == x || b == x) return true;
	if (a == b) return false; 
	vec v1 = b - a;
	vec v2 = x - a;
	if (sign(v1 ^ v2)) return false;
	if (sign(v1 * v2) != 1) return false;
	v1 = a - b;
	v2 = x - b;
	if (sign(v2 * v2) != 1) return false;
	return true;
}

bool check(point a, vector<point> p) {
	int n = p.size();
	ld ans = 0;
	for (int i = 0; i < n; i++) {
		point x = p[i];
		point y = p[(i + 1) % n];
		if (check(x, y, a)) return false;
		x = x - a;
		y = y - a;
		ans += atan2(x ^ y, x * y);
	}
	return abs(ans) > EPS;
}

int n;
point a;
vector<point> p;

void read() {
	cin >> n;
	cin >> a.x >> a.y;
	p.resize(n);
	for (auto &i : p)
		cin >> i.x >> i.y;
}

void no() {
	cout << "NO\n";
	exit(0);
}

point ans;

bool check_angle(vec a, vec b, vec x) {
	if (sign(a ^ b) == -1) swap(a, b);
	return sign(a ^ x) >= 0 && sign(x ^ b) >= 0;
}

void run() {
	p = convex_hull(p);
	n = (int)p.size();
	if (n == 1) {
		ans = a - (p[0] - a);
		return;
	} 
	for (int i = 0; i < n; i++) {
		point x = p[i];
		point y = p[(i + 1) % n];
		if (!check(x, y, a)) continue;
		vec v1 = y - x;
		v1 = vec(v1.y, -v1.x);
		ans = a + v1;
		return;
	}
	if (check(a, p)) no();

	for (int i = 0; i < n; i++) {
		point x = p[i];
		point y = p[(i + 1) % n];
		vec perp = y - x;
		perp = vec(perp.y, -perp.x);
		vec norm = y - x;
		if (sign(norm ^ (a - x)) > 0) continue;
		ans = a + perp;
		return;
	}
}

void write() {
	cout << "YES\n";
	cout << ans.x << " " << ans.y << "\n";
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