#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

#define int ll

struct Point{
    int x, y;
    Point() {}
    Point(int _x, int _y) {
        x = _x, y = _y;
    }
};

Point operator-(const Point& a, const Point& b) {
    return Point(a.x - b.x, a.y - b.y);
}

int operator^(const Point& a, const Point& b) {
    return a.x * b.y - a.y * b.x;
}

int sign(int x) {
    if (x > 0) return 1;
    if (x < 0) return -1;
    return 0;
}

bool check(Point a, Point b, Point c, Point x) {
    return sign((x - a) ^ (b - a)) * sign((x - a) ^ (c - a)) <= 0;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    Point a, b, c;
    cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y;
    Point x = Point(0, 0);
    bool ok = true;
    ok &= check(a, b, c, x);
    ok &= check(b, a, c, x);
    ok &= check(c, a, b, x);
    if (ok) {
        cout << "987654321\n";
    } else {
        cout << -a.x << " " << -a.y << " " << -b.x << " " << -b.y << " " << -c.x << " " << -c.y << endl;
    }
	return 0;
}