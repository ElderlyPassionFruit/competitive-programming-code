#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const ld EPS = 1e-7;

int sign(ld x) {
	if (x > EPS) return 1;
	if (x < -EPS) return -1;
	return 0;
}

struct pt{
	ld x, y;
	pt() {}
	pt(ld _x, ld _y) {
		x = _x, y = _y;
	}
};

pt operator-(const pt & a, const pt & b) {
	return pt(a.x - b.x, a.y - b.y);
}

ld operator^(const pt & a, const pt & b) {
	return a.x * b.y - a.y * b.x;
}

void check(pt x1, pt x2) {
	if (sign(x1 ^ x2) == 0) {
		cout << 0 << endl;
		exit(0);
	}
}

ld getTy0(pt x1, pt v1) {
	if (sign(x1.y) == 0) return 0;
	if (sign(v1.y) == 0) return -1;
	return -x1.y / v1.y;
}

ld getY0(pt x1, pt v1, pt x2, pt v2) {
	ld t1 = getTy0(x1, v1);
	ld t2 = getTy0(x2, v2);
	if (sign(t1) <= 0 || sign(t2) <= 0) return 1e9;
	if (sign(t1 - t2) != 0) return 1e9;
	return t1;
}

ld solve(ld A, ld B, ld C) {
	if (sign(A) == 0) {
		if (sign(B) == 0 || sign(C) == 0) {
			return 1e9;
		}
		ld ans = -C / B;
		if (sign(ans) <= 0) {
			ans = 1e9;
		}
		return ans;
	}
	ld d = B * B - 4 * A * C;
	if (sign(d) == -1) return 1e9;
	d = sqrt(d);
	ld x1 = (-B + d) / (2 * A);
	ld x2 = (-B - d) / (2 * A);
	if (sign(x1) <= 0) x1 = 1e9;
	if (sign(x2) <= 0) x2 = 1e9;
	return min(x1, x2);
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	ld t;
	cin >> t;
	pt x1, v1, x2, v2, x3, v3;
	cin >> x1.x >> x1.y >> v1.x >> v1.y; 
	cin >> x2.x >> x2.y >> v2.x >> v2.y; 
	cin >> x3.x >> x3.y >> v3.x >> v3.y;
	x1 = x1 - x3;
	x2 = x2 - x3;
	v1 = v1 - v3;
	v2 = v2 - v3;
	check(x1, x2);
	ld ans = 1e9;
	ans = min(ans, getY0(x1, v1, x2, v2));
	//cerr << ans << endl;
	ans = min(ans, solve(
		v1.x * v2.y - v2.x * v1.y,
		x1.x * v2.y + v1.x * x2.y - v1.y * x2.x - v2.x * x1.y,
		x1.x * x2.y - x2.x * x1.y
		));
	//cerr << ans << endl;
	if (sign(t - ans) == -1) {
		cout << -1 << endl;
		exit(0);
	}
	cout.precision(20);
	cout.setf(ios::fixed);
	cout << ans << endl;
	return 0;
}