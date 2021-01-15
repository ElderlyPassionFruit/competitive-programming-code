#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

struct Point{
    ld x, y;
    Point() {}
    Point(ld _x, ld _y) {
        x = _x, y = _y;
    }
};

Point operator-(const Point& a, const Point& b) {
    return Point(a.x - b.x, a.y - b.y);
}

ld operator^(const Point& a, const Point& b) {
    return a.x * b.y - a.y * b.x;
}

ld operator*(const Point& a, const Point& b) {
    return a.x * b.x + a.y * b.y;
}

const ld EPS = 1e-10;

int sign(ld x) {
    if (x < -EPS) return -1;
    if (x > EPS) return 1;
    return 0;
}

#define Vec Point

struct Circle{
    Point o;
    ld r;
};

ld sq(ld x) {
    return x * x;
}

ld dist(const Vec& a) {
    return sqrt(sq(a.x) + sq(a.y));
}

ld dist(const Point& a, const Point& b) {
    return dist(a - b);
}

ld dist(const Point& a, const Point& b, const Point& x) {
    ld ans = min(dist(a, x), dist(b, x));
    Vec v1, v2;
    v1 = b - a;
    v2 = x - a;
    if (sign(v1 * v2) == -1) return ans;
    v1 = a - b;
    v2 = x - b;
    if (sign(v1 * v2) == -1) return ans;
    return fabs(v1 ^ v2) / dist(a, b);
}

bool checkOnSegment(const Point& a, const Point& b, const Point& x) {
    Vec v1, v2;
    v1 = b - a;
    v2 = x - a;
    if (sign(v1 ^ v2) != 0) return false;
    if (sign(v1 * v2) == -1) return false;
    v1 = a - b;
    v2 = x - b;
    if (sign(v1 * v2) == -1) return false;
    return true; 
}

bool checkIn(const Point& a, const vector<Point>& p) {
    ld ans = 0;
    int n = p.size();
    for (int i = 0; i < n; ++i) {
        Point x = p[i];
        Point y = p[(i == n - 1 ? 0 : i + 1)];
        if (checkOnSegment(x, y, a)) {
            return true;
        }
        x = x - a;
        y = y - a;
        ans += atan2(x ^ y, x * y);
    }
    return fabs(ans) > 1;
}

bool checkCross(const Circle& a, const vector<Point>& p) {
    if (checkIn(a.o, p)) return true;
    int n = p.size();
    for (int i = 0; i < n; ++i) {
        int nxt = i + 1;
        if (nxt == n) nxt = 0;
        if (sign(dist(p[i], p[nxt], a.o) - a.r) <= 0) {
            return true;
        }
    }
    return false;
}

ld area(const vector<Point>& p) {
    ld ans = 0;
    int n = p.size();
    for (int i = 0; i < n; ++i) {
        ans += (p[(i + 1) % n].x - p[i].x) * (p[(i + 1) % n].y + p[i].y) / 2;
    }
    return fabs(ans);
}

const int N = 1e6 + 10;
ld w, h;
int n;
vector<Point> p[N];
bool used[N];

void solve() {
    fill(used, used + n, false);
    int cntAns = 0;
    ld fans = 0;
    Circle o;
    cin >> o.o.x >> o.o.y >> o.r;
    for (int i = 0; i < n; ++i) {
        if (checkCross(o, p[i])) {
            used[i] = true;
            fans += area(p[i]);
            ++cntAns;
        }
    }
    cout << fans << " " << cntAns;
    for (int i = 0; i < n; ++i) {
        if (used[i]) {
            cout << " " << i;
        }
    }
    cout << "\n";
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cout.setf(ios::fixed), cout.precision(20);
    cin >> w >> h >> n;
    for (int i = 0; i < n; ++i) {
        int sz;
        cin >> sz;
        p[i].resize(sz);
        for (auto &pt : p[i]) {
            cin >> pt.x >> pt.y;
        }
    }
    int q;
    cin >> q;
    while (q--) {
        solve();
    }
    return 0;
}