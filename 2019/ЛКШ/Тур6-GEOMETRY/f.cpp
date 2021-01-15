#include <bits/stdc++.h>

using namespace std;
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
#define vec point
struct point{
	long long x, y;
	point() {
		x = 0, y = 0;
	}
	point(long long a, long long b) {
		x = a, y = b;
	}
};
 
vec operator-(vec a, vec b) {
	return vec(a.x - b.x, a.y - b.y);
}

vec operator+(vec a, vec b) {
	return vec(a.x + b.x, a.y + b.y);
}

long long operator^(vec a, vec b) {
	return a.x * b.y - a.y * b.x;
}

long long operator*(vec a, vec b) {
	return a.x * b.x + a.y * b.y;
}

long double sq(long double x) {
	return x * x;
}
 
long double dist(vec a) {
	return sqrt(sq(a.x) + sq(a.y));
}

long double dist(point a, point b) {
	return dist(a - b);
}

point p0;
bool cmp(vec a, vec b) {
	a = a - p0;
	b = b - p0;
	if ((a ^ b) == 0) {
		return dist(a) < dist(b);
	}
	return (a ^ b) > 0;
}

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
		vec x = g[i];
		vec y = g[(i + 1) % n];
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

bool half(vec a) {
	return a.y > 0 || (a.y == 0 && a.x >= 0);
}

bool cmp_half(vec a, vec b) {
	if (half(a) != half(b))
		return half(a);
	return (a ^ b) > 0;
}

vector<vec> make(vector<point> a) {
	vector<vec> v_a;
	a = convex_hull(a);
	int n = a.size();
	for (int i = 0; i < n; i++) {
		v_a.push_back(a[(i + 1) % n] - a[i]);
	}
	sort(v_a.begin(), v_a.end(), cmp_half);
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

vector <point> summ(vector<point> a, vector<point> b) {
	if (a.empty())
		return b;
	if (b.empty())
		return a;

	auto v_a = make(a);
	auto v_b = make(b);

	vector<vec> fans((int)v_a.size() + (int)v_b.size());

	merge(v_a.begin(), v_a.end(), v_b.begin(), v_b.end(), fans.begin(), cmp_half);
	fans.pop_back();

	vector<point> ans;
	ans.push_back(find(a) + find(b));
	for (auto i : fans)
		ans.push_back(i + ans.back());
	ans = convex_hull(ans);
	return ans;
}

vector<point> g;

void add() {
	int m;
	cin >> m;
	vector<point> help(m);
	for (auto &i : help)
		cin >> i.x >> i.y;
	g = summ(g, help);
}

void read() {
	g = {};
	for (int i = 0; i < 3; i++)
		add();
}

vector<bool> ans;

void run() {
	int q;
	cin >> q;
	for (int i = 0; i < q; i++) {
		point x;
		cin >> x.x >> x.y;
		x.x *= 3;
		x.y *= 3;
		ans.push_back(fast_check(x, g));
	}
}

void write() {
	for (auto i : ans) {
		if (i)
			cout << "YES\n";
		else
			cout << "NO\n";
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