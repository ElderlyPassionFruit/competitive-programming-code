#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const ld EPS = 1e-9;

struct point{
	ld x, y;
	point() {}
	point(ld a, ld b) {
		x = a, y = b;
	}
};

point operator-(const point & a, const point & b) {
	return point(a.x - b.x, a.y - b.y); 
}

point operator+(const point & a, const point & b) {
	return point(a.x + b.x, a.y + b.y); 
}

ld operator^(const point & a, const point & b) {
	return a.x * b.y - a.y * b.x;
}

ld operator*(const point & a, const point & b) {
	return a.x * b.x + a.y * b.y;
}

ld sq(ld x) {
	return x * x;
}

#define vec point

ld dist(vec a) {
	return sqrt(sq(a.x) + sq(a.y));
}

ld dist(point a, point b) {
	return dist(a - b);
}

vec norm(vec a, ld d) {
	ld x = dist(a);
	a.x /= x;
	a.y /= x;
	a.x *= d;
	a.y *= d;
	return a;
}

struct line{
	ld a, b, c;
	line() {}
	line(ld x, ld y, ld z) {
		a = x, b = y, c = z;
	}
	line(point x, point y) {
		a = y.y - x.y;
		b = x.x - y.x;
		c = x.y * y.x - x.x * y.y;
	}
};

bool operator==(const line & l, const line & m) {
	return abs(m.a * l.b - m.b * l.a) < EPS && 
		   abs(m.c * l.a - m.a * l.c) < EPS && 
		   abs(m.c * l.b - m.b * l.c) < EPS;
}

bool is_parallel(const line & l, const line & m) {
	return !(l == m) && abs(m.a * l.b - m.b * l.a) < EPS;
}

point cross(line l, line m) {
	point ans;
	ans.x = m.b * l.c - m.c * l.b;
	ans.y = m.c * l.a - m.a * l.c;

	ans.x /= m.a * l.b - m.b * l.a;
	ans.y /= m.a * l.b - m.b * l.a;
	return ans;
}

ld dist(line l, point a) {
	return abs(l.a * a.x + l.b * a.y + l.c) / sqrt(sq(l.a) + sq(l.b));
}

bool check(line l, point a) {
	return abs(l.a * a.x + l.b * a.y + l.c) < EPS;
}

point proection(line l, point a) {
	ld len = dist(l, a);
	vec x = vec(l.a, l.b);
	x = norm(x, len);
	point ans = a + x;
	if (!check(l, ans))
		ans = a - x;
	return ans;
}

bool check(point a, point b, point c) {
	return abs(dist(a, b) - dist(a, c) - dist(b, c)) < EPS;
}

bool operator==(point a, point b) {
	return abs(a.x - b.x) < EPS && abs(a.y - b.y) < EPS;
}

bool check(point a, point b, const vector<point> & g) {
	int n = g.size();
	vector<point> have;
	line l = line(a, b);
	for (int i = 0; i < n; i++) {
		line m = line(g[i], g[(i + 1) % n]);
		if (l == m) continue;
		if (is_parallel(l, m)) continue;
		if (!check(a, b, cross(l, m))) continue;
		if (!check(g[i], g[(i + 1) % n], cross(l, m))) continue;
		have.push_back(cross(l, m));
	}

	if (have.empty()) return true;
	sort(all(have), [&] (point a, point b) {return tie(a.x, a.y) < tie(b.x, b.y);});
	vector<point> uni;
	uni.push_back(have[0]);
	for (int i = 1; i < (int) have.size(); i++) {
		if (have[i] == uni.back()) continue;
		uni.push_back(have[i]);
	}
	have = uni;

	if (have.size() > 2) return false;
	if (have.size() == 1) return true;
	for (int i = 0; i < n; i++) {
		point a = g[i], b = g[(i + 1) % n];
		if (tie(a.x, a.y) > tie(b.x, b.y))
			swap(a, b); 
		if ((a == have[0]) && (b == have[1]))
			return true;
	}
	return false;
} 

point petr;
ld v;
int n;
vector<point> g;

const int MAXN = 110;
const ld INF = 1e9;

ld pref[MAXN];
ld petr_can[MAXN];
ld light_can[MAXN];

line l1, l2;

ld get_light(line l, point a) {
	point p = proection(l, a);
	if (check(a, p, g))
		return dist(l, a);
	return INF;
}

ld get_light(point x) {
	return min(get_light(l1, x), get_light(l2, x));
}

void build() {
	for (int i = 1; i <= n; i++)
		pref[i] = pref[i - 1] + dist(g[i - 1], g[i % n]); 
	
	for (int i = 0; i < n; i++) {
		petr_can[i] = INF;
		if (check(petr, g[i], g))
			petr_can[i] = dist(petr, g[i]);
	}

	vector<point> help = g;
	sort(all(help), [&] (point a, point b) {
		if (abs(a ^ b) < EPS) return dist(a) < dist(b);
		return (a ^ b) > 0;
	});

	l1 = line(point(0, 0), help[0]);
	l2 = line(point(0, 0), help[n - 1]);

	for (int i = 0; i < n; i++) {
		light_can[i] = get_light(g[i]);
	}
}

ld get_path(int i, int j) {
	if (i < j) swap(i, j);
	return min(pref[i] - pref[j], pref[n] - (pref[i] - pref[j]));
}

ld get_full_path(int i, int j) {
	return petr_can[i] + light_can[j] + get_path(i, j);
}	

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.setf(ios::fixed), cout.precision(50);
	cin >> petr.x >> petr.y >> v;
	cin >> n;
	g.resize(n);
	for (auto &i : g){
		cin >> i.x >> i.y;
	}
	build();

	if (check(petr, point(0, 0), g)) {
		cout << 0 << endl;
		return 0;
	}
	ld ans = get_light(petr);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			ans = min(ans, get_full_path(i, j));
		}
	}

	ans /= v;
	cout << ans << endl;
	return 0;
}