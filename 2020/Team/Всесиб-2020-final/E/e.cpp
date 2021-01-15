#include <bits/stdc++.h>

#define f first
#define s second
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
#define ll long double
#define ull unsigned long long
#define db long double
#define ld long double
#define pii pair<int, int>
#define pil pair<int, ll>
#define pli pair<ll, int>
#define pll pair<ll, ll>
#define px pair<db, db>
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define input(a) for (auto& el : a) cin >> el;
#define output(a) cout << '!'; for (auto& el : a) cout << el << ' '; cout << '\n'; cout.flush();
#define sz(el) int(el.size())
#define sq(a) ((a) * (a))
#define xll __int128
#define xmin(a,b) a = min(a, b)
#define xmax(a,b) a = max(a, b)
#define sun(a) sort(all(a)); a.resize(unique(all(a)) - a.begin());

using namespace std;

template <class T1, class T2>
ostream& operator<<(ostream& out, const pair<T1, T2>& p) {
    return (out << p.f << ' ' << p.s << endl);
}

const int INF = 1000000017;
const ll LLINF = 1000000000000000017LL;
const ld inf = 1.0 / 0.0;
const ld eps = 1e-2;
const int MOD = 1e9 + 7;
const int MOD2 = 1e9 + 9;

//mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

//uniform_int_distribution<int> uid(l, r); [l, r]
//int x = uid(rng);

/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> tret;

/// *find_by_order - val by index, order_of_key - # less than x
*/

/// Author: @mathalex
namespace geometry {
    const ld PI = atan2(0, -1);
    const ld EPS = 1e-2;

    struct Point {
        ll x = 0, y = 0;

        Point() {}

        Point(const ll& x, const ll& y) : x(x), y(y) {}

        bool operator==(const Point& a) const {
            return abs(x - a.x) < EPS && abs(y - a.y) < EPS;
        }

        bool operator!=(const Point& a) const {
            return (x - a.x) > EPS || (y - a.y) > EPS;
        }

        bool operator<(const Point& a) const {
            return x < a.x || (x == a.x && y < a.y);
        }

        bool operator>(const Point& a) const {
            return x > a.x || (x == a.x && y > a.y);
        }

        Point operator+(const Point& a) const {
            return {x + a.x, y + a.y};
        }

        Point operator-(const Point& a) const {
            return {x - a.x, y - a.y};
        }

        Point operator*(const ll& a) const {
            return {x * a, y * a};
        }

        Point operator/(const ll& a) const {
            return {x / a, y / a};
        }
    };

    struct Vector {
        ll x = 0, y = 0;

        Vector() {}

        Vector(const ll& x, const ll& y) : x(x), y(y) {}

        Vector(const Point& a) : x(a.x), y(a.y) {}

        Vector(const Point& a, const Point& b) : x(b.x - a.x), y(b.y - a.y) {}

        Vector operator-() const {
            return {-x, -y};
        }

        Vector operator+(const Vector& a) const {
            return {x + a.x, y + a.y};
        }

        void operator+=(const Vector& a) {
            x += a.x;
            y += a.y;
        }

        Vector operator-(const Vector& a) const {
            return {x - a.x, y - a.y};
        }

        void operator-=(const Vector& a) {
            x -= a.x;
            y -= a.y;
        }

        ll operator*(const Vector& a) const {
            return a.x * x + a.y * y;
        }

        ll operator%(const Vector& a) const {
            return a.y * x - a.x * y;
        }

        Vector operator*(const ll& r) const {
            return {x * r, y * r};
        }

        void operator*=(const ll& r) {
            x *= r;
            y *= r;
        }

        Vector operator/(const ll& r) const {
            return {x / r, y / r};
        }

        void operator/=(const ll& r) {
            x /= r;
            y /= r;
        }

        ld len() const {
            return sqrt(x * x + y * y);
        }
    };

    struct Line {
        ld a = 0, b = 0, c = 0;

        Line() {}

        Line(const ll& a, const ll& b, const ll& c) : a(a), b(b), c(c) {}

        Line(const Point& a, const Point& b) : a(b.y - a.y), b(a.x - b.x), c(a.y * b.x - a.x * b.y) {}

        Line(const Point& p, const Vector& v) : a(v.y), b(-v.x), c(p.y * v.x - p.x * v.y) {}

        bool operator==(const Line& x) const {
            return (abs(a * x.b - b * x.a) < EPS &&
                    abs(a * x.c - c * x.a) < EPS &&
                    abs(b * x.c - c * x.b) < EPS);
        }
    };

    ld angle(const Vector& v, const Vector& u) {
        return abs(atan2(v % u, v * u));
    }

    ld angleOrient(const Vector& v, const Vector& u) {
        return atan2(v % u, v * u);
    }

    ll ptLine(const Point& a, const Line& line) {
        return line.a * a.x + line.b * a.y + line.c;
    }

    ld dist(const Point& a, const Point& b) {
        return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    }

    ld dist(const Point& a, const Line& line) {
        return abs(ptLine(a, line)) / sqrt(line.a * line.a + line.b * line.b);
    }

    ld ordist(const Point& a, const Line& line) {
        return ptLine(a, line) / sqrt(line.a * line.a + line.b * line.b);
    }

    void norm(Vector& a, const ld& r) {  /// parameters of Vector should be long double
        ld d = sqrt(a.x * a.x + a.y * a.y);
        a.x /= d;
        a.y /= d;
        a.x *= r;
        a.y *= r;
    }

    bool intersect(const Line& a, const Line& b, Point& p) {
        if (a.a * b.b - b.a * a.b == 0) {
            return 0;
        }
        p = Point((b.c * a.b - a.c * b.b) / (a.a * b.b - b.a * a.b), (a.a * b.c - b.a * a.c) / (b.a * a.b - a.a * b.b));
        return 1;
    }

