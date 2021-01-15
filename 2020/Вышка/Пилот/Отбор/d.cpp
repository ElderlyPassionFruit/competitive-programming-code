#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

#define int ll

struct Point{
	ll x, y;
	Point() {}
	Point(ll _x, ll _y) {
		x = _x, y = _y;
	}
};

ld dist(Point a) {
	return sqrt(a.x * a.x + a.y * a.y);
}

ll operator^(const Point & a, const Point & b) {
	return a.x * b.y - a.y * b.x;
}

ll operator*(const Point & a, const Point & b) {
	return a.x * b.x + a.y * b.y;
}

const ll EPS = 1e-9;

int sign(ll x) {
	if (x > 0) return 1;
	if (x < 0) return -1;
	return 0;
}

const ld PI = acos(-1);
Point a, b;

void read() {
	cin >> a.x >> a.y >> b.x >> b.y;
}

ld ans;

void run() {
	ans = dist(a) + dist(b);
	ld fans = abs(dist(a) - dist(b));
	if (sign(a ^ b) < 0) swap(a, b);
	//cout << atan2(a ^ b, a * b) << endl;
	fans += atan2(a ^ b, a * b) * min(dist(a), dist(b));
	chkmin(ans, fans);
}

void write() {
	cout << ans << endl;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
	read();
	run();
	write();
	return 0;
}