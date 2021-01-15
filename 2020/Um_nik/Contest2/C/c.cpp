#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

#define int ll
#define vec point

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

point operator/(const point & a, int d) {
	assert(a.x % d == 0 && a.y % d == 0);
	return point(a.x / d, a.y / d);
}

point turn(const point & a) {
	return point(-a.y, a.x);
}

int gcd(int a, int b) {
	if (!a) return b;
	if (!b) return a;
	while (b) {
		a %= b;
		swap(a, b);
	}
	return a;
}

point norm(point a) {
	if (a.x < 0) {
		a.x *= -1, a.y *= -1;
	}
	if (a.x == 0 && a.y < 0) {
		a.y *= -1;
	}
	int g = gcd(abs(a.x), abs(a.y));
	a.x /= g;
	a.y /= g;
	return a;
}

struct line{
	int a, b, c;
	line() {}
	line(point x, point y) {
		a = y.y - x.y;
		b = x.x - y.x;
		c = x.y * y.x - x.x * y.y;
		int g = gcd(abs(a), gcd(abs(b), abs(c)));
		assert(g != 0);
		a /= g;
		b /= g;
		c /= g;
		if (a < 0) {
			a *= -1, b *= -1, c *= -1;
		} else if (a == 0 && b < 0) {
			b *= -1, c *= -1;
		} else if (a == 0 && b == 0 && c < 0) {
			c *= -1;
		}
	}
};

bool operator<(const line & a, const line & b) {
	return tie(a.a, a.b, a.c) < tie(b.a, b.b, b.c);
}

bool operator==(const line & a, const line & b) {
	return tie(a.a, a.b, a.c) == tie(b.a, b.b, b.c);
}

struct circle{
	point o;
	int r;
	circle() {}
	circle(point _o, int _r) {
		o = _o, r = _r;
	}
};

int sq(int x) {
	return x * x;
}

bool checkGood(const circle & a, const circle & b) {
	if (a.r != b.r) return false;
	if (sq(a.o.x - b.o.x) + sq(a.o.y - b.o.y) <= sq(a.r + b.r)) return false;
	return true;
}

line getline(const point & a, const point & b) {
	vec v = a - b;
	v = v / 2;
	point fans = b + v;
	v = turn(v);
	return line(fans, fans + v);
}

const int MAXN = 3e5 + 10, MAXM = 1510;
int n, m;
point seg[MAXN][2];
vector<line> lines;
vector<int> have[MAXN];
vector<int> fans[MAXN];
circle a[MAXN];
vector<point> All[MAXN];
	
void build(int pos) {
	for (int i = 0; i < (int)have[pos].size(); i++) {
		All[pos].push_back(seg[have[pos][i]][0]);
		All[pos].push_back(seg[have[pos][i]][1]);
	}
}

void buildFans(int pos) {
	sort(all(All[pos]));
	All[pos].resize(unique(all(All[pos])) - All[pos].begin());
	fans[pos].resize(All[pos].size() + 1);
	for (int i = 0; i < (int)have[pos].size(); i++) {
		int l = lower_bound(all(All[pos]), seg[have[pos][i]][0]) - All[pos].begin();
		int r = lower_bound(all(All[pos]), seg[have[pos][i]][1]) - All[pos].begin();
		if (l > r) swap(l, r);
		fans[pos][l]++;
		fans[pos][r + 1]--;
	}
	for (int i = 1; i < (int)fans[pos].size(); i++) {
		fans[pos][i] += fans[pos][i - 1];
	}
}

void build() {
	for (int i = 0; i < n; i++) {
		lines.push_back(line(seg[i][0], seg[i][1]));	
	}
	sort(all(lines));
	lines.resize(unique(all(lines)) - lines.begin());
	for (int i = 0; i < n; i++) {
		line now(seg[i][0], seg[i][1]);
		int pos = lower_bound(all(lines), now) - lines.begin();
		have[pos].push_back(i);
	}
	for (int i = 0; i < (int)lines.size(); i++) {
		build(i);
	}
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		cin >> seg[i][0].x >> seg[i][0].y >> seg[i][1].x >> seg[i][1].y;
		seg[i][0].x *= 2;
		seg[i][0].y *= 2;
		seg[i][1].x *= 2;
		seg[i][1].y *= 2;
	}
	for (int i = 0; i < m; i++) {
		cin >> a[i].o.x >> a[i].o.y >> a[i].r;
		a[i].o.x *= 2;
		a[i].o.y *= 2;
		a[i].r *= 2;
	}
	build();
	for (int i = 0; i < m; i++) {
		for (int j = i + 1; j < m; j++) {
			if (!checkGood(a[i], a[j])) continue;
			line now = getline(a[i].o, a[j].o);
			int pos;
			pos = lower_bound(all(lines), now) - lines.begin();
			if (pos == (int)lines.size() || !(lines[pos] == now)) continue;
			point centr = a[i].o + a[j].o;
			centr =  centr / 2;
			All[pos].push_back(centr);
		}
	}

	for (int i = 0; i < (int)lines.size(); i++) {
		buildFans(i);
	}

	/*cout << "segs = " << endl;
	for (int i = 0; i < n; i++) {
		cout << "(" << seg[i][0].x << "," << seg[i][0].y << ")" << endl;
		cout << "(" << seg[i][1].x << "," << seg[i][1].y << ")" << endl;
	}

	cout << "lines = " << endl;
	for (auto i : lines) {
		cout << "x * " << i.a << " + y * " << i.b << " + " << i.c << " = 0" << endl;
	}

	cout << "circle = " << endl;
	for (int i = 0; i < m; i++) {
		cout << "(x - " << a[i].o.x << ")^2 + (y - " << a[i].o.y << ")^2 = " << a[i].r * a[i].r << endl;
	}

	cout << "All = " << endl;
	for (int i = 0; i < (int)lines.size(); i++) {
		cout << "i = " << i << endl;
		for (auto have : All[i]) {
			cout << "(" << have.x << "," << have.y << ")" << endl;
		}
	}*/

	ll ans = 0;
	for (int i = 0; i < m; i++) {
		for (int j = i + 1; j < m; j++) {
			if (!checkGood(a[i], a[j])) continue;
			line now = getline(a[i].o, a[j].o);
			int pos;
			pos = lower_bound(all(lines), now) - lines.begin();
			if (pos == (int)lines.size() || !(lines[pos] == now)) continue;
			point centr = a[i].o + a[j].o;
			centr =  centr / 2;
			//All[pos].push_back(centr);
			int posCentr = lower_bound(all(All[pos]), centr) - All[pos].begin();
			ans += fans[pos][posCentr];
		}
	}

	cout << ans << endl;
	return 0;
}