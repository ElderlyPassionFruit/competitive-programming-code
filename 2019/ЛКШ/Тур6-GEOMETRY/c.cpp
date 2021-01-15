#include <bits/stdc++.h>

using namespace std;
#define pb push_back
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

#define vec point

vec operator-(vec a, vec b) {
	return point(a.x - b.x, a.y - b.y);
}

long long operator^(vec a, vec b) {
	return a.x * b.y - a.y * b.x;
}

long long sq(long long x) {
	return x * x;
}

long long dist(vec a) {
	return sq(a.x) + sq(a.y);
}

long long dist(point a, point b) {
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
		if (g[i].y < g[0].y || (g[i].y == g[0].y && g[i].x < g[0].x))
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

struct line{
	long long a, b, c;
	line() {
		a = 0, b = 0, c = 0;
	}	
	line(long long x, long long y, long long z) {
		a = x, b = y, c = z;
	}
};

bool half(vec a) {
	return a.y > 0 || (a.y == 0 && a.x >= 0);
}

bool cmp_half(vec a, vec b) {
	if (half(a) != half(b))
		return half(a);
	return (a ^ b) > 0;
}

bool check(line x, const vector<point> &g, const vector<vec> &help) {
	vec x1 = vec(-x.b, x.a);
	vec x2 = vec(x.b, -x.a);

	int pos1 = lower_bound(help.begin(), help.end(), x1, cmp_half) - help.begin();
	int pos2 = lower_bound(help.begin(), help.end(), x2, cmp_half) - help.begin();
	
	int n = g.size();
	point p1 = g[pos1 % n];
	point p2 = g[pos2 % n];

	long long c1 = -x.a * p1.x -x.b * p1.y;
	long long c2 = -x.a * p2.x -x.b * p2.y;
	if (c1 > c2)
		swap(c1, c2);

	return c1 <= x.c && c2 >= x.c;
}

int n, m;
vector<line> q;
vector<point> g;
vector<vec> help;
void read() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		line x;
		cin >> x.a >> x.b >> x.c;
		q.push_back(x);
	}
	for (int i = 0; i < m; i++) {
		point x;
		cin >> x.x >> x.y;
		g.push_back(x);
	}
}

vector<int> ans;

void run() {
	g = convex_hull(g);
	m = g.size();

	for (int i = 0; i < m; i++) {
		help.push_back(g[(i + 1) % m] - g[i]);
	}

	for (int i = 0; i < n; i++) {
		if (check(q[i], g, help))
			ans.push_back(i + 1);
	}
}

void write() {
	cout << ans.size() << endl;
	for (auto i : ans)
		cout << i << " ";
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