#include <bits/stdc++.h>

using namespace std;
#define int long long

struct point{
	int x, y;
	point() {
		x = 0, y = 0;
	}
	point(int a, int b) {
		x = a, y = b;
	}
};

int operator^(point a, point b) {
	return a.x * b.y - a.y * b.x;
}

int operator*(point a, point b) {
	return a.x * b.x + a.y * b.y;
}

point operator-(point a, point b) {
	return point(a.x - b.x, a.y - b.y);
}

point operator+(point a, point b) {
	return point(a.x + b.x, a.y + b.y);
}

bool operator==(point a, point b) {
	return a.x == b.x && a.y == b.y;
}

bool check1(point a, point b, point c, point d) {
	return (a == c) || (a == d) || (b == c) || (b == d); 
}

double sq(double x) {
	return x * x;
}

double dist(point a) {
	return sqrt(sq(a.x) + sq(a.y));
}

bool check2(point a, point b, point x) {
	return abs(dist(a - x) + dist(b - x) - dist(a - b)) < 1e-6;
}

bool check2(point a, point b, point c, point d) {
	return check2(a, b, c) || check2(a, b, d) || check2(c, d, a) || check2(c, d, b);
}

void print(point a) {
	cout << a.x << " " << a.y << "\n";
}

bool check(point a, point b, point c, point d) {
	if (check1(a, b, c, d)) return true;
	if (check2(a, b, c, d)) return true;

	point v1, v2, v3;
	v1 = b - a;
	v2 = c - a;
	v3 = d - a;
	point u1, u2, u3;
	u1 = c - d;
	u2 = a - d;
	u3 = b - d;
	if (((u1 ^ u2) * (u1 ^ u3) < 0) && ((v1 ^  v2) * (v1 ^ v3) < 0)) return true;
	return false;
}

#define double long double

bool check(vector<point> g, point x) {
	double ans = 0;
	int n = g.size();
	for (int i = 0; i < n; i++) {
		point a = g[i] - x;
		point b = g[(i + 1) % n] - x;
		if (check2(a + x, b + x, x))
			return true;
		ans += atan2(a ^ b, a * b);
	}
	return abs(ans) > 1e-6;
}

void solve() {
	int n;
	cin >> n;
	vector<point> p1(n);
	for (auto &i : p1)
		cin >> i.x >> i.y;
	int m;
	cin >> m;
	vector<point> p2(m);
	for (auto &i : p2)
		cin >> i.x >> i.y;

	for (int i = 0; i < n; i++) {
		point a = p1[i];
		point b = p1[(i + 1) % n];
		for (int j = 0; j < m; j++) {
			point c = p2[j];
			point d = p2[(j + 1) % m];
			if (check(a, b, c, d)) {
				cout << "YES" << "\n";
				return;
			}
		}
	}

	for (int i = 0; i < n; i++) {
		point x = p1[i];
		if (check(p2, x)) {
			cout << "YES" << "\n";
			return;
 		}
	}

	for (int i = 0; i < m; i++) {
		point x = p2[i];
		if (check(p1, x)) {
			cout << "YES" << "\n";
			return;
		}
	}

	cout << "NO" << "\n";
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t--) 
		solve();
	return 0;
}