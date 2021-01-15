#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

#define int ll

struct point{
	ld x, y;
	point() {}
	point(ld _x, ld _y) {
		x = _x, y = _y;
	}
};

point operator-(const point & a, const point & b) {
	return point(a.x - b.x, a.y - b.y);
}

ld operator^(const point & a, const point & b) {
	return a.x * b.y - a.y * b.x;
}

const ld EPS = 1e-9;

int sign(ld x) {
	if (abs(x) < EPS) return 0;
	if (x > 0) return 1;
	return -1;
}

void no() {
	cout << "no" << endl;
	exit(0);
}

ld sq(ld x) {
	return x * x;
}

ld dist(point a) {
	return sqrt(sq(a.x) + sq(a.y));
}

ld dist(point a, point b) {
	return dist(a - b);
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int n;
	cin >> n;
	if (n % 2) {
		no();
	}
	vector<point> p(n);
	for (auto &i : p)
		cin >> i.x >> i.y;
	for (int i = 0; i < n; i++) {
		point a1 = p[i];
		point a2 = p[(i + 1) % n];
		point b1 = p[(i + n / 2) % n];
		point b2 = p[(i + n / 2 + 1) % n];
		if (sign((a1 - a2) ^ (b1 - b2))) {
			no();
		}
		if (sign(dist(a1 - a2) ^ (b1 - b2))) {
			no();
		}
	}
	cout << "yes" << endl;
	return 0;
}