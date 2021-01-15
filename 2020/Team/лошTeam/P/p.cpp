#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

#define int ll

struct point{
	int x, y;
	point() {}
	point(int _x, int _y) {
		x = _x, y = _y;
	}
};

int operator^(const point & a, const point & b) {
	return a.x * b.y - a.y * b.x;
}

int operator*(const point & a, const point & b) {
	return a.x * b.x + a.y * b.y;
}

point operator-(const point & a, const point & b) {
	return point(a.x - b.x, a.y - b.y);
}

int sign(int x) {
	if (x == 0) return 0;
	if (x > 0) return 1;
	return -1;
}

int n;
vector<point> p;

bool check(point a, point b, point x) {
	return sign((b - a) ^ (x - a)) == -1;
}

int get(int x) {
	return (x - 1) * (x - 2) / 2;
}

bool check(point a) {
	ld ans = 0;
	for (int i = 0; i < n; i++) {
		point x = p[i];
		point y = p[(i + 1) % n];
		x = x - a;
		y = y - a;
		ans += atan2(x ^ y, x * y);
	}
	return abs(ans) > 1;
}

void solve() {
	point a;
	cin >> a.x >> a.y;
	if (!check(a)) {
		cout << 0 << endl;
		return;
	}
	int ans = n * (n - 1) * (n - 2) / 6;
	//cout << "ans = " << ans << endl;
	int pos = 0;
	for (int i = 0; i < n; i++) {
		pos = max(pos, i + 1);
		while (check(p[i], p[pos], a)) {
			pos++;
		}
	//	cout << "nxt = " << pos << " i = " << i << endl;
		ans -= get(pos - i);
	}
	cout << ans << endl;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n;
	p.resize(n);
	for (auto &i : p) {
		cin >> i.x >> i.y;
	}
	for (int i = 0; i < n; i++) {
		p.push_back(p[i]);
	}
	int t;
	cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}