    Point operator+(const Point& a, const Vector& v) {
        return {a.x + v.x, a.y + v.y};
    }

    Point operator-(const Point& a, const Vector& v) {
        return {a.x - v.x, a.y - v.y};
    }

    struct Circle {
        Point c;
        ll r = 0;

        Circle() {}

        Circle(const Point& c, const ll& r) : c(c), r(r) {}

        Circle(const Point& a, const Point& b) : c((a + b) / 2), r(dist(a, b) / 2) {}
    };

    bool into(const Circle& c, const Point& p) {
        return dist(c.c, p) <= c.r;
    }

    int intersect(const Circle& c, const Line& s, vector<Point>& pts) {
        ld d = dist(c.c, s);
        Vector v(s.a, s.b);
        norm(v, d);
        Point p1 = c.c + v, p2 = c.c - v;
        if (d > c.r) {
            return 0;
        } else if (abs(d - c.r) < EPS) {
            if (abs(ptLine(p1, s)) < EPS) {
                pts.emplace_back(p1);
            } else {
                pts.emplace_back(p2);
            }
            return 1;
        } else {
            if (abs(ptLine(p2, s)) < EPS) {
                p1 = p2;
            }
            Vector u(-s.b, s.a);
            ld q = sqrt(c.r * c.r - d * d);
            norm(u, q);
            Point p3 = p1 + u, p4 = p1 - u;
            pts.emplace_back(p3);
            pts.emplace_back(p4);
            return 2;
        }
    }

    int intersect(Circle c1, Circle c2, vector<Point>& pts) {
        if (c1.r < eps || c2.r < eps) {
            return 0;
        }
        if (c1.r > c2.r) {
            swap(c1, c2);
        }
        if (c1.c == c2.c && c1.r == c2.r) {
            return 3;
        } else if (c1.r < c2.r - dist(c1.c, c2.c)) {
            return 0;
        } else {
            Line s(2 * (c2.c.x - c1.c.x), 2 * (c2.c.y - c1.c.y),
                   c1.c.x * c1.c.x + c1.c.y * c1.c.y - c2.c.x * c2.c.x - c2.c.y * c2.c.y - c1.r * c1.r + c2.r * c2.r);
            return intersect(c1, s, pts);
        }
    }

    istream& operator>>(istream& in, Point& a) {
        return (in >> a.x >> a.y);
    }

    ostream& operator<<(ostream& out, const Point& a) {
        return (out << a.x << ' ' << a.y << '\n');
    }

    istream& operator>>(istream& in, Vector& a) {
        return (in >> a.x >> a.y);
    }

    ostream& operator<<(ostream& out, const Vector& a) {
        return (out << a.x << ' ' << a.y << '\n');
    }

    istream& operator>>(istream& in, Line& a) {
        return (in >> a.a >> a.b >> a.c);
    }

    ostream& operator<<(ostream& out, const Line& a) {
        return (out << a.a << ' ' << a.b << ' ' << a.c << '\n');
    }

    istream& operator>>(istream& in, Circle& a) {
        return (in >> a.c >> a.r);
    }

    ostream& operator<<(ostream& out, const Circle& a) {
        return (out << a.c << a.r << '\n');
    }
}

using namespace geometry;

ld r;
bool ok(const Point& cur, const pair<Point, ld>& p) {
    ld d = (cur.x - p.f.x) * (cur.x - p.f.x) + (cur.y - p.f.y) * (cur.y - p.f.y);
    return (d >= max(p.s - r, (ld)0.0) * max(p.s - r, (ld)0.0) - eps && d <= (p.s + r) * (p.s + r) + eps);
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << setprecision(20) << fixed;

    int n;
    cin >> n >> r;

    vector<pair<Point, ld>> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].f >> a[i].s;
    }

    int cnt = 0;
    Point p;
    for (int i = 0; i < n; ++i) {
        for (const Point& cur : {a[i].f + Point(max(a[i].s - r, (ld)0.0), 0), a[i].f + Point(a[i].s + r, 0), a[i].f}) {
            int tmp = 0;
            for (int k = 0; k < n; ++k) {
                if (ok(cur, a[k])) {
                    ++tmp;
                }
            }
            if (tmp > cnt) {
                cnt = tmp;
                p = cur;
            }
        }
        for (int j = 0; j < i; ++j) {
            vector<Point> cand;
            Circle ci1(a[i].f, max(a[i].s - r, (ld)0.0)), ci2(a[i].f, a[i].s + r);
            Circle cj1(a[j].f, max(a[j].s - r, (ld)0.0)), cj2(a[j].f, a[j].s + r);
            intersect(ci1, cj2, cand);
            intersect(ci2, cj1, cand);
            intersect(ci2, cj2, cand);
            intersect(ci1, cj1, cand);
            for (Point& cur : cand) {
                int tmp = 0;
                for (int k = 0; k < n; ++k) {
                    if (ok(cur, a[k])) {
                        ++tmp;
                    }
                }
                if (tmp > cnt) {
                    cnt = tmp;
                    p = cur;
                }
            }
        }
    }

    cout << cnt << '\n';
    cout << p;
    for (int k = 0; k < n; ++k) {
        if (ok(p, a[k])) {
            ld phi = atan2(p.y - a[k].f.y, p.x - a[k].f.x);
            if (fabs(phi) < eps) {
                phi = 0;
            }
            if (phi < -eps) {
                phi = 2 * PI + phi;
            }
            //cout << phi << endl;
            phi *= 180 / PI;
            cout << k + 1 << ' ' << phi << '\n';
        }
    }
    return 0;
}