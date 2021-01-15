#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;

#define all(x) (x).begin(), (x).end()
template <typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;};
template <typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (y > x) x = y;};

struct point{
	ll x, y;
	point() {}
	point(ll a, ll b) {
		x = a, y = b;
	}
};

point operator-(const point & a, const point & b) {
	return point(a.x - b.x, a.y - b.y);
}

ll operator^(const point & a, const point & b) {
	return a.x * b.y - a.y * b.x;
}

ll operator*(const point & a, const point & b) {
	return a.x * b.x + a.y * b.y;
}

point a, x, y;

void read() {
	cin >> a.x >> a.y >> x.x >> x.y >> y.x >> y.y;
}

#define vec point

bool ans;

void run() {
	a = a - x;
	y = y - x;
	ans = ((a ^ y) == 0) && ((a * y) >= 0);
}

void write() {
	if (ans) cout << "YES";
	else cout << "NO";
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.setf(ios::fixed), cout.precision(20);
	read();
	run();
	write();
	return 0;
}