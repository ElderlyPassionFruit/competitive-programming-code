#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()
using ld = long double;
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct point{
	int x, y;
	point() {
	}
	point(int a, int b) {
		x = a, y = b;
	}
};

int operator^(const point & a, const point & b) {
	return a.x * b.y - a.y * b.x;
}

int operator*(const point & a, const point & b) {
	return a.x * b.x + a.y * b.y;
}

point operator-(const point & a, const point & b) {
	return point(a.x - b.x, a.y - b.y);
}

point operator+(const point & a, const point & b) {
	return point(a.x + b.x, a.y + b.y);
}

ld sq(ld a) {
	return a * a;
}

#define vec point

ld dist(const vec & a) {
	return sqrt(sq(a.x) + sq(a.y));
}

ld dist(const point & a, const point & b) {
	return dist(a - b);
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
		if (g[i].y < g[0].y || (g[i].y == g[0].y && g[i].x < g[0].x))
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
			if ((v1 ^ v2) > 0) break;
			hull.pop_back();
		}
		hull.push_back(g[i]);
	}
	return hull;
}

bool half(const vec & a) {
	return a.y > 0 || (a.y == 0 && a.x >= 0);
}

bool cmp_half(const vec & a, const vec & b) {
	if (half(a) != half(b))
		return half(a);
	return (a ^ b) > 0;
}

vector<vec> make(const vector<point> & a) {
	vector<vec> v_a;
	int n = a.size();
	for (int i = 0; i < n; i++) {
		v_a.push_back(a[(i + 1) % n] - a[i]);
	}
	return v_a;
}

point find(vector<point> a) {
	int n = a.size();
	for (int i = 0; i < n; i++) {
		if (a[i].y < a[0].y || (a[i].y == a[0].y && a[i].x < a[0].x))
			swap(a[0], a[i]);
	}
	return a[0];
}

vector <point> get_poly(const vector<point> & a, point a0, const vector<point> & b, point b0) {
	if (a.empty())
		return b;
	if (b.empty())
		return a;
	
	vector<vec> fans((int)a.size() + (int)b.size());
	merge(a.begin(), a.end(), b.begin(), b.end(), fans.begin(), cmp_half);
	fans.pop_back();

	vector<point> ans;
	ans.push_back(a0 + b0);
	for (auto i : fans)
		ans.push_back(i + ans.back());
	return ans;
}

const double INF = 1e18;

bool check(point a, point b, point x) {
	vec v1 = x - a, v2 = b - a;
	if (v1 * v2 < 0) return false;
	v1 = x - b, v2 = a - b;
	if (v1 * v2 < 0) return false;
	return true;
}

ld dist(point a, point b, point x) {
	ld ans = INF;
	chkmin(ans, dist(a, x));
	chkmin(ans, dist(b, x));
	if (check(a, b, x)) {
		vec v1 = a - b;
		vec v2 = x - b;
		int s = abs(v1 ^ v2);
		chkmin(ans, (ld) s / dist(a, b));
	}
	return ans;
}

ld dist(point a, const vector<point> & g) {
	ld ans = INF;
	int n = g.size();
	for (int i = 0; i < n; i++) {
		point x = g[i];
		point y = g[(i + 1) % n];
		chkmin(ans, dist(x, y, a));
	}
	return ans;
}

const int MAXN = 210;

int n, s, f;
vector<point> p[MAXN];
point best_p[MAXN];
vector<point> rp[MAXN];
point best_rp[MAXN];
ld dp[MAXN][MAXN];

void read() {
	cin >> n >> s >> f;
	s--;
	f--;
	for (int i = 0; i < n; i++) {
		int k;
		cin >> k;
		p[i].resize(k);
		for (auto &j : p[i])
			cin >> j.x >> j.y;
		p[i] = convex_hull(p[i]);
		rp[i] = p[i];
		for (auto &j : rp[i])
			j.x *= -1, j.y *= -1;
		rp[i] = convex_hull(rp[i]);
		best_p[i] = find(p[i]);
		p[i] = make(p[i]);
		best_rp[i] = find(rp[i]);
		rp[i] = make(rp[i]);
	}
}

void build() {
	for (int i = 0; i < n; i++) {
		for (int j = i; j < n; j++) {
			if (i == j) {
				dp[i][j] = 0;
				continue;
			}
			dp[i][j] = dist(point(0, 0), get_poly(p[i], best_p[i], rp[j], best_rp[j]));
			dp[j][i] = dp[i][j];
		}
	}
}

ld ans;

ld d[MAXN];

void calc() {
	for (int i = 0; i < MAXN; i++)
		d[i] = INF;
	d[s] = 0;
	set<pair<int, int> > q;
	q.insert({0, s});
	while (!q.empty()) {
		auto x = *q.begin();
		q.erase(q.begin());
		int v = x.second;
		for (int i = 0; i < n; i++) {
			if (d[i] > d[v] + dp[v][i]) {
				q.erase({d[i], i});
				d[i] = d[v] + dp[v][i];
				q.insert({d[i], i});
			}
		}
	}
	ans = d[f];
}

void run() {
	build();
	calc();
}

void write() {
	cout.precision(20);
	cout << ans << endl;
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