#include <bits/stdc++.h>

using namespace std;
#define int long long
#define double long double
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int INF = 1e9;

struct point{
	double x, y;
	point (double a, double b) {
		x = a, y = b;
	}
};

#define vec point

point operator+(point a, point b) {
	return point(a.x + b.x, a.y + b.y);
}

point operator-(point a, point b) {
	return point(a.x - b.x, a.y - b.y);
}

double operator*(point a, point b) {
	return a.x * b.x + a.y * b.y;
}

double operator^(point a, point b) {
	return a.x * b.y - a.y * b.x;
}

double sq(double x) {
	return x * x;
}

double dist(vec a) {
	return sqrt(sq(a.x) + sq(a.y));
}

double dist(point a, point b) {
	return dist(a - b);
}

struct line{
	double a, b, c;
	line(point x, point y) {
		a = y.y - x.y;
		b = x.x - y.x;
		c = x.y * y.x - x.x * y.y;
	}
};

point cross(line l, line m) {
	point ans;
	ans.x = m.b * l.c - l.c * m.b;
	ans.y = m.c * l.a - l.c * m.a;
	ans.x /= l.b * m.a - m.b * l.a;
	ans.y /= l.b * m.a - m.b * l.a;
	return ans;
}


bool check(point a, point b, point s, point f) {
	vec v1 = a - s;
	vec v2 = b - s;	
	vec x = f - s;
	return ((x ^ v1) * (x ^ v2) < 0);
}

int n;
int x1, y1, x2, y2;
vector<pair <point, vec> > mouse;
vector<point> rect;

void read() {
	cin >> n;
	cin >> x1 >> y1 >> x2 >> y2;
	mouse.resize(n);
	for (auto &i : mouse) {
		cin >> i.first.x >> i.first.y >> i.second.x >> i.second.y;
	}
}

bool check_in(point a) {
	return a.x > min(x1, x2) && a.x < max(x1, x2) && a.y > min(y1, y2) && a.y < max(y1, y2);
}

bool operator==(point a, point b) {
	return tie(a.x, a.y) == tie(b.x, b.y);
}

bool check_is(point a) {
	for (auto i : rect)
		if (i == a)
			return true;
	return false;
}

bool check_on(point a) {
	bool flag1 = a.y > min(y1, y2) && a.y < max(y1, y2);
	bool flag2 = a.x > min(x1, x2) && a.x > max(x1, x2);

	return ((a.x == x1 || a.x == x2) && flag1) || ((a.y == y1 || a.y == y2) && flag2);
}

int eval(line l, point a) {
	return l.a * a.x + l.b * a.y + l.c;
}

bool check(line l, point a) {
	return abs(eval(l, a)) == 0;
}

point get_vert(point x, vec v) {
	line l(x, v);
	for (auto i : rect) {
		if (i == x)
			continue;
		if (check(l, i))
			return i;
	}
	return point(INF, INF);
}

bool check_next(point a, point b) {
	int ind1 = 0;
	for (int i = 0; i < 4; i++)
		if (rect[i] == a)
			ind1 = i;
	int ind2 = 0;
	for (int i = 0; i < 4; i++)
		if (rect[i] == b)
			ind2 = i;
	return abs(ind1 - ind2) <= 1;
}

bool check_good(vec a, vec b) {
	reutrn (a * b) > 0; 
}

vector<pair <point, point> > segs;

vector<point> check2(point a, vec b) {
	vector<point> ans;
	for (int i = 0; i < 4; i++) {
		if (check(segs[i].first, segs[i].second, a, a + b)) {
			point help = cross(line(a, a + b), line(segs[i].first, segs[i].second));
			if (check_good(help - a, b))
				ans.push_back(help);
		}
	}
	return ans;
}

const double EPS = 1e-9;

double ans;

void run() {
	double l = 0, r = 1e9 + 10;

	point a1(x1, y1);
	point a2(x2, y1);
	point a3(x2, y2);
	point a4(x1, y2);

	rect = {a1, a2, a3, a4};

	segs.push_back({a1, a2});
	segs.push_back({a2, a3});
	segs.push_back({a3, a4});
	segs.push_back({a4, a1});

	for (auto x : mouse) {
		if (check_is(x.first)) {
			auto check1 = get_vert(x.first);
			if (check1 != point(INF, INF)) {
				if (check_next(x.first, check1) || !check_good(check1 - x.first, x.second)) {
					r = -INF;
					break;
				}
				else {
					double d = dist(check1, x.first) / dist(x.second);
					chkmin(r, d);
				}
			}
			auto check2 = get_seg(x.first, x.second)[0];
			double d = dist(check2, x.first) / dist(x.second);
			chkmin(r, d); 
		}
		else if (check_on(x)) {
			auto check1 = get_vert(x.first);
			if (check1 != point(INF, INF)) {
				if (!check_good(check1 - x.first, x.second)) {
					r = -INF;
					break;
				}
				else {
					double d = dist(check1, x.first) / dist(x.second);
					chkmin(r, d);
				}
			}
			auto check2 = get_seg(x.first, x.second)[0];
			double d = dist(check2, x.first) / dist(x.second);
			chkmin(r, d); 
		}
		else if (check_in(x)) {

		}
		else {

		}
	}

	if (abs(l - r) < EPS || l > r)
		ans = -1;
	else
		ans = l;
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