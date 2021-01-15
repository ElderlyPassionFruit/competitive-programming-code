#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

struct vec{
	ld x, y, z;
	vec() {}
	vec(ld _x, ld _y, ld _z) {
		x = _x, y = _y, z = _z;
	}
};

vec operator-(const vec & a, const vec & b) {
	return vec(a.x - b.x, a.y - b.y, a.z - b.z);
}

vec operator+(const vec & a, const vec & b) {
	return vec(a.x + b.x, a.y + b.y, a.z + b.z);
}

ld sq(ld x) {
	return x * x;
}

ld dist(vec a) {
	return sqrt(sq(a.x) + sq(a.y) + sq(a.z));
}

ld dist(vec a, vec b) {
	return sqrt(sq(a.x - b.x) + sq(a.y - b.y) + sq(a.z - b.z));
}

void norm(vec & a, ld d) {
	ld D = dist(a);
	a.x = a.x / d * D;
	a.y = a.y / d * D;
	a.z = a.z / d * D;
}

const ld EPS = 1e-8;

int sign(ld x) {
	if (x > EPS) return 1;
	if (x < -EPS) return -1;
	return 0;
}

const int MAXN = 1e4 + 10;
int n;
vec a[MAXN];
ld vs, vp;
vec start;

vec getPoint(ld t) {
	for (int i = 0; i + 1 < n; i++) {
		if (sign(dist(a[i], a[i + 1]) / vs - t) <= 0) {
			t -= dist(a[i], a[i + 1]) / vs;
		} else {
			vec v = a[i + 1] - a[i];
			norm(v, t * vs);
			return v + a[i];
		}
	}
	return a[n - 1];
}

bool check(ld t) {
	return sign(dist(getPoint(t), start) / vp - t) <= 0;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cout.setf(ios::fixed);
	cin >> n;
	n++;
	for (int i = 0; i < n; i++) {
		cin >> a[i].x >> a[i].y >> a[i].z;
	}
	cin >> vs >> vp;
	cin >> start.x >> start.y >> start.z;
	ld r = 0;
	for (int i = 0; i + 1 < n; i++) {
		//cout << dist(a[i], a[i + 1]) << endl;
		r += dist(a[i], a[i + 1]);
	}

	//vec fans = vec(10.0000000000, 4.5000000000, 0.0000000000);

	r /= vs;
	//cout << dist(fans, start) / vp << endl;
	if (sign(dist(a[n - 1], start) / vp - r) == 1) {
		cout << "NO\n";
		return 0;
	}
	ld l = 0;
	for (int it = 0; it < 120; it++) {
		ld mid = (l + r) / 2;
		if (check(mid)) {
			r = mid;
		} else {
			l = mid;
		}
	}
	cout << "YES" << endl;
	cout << r << endl;
	auto ans = getPoint(r);
	cout << ans.x << " " << ans.y << " " << ans.z << endl;
	return 0;
}