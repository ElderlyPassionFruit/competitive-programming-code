#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()
#define int ll
struct point{
	ll x, y;
};

point operator-(const point & a, const point & b) {
	return {a.x - b.x, a.y - b.y};
}

ll operator^(const point & a, const point & b) {
	return a.x * b.y - a.y * b.x;
}

bool check(point a, point b, point c) {
	b = b - a;
	c = c - a;
	return (b ^ c) != 0;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int n;
	cin >> n;
	point a, b;
	cin >> a.x >> a.y >> b.x >> b.y;
	for (int i = 0; i < n - 2; i++) {
		point c;
		cin >> c.x >> c.y;
		if (check(a, b, c)) {
			cout << "Yes" << endl;
			cout << "1 2 " << i + 3 << endl;
			return 0;
		}
	}
	cout << "No" << endl;
	return 0;
}