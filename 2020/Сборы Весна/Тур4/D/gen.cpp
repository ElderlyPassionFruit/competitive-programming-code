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


signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n = get(1, 5);
	vector<point> have;
	have.push_back({0, 0});
	have.push_back({1, 0});
	have.push_back({1, 1});
	return 0;
}