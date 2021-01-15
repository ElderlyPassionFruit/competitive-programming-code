#pragma comment(linker, "/STACK:100000000")
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <ctime>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
using namespace std;
#define int64 long long
#define ldb long double
#define pb push_back
#define mp make_pair
#define fs first
#define sc second
#define sz(a) ((int) (a).size())
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#define taskname "collider"
const ldb pi = acos(-1.0);
const double eps = 1e-10;
const double inf = 1e18;

struct pt {
    double x, y;
    pt() {}
    pt(double x, double y): x(x), y(y) {}
    void read() {
        scanf("%lf%lf", &x, &y);
    }
};

pt operator-(const pt& a, const pt& b) {
    return pt(a.x - b.x, a.y - b.y);
}

double smul(const pt& a, const pt& b) {
    return a.x * b.x + a.y * b.y;
}

ldb det2(ldb a, ldb b, ldb c, ldb d) {
    return a * d - b * c;
}

ldb vmul(const pt& a, const pt& b) {
    return det2(a.x, a.y, b.x, b.y);
}

bool on_segment(const pt& a, const pt& b, const pt& c) {
    return (smul(c - a, c - b) < eps);
}

bool is_convex(const pt& a, const pt& b, const pt& c) {
    return (vmul(b - a, c - b) > eps);
}

struct line {
    double a, b, c;
    line(const pt& p1, const pt& p2): a(p1.y - p2.y), b(p2.x - p1.x), c(- a * p1.x - b * p1.y) {
        double d = sqrt(a * a + b * b);
        a /= d, b /= d, c /= d;
    }
};

int side(const pt& a) {
    return ((a.y > eps) || ((a.y > -eps) && (a.x > -eps))) ? 0 : 1;
}

bool operator<(const pt& a, const pt& b) {
	int ap = side(a), bp = side(b);
	if (ap != bp) return (ap < bp);
	ldb vm = vmul(a, b);
	if (fabsl(vm) > eps) return (vm > eps);
	if (fabsl(a.x - b.x) > eps) return (a.x < b.x - eps);
	if (fabsl(a.y - b.y) > eps) return (a.y < b.y - eps);
	return false;
}

bool operator<(const line& a, const line& b) {
    pt n1(a.a, a.b), n2(b.a, b.b);
    int a1 = side(n1), a2 = side(n2);
    if (a1 != a2) return (a1 < a2);
    double vm = vmul(n1, n2);
    if (fabs(vm) > eps) return (vm > eps);
    if (fabs(a.c - b.c) > eps) return (a.c < b.c - eps);
    return false;
}

bool cross(const line& a, const line& b, pt& p) {
    double d = det2(a.a, a.b, b.a, b.b);
    if (fabs(d) < eps) return false;
    p = pt(det2(-a.c, a.b, -b.c, b.b) / d, det2(a.a, -a.c, b.a, -b.c) / d);
    return true;
}

pt ort(const pt& a) {
    return pt(-a.y, a.x);
}

struct hull {
    set<pt> pts;
    set< pair<pt, pt> > dirs;
    pt base;
    void fix_convex(set<pt>::iterator it) {
        set<pt>::iterator prev = it, next = it;
        ++next; if (next == pts.end()) next = pts.begin();
        if (prev == pts.begin()) prev = pts.end(); --prev;
        if (!is_convex(*prev, *it, *next)) {
            dirs.erase(mp(*next - *it, *it));
            dirs.erase(mp(*it - *prev, *prev));
            dirs.insert(mp(*next - *prev, *prev));
            pts.erase(it);
            fix_convex(prev);
            fix_convex(next);
        }
    }
    void add_interesting(vector<pt>& v, const pt& p) {
        set< pair<pt, pt> >::iterator it = dirs.lower_bound(mp(p, pt()));
        if (it == dirs.end()) it = dirs.begin();
        v.pb(pt(it->sc.x, it->sc.y));
    }
    double get(pt p) {
        if (pts.empty()) return 0;
        double smin = inf, smax = -inf;
        vector<pt> v;
        add_interesting(v, p), p.x *= -1, p.y *= -1;
        add_interesting(v, p), p.x *= -1, p.y *= -1;
        p = ort(p);
        for (int i = 0; i < sz(v); ++i) {
            smin = min(smin, smul(v[i], p));
            smax = max(smax, smul(v[i], p));
        }
        return (smax - smin) / sqrt(smul(p, p));
    }
    void add(pt p) {
        if (sz(pts) < 2)
            pts.insert(p);
        else if (sz(pts) == 2) {
            pt p1 = *pts.begin(), p2 = *pts.rbegin();
            pts.clear();
            if (fabs(vmul(p - p1, p - p2)) < eps) {
                if (on_segment(p1, p2, p)) pts.insert(p1), pts.insert(p2);
                else if (on_segment(p1, p, p2)) pts.insert(p1), pts.insert(p);
                else pts.insert(p2), pts.insert(p);
            } else {
                base = pt((p1.x + p2.x + p.x) / 3.0, (p1.y + p2.y + p.y) / 3.0);
                pts.insert(p1 - base), pts.insert(p2 - base), pts.insert(p - base);
            }
        } else {
            p = p - base;
            set<pt>::iterator it = pts.insert(p).fs, prev = it, next = it;
            ++next; if (next == pts.end()) next = pts.begin();
            if (prev == pts.begin()) prev = pts.end(); --prev;
            dirs.erase(mp(*next - *prev, *prev));
            dirs.insert(mp(*next - *it, *it));
            dirs.insert(mp(*it - *prev, *prev));
            fix_convex(it);
            fix_convex(prev);
            fix_convex(next);
        }
        if (sz(pts) <= 3) {
            dirs.clear();
            vector<pt> v(pts.begin(), pts.end());
            for (int i = 0; i < sz(pts); ++i) dirs.insert(mp(v[(i + 1) % sz(pts)] - v[i], v[i]));
        }
    }
};

set<line> s;
int n;
char c;
hull h;
pt p1, p2;

void work(line l) {
    set<line>::iterator it = s.insert(l).fs, next = it, prev = it;
    ++next; if (next == s.end()) next = s.begin();
    if (prev == s.begin()) prev = s.end(); --prev;
    pt p;
    if (cross(l, *next, p)) h.add(p);
    if (cross(l, *prev, p)) h.add(p);
}

void build(line l) {
    work(l);
    l.a *= -1, l.b *= -1, l.c *= -1;
    work(l);
}

int main() {
    //assert(freopen(taskname".in", "r", stdin));
    //assert(freopen(taskname".out", "w", stdout));
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf(" %c", &c);
        p1.read(), p2.read();
        if (c == '?') printf("%.10lf\n", h.get(p2 - p1) * h.get(ort(p2 - p1)));
        else build(line(p1, p2));
    }
    return 0;
}