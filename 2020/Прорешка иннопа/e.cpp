#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

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

struct Line{
    ld a, b, c;
    Line() {}
    Line(ld _a, ld _b, ld _c) {
        a = _a, b = _b, c = _c;
    }
};

ld sq(ld x) {
    return x * x;
}

ld dist(Point a, Line l) {
    return abs(l.a * a.x + l.b * a.y + l.c) / sqrt(sq(l.a) + sq(l.b));
}

struct Circle{
    Point o;
    ld r;
    Circle() {}
    Circle(Point _o, ld _r) {
        o = _o;
        r = _r;
    }
};

const ld EPS = 1e-9;

int sign(ld x) {
    if (x < -EPS) return -1;
    if (x > EPS) return 1;
    return 0;
}

void tangents (Point c, ld r1, ld r2, vector<Line>& ans) {
    ld r = r2 - r1;
    ld z = sq(c.x) + sq(c.y);
    ld d = z - sq(r);
    if (sign(d) == -1)  return;
    d = sqrt(abs(d));
    Line l;
    l.a = (c.x * r + c.y * d) / z;
    l.b = (c.y * r - c.x * d) / z;
    l.c = r1;
    ans.push_back(l);
}
 
vector<Line> tangents(Circle a, Circle b) {
    vector<Line> ans;
    for (int i = -1; i <= 1; i += 2)
        for (int j = -1; j <= 1; j += 2)
            tangents(b.o - a.o, a.r * i, b.r * j, ans);
    for (int i = 0; i < ans.size(); ++i)
        ans[i].c -= ans[i].a * a.o.x + ans[i].b * a.o.y;
    return ans;
}

const int N = 2e3 + 10;
int n;
Point a[N];

void read() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i].x >> a[i].y;
    }
}

bool check(ld r) {
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            auto have = tangents(Circle(a[i], r), Circle(a[j], r));
            /*cerr << "i = " << i << " j = " << j << endl;
            cerr << "(x - " << a[i].x << ")^2 + (y - " << a[i].y << ")^2 = " << r * r << endl;
            cerr << "(x - " << a[j].x << ")^2 + (y - " << a[j].y << ")^2 = " << r * r << endl;
            cerr << "have = " << endl;
            for (auto line : have) {
                cerr << "x * " << line.a << " + y * " << line.b << " + " << line.c << "= 0" << endl;
            }*/
            for (auto line : have) {
                bool ok = true;
                bool L = false, R = false;
                for (int x = 0; x < n; ++x) {
                    int sgn = sign(line.a * a[x].x + line.b * a[x].y + line.c);
                    if (sgn == -1) {
                        L = true;
                    } else if (sgn == 1) {
                        R = true;
                    }
                    if (sign(dist(a[x], line) - r)== -1) {
                        ok = false;
                        break;
                    }
                }
                if (ok && L && R) {
                    return true;
                }
            }
        }
    }
    return false;
}

ld ans;

void run() {
    //cerr << check(0.5) << endl;
    //exit(0);
    ld l = 0, r = 2e9 + 228 * sqrt(2) + 228;
    for (int it = 0; it < 100; ++it) {
        ld mid = (l + r) / 2;
        if (check(mid)) {
            l = mid;
        } else {
            r = mid;
        }
    }
    ans = l;
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