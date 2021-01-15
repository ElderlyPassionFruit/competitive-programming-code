#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

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

ll operator^(const Point& a, const Point& b) {
    return (ll)a.x * b.y - (ll)a.y * b.x;
}

#define Vec Point

ll calcArea(const vector<Point>& p) {
    int n = p.size();
    ll ans = 0;
    for (int i = 0; i < n; ++i) {
        Vec v1 = p[i] - p[0];
        Vec v2 = p[(i + 1) % n] - p[0];
        ans += v1 ^ v2;
    }
    return abs(ans);
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    int n;
    cin >> n;
    ll ans = 0;
    for (int i = 0; i < n; ++i) {
        int sz;
        cin >> sz;
        vector<Point> p(sz);
        for (auto& x : p) {
            cin >> x.x >> x.y;
        }
        ans += calcArea(p);
    }
    cout << ans / 2 << endl;
	return 0;
}