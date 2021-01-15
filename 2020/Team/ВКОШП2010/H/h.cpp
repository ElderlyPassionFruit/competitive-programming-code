#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

struct point{
	ll x, y;
	point() {}
	point(ll a, ll b) {
		x = a, y = b;
	}
};

bool operator<(const point & a, const point & b) {
	return tie(a.x, a.y) < tie(b.x, b.y);
}

struct line{
	ll a, b, c;
	line() {}
	line(point x, point y) {
		a = y.y - x.y;
		b = x.x - y.x;
		c = x.y * y.x - x.x * y.y;
	}
};

ld eval(line l, ll x) {
	return (ld) (-l.a * x - l.c) / l.b;
}
 
signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int n, d;
	cin >> n >> d;
	vector<point> a(n);
	for (auto &i : a)
		cin >> i;
	sort(all(a));
	vector<point> up, down;
	for (int i = 1; i < n; i++) {
		if (a[i].y >= a[0].y)
			up.push_back(a[i]);
		else
			down.push_back(a[i]);
	}

	cout << ans << endl;
	return 0;
}