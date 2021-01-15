#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

struct point{
	ld x, y;
	point() {}
	point(ld a, ld b) {
		x = a, y = b;
	}
};

#define vec point

vec operator+(vec a, vec b) {
	return point(a.x + b.x, a.y + b.y);
}

vec operator-(point a, point b) {
	return point(a.x - b.x, a.y - b.y);
}

double operator^(vec a, vec b) {
	return a.x * b.y - a.y * b.x;
}

struct line{
	ld a, b, c;
	line() {}
	line(point x, point y) {
		a = y.y - x.y;
		b = x.x - y.x;
		c = x.y * y.x - x.x * y.y;
	}
};

struct circle{
	point o;
	ld r;
	circle() {}
	circle(ld x, point a) {
		r = x;
		o = a;
	}
};

ld sq(ld x) {
	return x * x;
}

ld dist(vec a) {
	return sqrt(sq(a.x) + sq(a.y));
}

ld dist(point a, point b) {
	return dist(a - b);
}

ld dist(point a, line l) {
	return abs((l.a * a.x + l.b * a.y + l.c) / sqrt(sq(l.a) + sq(l.b)));
}

vec norm(vec a, ld d) {
	ld x = dist(a);
	a.x /= x;
	a.y /= x;
	a.x *= d;
	a.y *= d;
	return a;	
}

const ld EPS = 1e-10;

bool check(point a, line l) {
	return abs((l.a * a.x + l.b * a.y + l.c)) < EPS;
}

vector<point> cross(circle o, line l) {
	vec x = vec(l.a, l.b);
	ld d = dist(o.o, l);
	x = norm(x, d);
	point o1, o2;
	o1 = o.o + x;
	o2 = o.o - x;
	point O = o1;
	if (!check(o1, l)) O = o2;
	vec y = vec(-l.b, l.a);
	d = sqrt(sq(o.r) - sq(d));
	y = norm(y, d);
	vector <point> ans;
	ans.push_back(O + y);
	ans.push_back(O - y);
	return ans;
}

point p0;

bool cmp(point a, point b) {
	a = a - p0;
	b = b - p0;
	if (abs(a ^ b) < EPS) {
		return dist(a) < dist(b);
	}
	return (a ^ b) > 0;
}

bool operator<(const point & a, const point & b) {
	return tie(a.x, a.y) < tie(b.x, b.y);
}

vector<point> convex_hull(vector<point> g) {
	int n = g.size();
	for (int i = 0; i < n; i++) {
		if (g[i] < g[0])
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
bool cmpkek(point a, point b)
{
	if(abs(a.x- b.x) >EPS) return a.x < b.x;
	return a.y - EPS < b.y;
}
bool operator==(point a, point b)
{
	return abs(a.x - b.x) <EPS&&abs(a.y-b.y)<EPS;
}
vector<point> uni(vector<point> a)
{
	vector<point> ans;
	sort(all(a), cmpkek);
	ans.push_back(a[0]);
	for(int i= 1;i < a.size();++i)
	{
		if(!(a[i]==ans.back()))ans.push_back(a[i]);
	}
	return ans;
}
signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	circle o;
	cin >> o.r >> o.o.x >> o.o.y;
	vector<pair<int,int>> kekos(n);
	for(int i = 0 ; i< n;++i)
	{
		cin>>kekos[i].first>>kekos[i].second;
	}
	sort(all(kekos));
	kekos.resize(unique(all(kekos)) - kekos.begin());
	vector<point> g;	
	for (int i = 0 ;i< kekos.size();++i)
	{
		point now;
		now.x = kekos[i].first;
		now.y = kekos[i].second;
		g.push_back(now);
	}
	g.push_back(o.o + point(0, 1));
	g.push_back(o.o + point(1, 0));
	g.push_back(o.o + point(0, -1));
	g.push_back(o.o + point(-1, 0));
	g = convex_hull(g);
	n = g.size();
	vector<point> ans;
	for (int i = 0; i < n; i++) {
		point a = g[i];
		point b = g[(i + 1) % n];
		vector<point> help = cross(o, line(a, b));
		ans.push_back(help[0]);
		ans.push_back(help[1]);
	}

	sort(all(ans), cmp);
	ans =uni(ans);

	ans = convex_hull(ans);
	assert(ans.size() >= 3 && ans.size() <= 222);
	cout << ans.size() << endl;
	for (auto i : ans)
		cout << fixed << setprecision(8) << i.x << " " << i.y << endl;
	return 0;
}