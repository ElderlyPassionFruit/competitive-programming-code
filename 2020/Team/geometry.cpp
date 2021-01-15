//cout.precision(20)!!!
const ld EPS = 1e-9;

struct point{
    ld x,y;
    point() {}
    point(ld a, ld b) {
        x = a, y = b;
    }
};

bool operator<(point a, point b) {
    return tie(a.x, a.y) < tie(b.x, b.y);
}

bool operator==(point a, point b) {
    return abs(a.x - b.x) < EPS && abs(a.y - b.y) < EPS;
}

point operator-(point a, point b) {
    return point(a.x - b.x, a.y - b.y);
}

point operator+(point a, point b) {
    return point(a.x + b.x, a.y + b.y);
}

ld operator^(point a, point b) {
    return a.x * b.y - a.y * b.x;
}

ld operator*(point a, point b) {
    return a.x * b.x + a.y * b.y;
}

ld sq(ld x) {
    return x * x;
}

#define vec point

ld dist(vec a) {
    return sqrt(sq(a.x) + sq(a.y));
}

ld dist(point a, point b) {
    return dist(a - b);
}

bool check(point a, point b, point x) {
    return abs(dist(a, x) + dist(b, x) - dist(a, b)) < EPS;
}

struct line{
    ld a, b, c;
    line() {}
    line(ld x, ld y, ld z) {
        a = x, b = y, c = z;
    }
    line(point x, point y) {
        a = y.y - x.y;
        b = x.x - y.x;
        c = x.y * y.x - x.x * y.y;
    }
};

bool operator==(line l, line m) {
    return abs(m.a * l.b - m.b * l.a) < EPS && 
           abs(m.c * l.a - m.a * l.c) < EPS && 
           abs(m.c * l.b - m.b * l.c) < EPS;
}

bool is_parallel(line l, line m) {
    return !(l == m) && abs(m.a * l.b - m.b * l.a) < EPS;
}

point cross(line l, line m) {
    point ans;
    ans.x = m.b * l.c - m.c * l.b;
    ans.y = m.c * l.a - m.a * l.c;

    ans.x /= m.a * l.b - m.b * l.a;
    ans.y /= m.a * l.b - m.b * l.a;
    return ans;
}

ld dist(point a, line l) {
    return abs((l.a * a.x + l.b * a.y + l.c) / sqrt(sq(l.a) + sq(l.b)));
}

// Вектор нормали к прямой (a, b)
// Направляющий вектор прямой (-b, a)

struct circle{
    point o;
    ld r;
    circle() {}
    circle(point a, ld x) {
        o = a, r = x;
    }
    circle(ld a, ld b, ld x) {
        o = point(a, b);
        r = x;
    }
};

bool operator==(circle a, circle b) {
    return a.o == b.o && abs(a.r - b.r) < EPS;
}

vec norm(vec a, ld d) {
    ld x = dist(a);
    a.x /= x;
    a.y /= x;
    a.x *= d;
    a.y *= d;
    return a;
}

vector<point> cross(circle o, line l) {
    ld d = dist(o.o, l);
    if (d - o.r > EPS) {
        return {};
    }
    vec v = norm(vec(l.a, l.b), d);
    point x = o.o + v;
    if (abs(dist(x, l)) > EPS) {
        x = o.o - v;
    }
    if (abs(d - o.r) < EPS) {
        return {x};
    }
    ld y = sqrt(sq(o.r) - sq(d));
    vec u = norm(vec(-l.b, l.a), y);
    return {x + u, x - u};
}

vector<point> cross(circle a, circle b) {
    line l;
    l.a = 2 * (b.o.x - a.o.x);
    l.b = 2 * (b.o.y - a.o.y);
    l.c = sq(a.o.x) - sq(b.o.x) + sq(a.o.y) - sq(b.o.y) - sq(a.r) + sq(b.r);
    return cross(a, l);
}

ld area(const vector<point> & g) {
    int n = g.size();
    ld ans = 0;
    for (int i = 0; i < n; i++) {
        ans += g[i] ^ g[(i + 1) % n];
    }
    return abs(ans) / 2;
}

ld perimeter(const vector<point> & g) {
    int n = g.size();
    ld ans = 0;
    for (int i = 0; i < n; i++) {
        ans += dist(g[i], g[(i + 1) % n]);
    }
    return ans;
}

point p0;

bool cmp(point a, point b) {
    a = a - p0;
    b = b - p0;
    if (abs(a ^ b) < EPS) {
        return dist(a) < dist(b);
    }
    return (a ^ b) > 0;
}

vector<point> convex_hull(vector<point> g) {
    int n = g.size();
    for (int i = 1; i < n; i++) {
        if (g[i] < g[0])
            swap(g[i], g[0]);
    }
    p0 = g[0];
    sort(g.begin() + 1, g.end(), cmp);
    vector<point> hull;
    for (int i = 0; i < n; i++) {
        while (hull.size() >= 2) {
            int last = hull.size() - 1;
            vec v1 = hull[last] - hull[last - 1];
            vec v2 = g[i] - hull[last];
            if ((v1 ^ v2) > 0)
                break;
            hull.pop_back();
        }
        hull.push_back(g[i]);
    }
    return hull;
}

bool check(point x, vector<point> g) {
    int n = g.size();
    ld ans = 0;
    for (int i = 0; i < n; i++) {
        point a = g[i];
        point b = g[(i + 1) % n];
        if (check(a, b, x))
            return true;
        // Если границы не учитываются нужно ставить false
        ans += (a - x) ^ (b - x);
    }
    return abs(ans) > 3;
}