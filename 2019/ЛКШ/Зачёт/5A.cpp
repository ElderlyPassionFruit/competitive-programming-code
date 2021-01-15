#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4")
#include <bits/stdc++.h>

using namespace std;
#define pb push_back
#define double long double
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

long long area(vector<point> g) {
	long long ans = 0;
	long long n = g.size();
	for (long long i = 0; i < n; i++) {
		ans += g[i] ^ g[(i + 1) % n];
	}
	return abs(ans);
}

long long sq(long long a) {
	return a * a;
}

long long dist(point a) {
	return sq(a.x) + sq(a.y);
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
	long long n = g.size();
	for (long long i = 0; i < n; i++) {
		if (g[i].y < g[0].y || (g[i].y == g[0].y && g[i].x < g[0].x))
			swap(g[0], g[i]);
	}
	p0 = g[0];
	sort(g.begin() + 1, g.end(), cmp);
	vector<point> hull;
	for (long long i = 0; i < n; i++) {
		while (hull.size() >= 2) {
			long long last = hull.size() - 1;
			point v1 = hull[last] - hull[last - 1];
			point v2 = g[i] - hull[last];
			if ((v1 ^ v2) > 0)
				break;
			hull.pop_back();
		}
		hull.push_back(g[i]);
	}
	return hull;
}

vector<point> g;
int n;

void read() {
	cin >> n;
	g.resize(n);
	for (auto &i : g)
		cin >> i.x >> i.y;
}

bool operator==(const point & a, const point & b) {
	return tie(a.x, a.y) == tie(b.x, b.y);
}

bool operator<(const point & a, const point & b) {
	return tie(a.x, a.y) < tie(b.x, b.y);
}

struct line{
	long long a, b, c;
	line(point & x, point & y) {
		a = y.y - x.y;
		b = x.x - y.x;
		c = x.y * y.x - x.x * y.y;
	}
};

inline long long dist(line & l, point & x) {
	return abs(l.a * x.x + l.b * x.y + l.c);
}

inline int get(line & l1, int l, int r) {
	while (l < r - 2) {
		int mid1 = l + (r - l) / 3;
		int mid2 = r - (r - l) / 3;
		if (dist(l1, g[mid1]) < dist(l1, g[mid2]))
			l = mid1;
		else
			r = mid2; 
	}
	
	int ans = l;
	for (int i1 = l + 1; i1 <= r; i1++) {
		if (dist(l1, g[ans]) < dist(l1, g[i1]))
			ans = i1;
	}
	return ans;
}

inline int get(line & l1, int pos) {
	while (pos < 2 * n && dist(l1, g[pos]) <= dist(l1, g[pos + 1]))
		pos++;
	return pos;
}

long long ans;

inline void calc() {
	g = convex_hull(g);
	n = g.size();
	for (int i = 0; i < n; i++)
		g.push_back(g[i]);

	ans = 0;
	for (int i = 0; i < n; i++) {
		int pos1 = i + 1;
		int pos2 = i + 2;
		for (int j = i + 2; j < n - 1; j++) {
			line l(g[i], g[j]);

			pos1 = get(l, pos1);
			pos2 = get(l, pos2);
			
			chkmax(ans, area({g[i], g[pos1], g[j], g[pos2]}));
		}
	}
}

inline void run() {
	auto x = convex_hull(g);	
	if (x.size() == 3) {
		ans = 0;
		for (auto i : g) {
			set<point> help = {x[0], x[1], x[2], i};
			if (help.size() < 4)
				continue;
			long long fans = 1e18 + 10;
			chkmin(fans, area({x[0], x[1], i}));
			chkmin(fans, area({x[0], x[2], i}));
			chkmin(fans, area({x[1], x[2], i}));
			chkmax(ans, area({x[0], x[1], x[2]}) - fans);
		}
		return;
	}

	calc();
}

inline void write() {
	cout << ans / 2;
	if (ans % 2 == 1)
		cout << ".5";
	else
		cout << ".0";
	cout << endl;
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