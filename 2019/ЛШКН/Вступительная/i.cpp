#include <bits/stdc++.h>

using namespace std;
#define int long long
#define double long double
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const double EPS = 1e-6;

struct point{
	double x, y;
	point() {
		x = 0, y = 0;
	}
	point(double a, double b) {
		x = a, y = b;
	}
};

point operator+(point a, point b) {
	return point(a.x + b.x, a.y + b.y);
}

point operator-(point a, point b) {
	return point(a.x - b.x, a.y - b.y);
}

double operator^(point a, point b) {
	return a.x * b.y - a.y * b.x;
}

double operator*(point a, point b) {
	return a.x * b.x + a.y * b.y;
}

bool check(double x) {
	return abs(x) < EPS;
}

bool check(double x, double y) {
	return check(x - y);
}

bool is_less(double x, double y) {
	return !check(x, y) && x < y;
}

bool operator==(point a, point b) {
	return check(a.x, b.x) && check(a.y, b.y);
}

bool operator!=(point a, point b) {
	return !(a == b);
}

bool operator<(point a, point b) {
	return is_less(a.x, b.x) || (check(a.x, b.x) && is_less(a.y, b.y));
}

bool operator>(point a, point b) {
	return !(a == b) && !(a < b);
}


istream& operator >> (istream& in, point& p) {
	in >> p.x >> p.y;
	return in;
}

ostream& operator << (ostream& in, point& p) {
	in << p.x << " " << p.y;
	return in;
}

double sq(double x) {
	return x * x;
}

double dist(point a) {
	return sqrt(sq(a.x) + sq(a.y));
}

double dist(point a, point b) {
	return dist(a - b);
}

point p0;
bool cmp(pair <point, int> a, pair <point, int> b) {
	a.first = a.first - p0;
	b.first = b.first - p0;
	if (check(a.first ^ b.first)) {
		return dist(a.first) < dist(b.first);
	}
	return (a.first ^ b.first) > 0;
}

vector<pair <point, int> > convex_hull(vector<pair<point, int> > g) {
	int n = g.size();
	for (int i = 0; i < n; i++) {
		if (g[i] < g[0]) swap(g[i], g[0]);
	}
	p0 = g[0].first;
	sort(g.begin() + 1, g.end(), cmp);

	vector<pair<point, int> > hull;

	for (int i = 0; i < n; i++) {
		while (hull.size() >= 2) {
			int last = hull.size() - 1;
			auto p1 = hull[last].first - hull[last - 1].first;
			auto p2 = g[i].first - hull[last].first;
			if ((p1 ^ p2) > 0) break;
			hull.pop_back();
		}
		hull.push_back(g[i]);
	}
	return hull;
}

double ang(point a, point b) {
	return atan2(a ^ b, a * b);
}

int n;
vector<pair<point, int> > a;

void read() {
	cin >> n;
	a.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i].first;
		a[i].second = i;
	}
	a = convex_hull(a);
	n = a.size();
}

set<pair <int, int> > ans;

#define vec point

point mid(point a, point b) {
	point ans = a + b;
	ans.x /= 2;
	ans.y /= 2;
	return ans;
}

bool check_in(point o, double r, point x) {
	return check(dist(o, x), r) || r > dist(o, x);
}

bool check_on(point o, double r, point x) {
	return check(dist(o, x), r);
}


void make(point &x) {
	if (check(x.x)) x.x = 0;
	if (check(x.y)) x.y = 0;
}

void run() {
	pair <point, int> x1, x2;
	x1 = a[0], x2 = a[0];
	for (int i = 0; i < n; i++) {
		chkmin(x1, make_pair(a[i].first, i));
		chkmax(x2, make_pair(a[i].first, i));
	}

	vector<pair <point, point> > ed;
	int ind1 = x1.second, ind2 = x2.second;
	vec next1(0, 1);
	vec next2(0, -1);

	bool flag1 = false, flag2 = false;

	while (!flag1 || !flag2) {
		if (ind1 == x2.second) flag1 = true;
		if (ind2 == x1.second) flag2 = true;

		ed.push_back({a[ind1].first, a[ind2].first});
		vec v1 = a[(ind1 + 1) % n].first - a[ind1].first;
		vec v2 = a[(ind2 + 1) % n].first - a[ind2].first;
	
		double angle1 = ang(next1, v1);
		double angle2 = ang(next2, v2);

		if (angle1 < angle2) {
			ind1++;
			ind1 %= n;
			next1 = v1;
			next2 = vec(-v1.x, -v1.y);
		}
		else {
			ind2++;
			ind2 %= n;
			next2 = v2;
			next1 = vec(-v2.x, -v2.y);
		}
	}

	pair <double, point> help = {0, {}};
	for (auto i : ed) {
		chkmax(help, make_pair(dist(i.first, i.second), mid(i.first, i.second)));
	}

	help.first /= 2;

	for (auto i : a) {
		if (!check_in(help.second, help.first, i.first))
			return;
	}

	set<pair <point, int> > p;
	for (auto i : a)
		p.insert(i);

	for (auto i : a) {
		if (check_on(help.second, help.first, i.first)) {
			vec v = help.second - i.first;
			v.x *= 2;
			v.y *= 2;

			point j = i.first + v;
	
			j.x -= EPS / 2;
			j.y -= EPS / 2;
			make(j);
			auto chk = p.lower_bound({j, -1});
			j.x += EPS / 2;
			j.y += EPS / 2;
			make(j);

			if (chk == p.end()) continue;
			if (chk->first == j)
				ans.insert({min(i.second, chk->second), max(i.second, chk->second)});
		}
	}
}

void write() {
	cout << ans.size() << "\n";
	for (auto i : ans)
		cout << i.first + 1 << " " << i.second + 1 << "\n";
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