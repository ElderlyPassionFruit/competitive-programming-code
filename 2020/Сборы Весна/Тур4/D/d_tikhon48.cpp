#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long
#define all(a) (a).begin(), (a).end()
#define pii pair <int, int>
 
struct point {
    ll x, y;
    point() {}
    point (int x_, int y_) {
        x = x_;
        y = y_;
    }
    void show() {
        cout << "(" << x << ", " << y << ")\n";
    }
};
 
point operator+(point a, point b) {
    a.x += b.x;
    a.y += b.y;
    return a;
}
point operator-(point a, point b) {
    a.x -= b.x;
    a.y -= b.y;
    return a;
}
ll operator*(point a, point b) {
    return a.x * b.x + a.y * b.y;
}
ll operator%(point a, point b) {
    return a.x * b.y - a.y * b.x;
}
 
ll dist(point a) {
    return a.x * a.x + a.y * a.y;
}
 
struct segment {
    point p0;
    point p1;
    segment() {}
    segment(point p0_, point p1_) {
        p0 = p0_;
        p1 = p1_;
    }
};
 
ll operator%(segment s, point p) {
    return (s.p1 - s.p0) % (p - s.p0);
}
 
struct polygon {
    vector<point> p;
    int n;
    polygon() {
        n = 0;
    };
    void add(point p_) {
        p.push_back(p_);
        n++;
    }
 
    bool left(int i, point a) {
        int vp = ((p[i] - a) % (p[(i + 1) % n] - a));
        if (vp == 0) {
            return dist(p[i] - a) < dist(p[(i + 1) % n] - a);
        }
        return vp > 0;
    }
 
    pair <point, point> left_t(point a) {
        // cout << "lef_t\n";
        int l = 0;
        int r = n;
        while (l + 1 < r) {
            int m = (l + r) / 2;
            if ((p[0] - a) % (p[m] - a) >= 0) {
                l = m;
            } else {
                r = m;
            }
        }
 
        int cpos = l;
        // cout << "cpos = " << cpos << '\n';
 
        int pos1;
        if (cpos == 0) {
            pos1 = 0;
        } else {
            l = 0;
            r = cpos + 1;
            while (l + 1 < r) {
                int m = (l + r) / 2;
                if (left(m, a)) {
                    l = m;
                } else {
                    r = m;
                }
            }
            pos1 = r;
        }
 
        l = cpos;
        r = n;
        while (l + 1 < r) {
            int m = (l + r) / 2;
            if (left(m, a)) {
                r = m;
            } else {
                l = m;
            }
        }
        int pos2 = (r % n);
        return {p[pos1], p[pos2]};
    }
 
    pair <point, point> right_t(point a) {
        // cout << "righ_t\n";
        int l = 0;
        int r = n;
        while (l + 1 < r) {
            int m = (l + r) / 2;
            if ((p[0] - a) % (p[m] - a) < 0) {
                l = m;
            } else {
                r = m;
            }
        }
        int cpos = r;
        // cout << "cpos = " << cpos << '\n';
        l = 0;
        r = cpos;
 
        while (l + 1 < r) {
            int m = (l + r) / 2;
            if (left(m, a)) {
                r = m;
            } else {
                l = m;
            }
        }
        int pos2 = (r % n);
 
        l = cpos - 1;
        r = n;
        while (l + 1 < r) {
            int m = (l + r) / 2;
            if (left(m, a)) {
                l = m;
            } else {
                r = m;
            }
        }
        int pos1 = (r % n);
        return {p[pos1], p[pos2]};
    }
 
    pair <point, point> tangent(point a) {
        if (left(0, a)) {
            return left_t(a);
        } else {
            return right_t(a);
        }
    }
};
 
 
bool inside(point p, point a, point b, point c) {
    if ((b - a) % (c - a) < 0) swap(b, c);
    if ((b - a) % (p - a) < 0) return 0;
    if ((c - a) % (p - a) > 0) return 0;
    if ((c - b) % (p - b) < 0) return 0;
    return 1;
}
 
int n, k;
polygon pol;
vector<point> p;
 
vector<int> used;
 
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
 
    cin >> k >> n;
    int x, y;
    for (int i = 0; i < k; i++) {
        cin >> x >> y;
        pol.add(point(x, y));
    }
 
    p.resize(n);
     
    for (int i = 0; i < n; i++) {
        cin >> x >> y;
        p[i] = point(x, y);
    }
 
    int ans = 0;
 
    for (int i = 0; i < n; i++) {
        auto tg = pol.tangent(p[i]);
        for (int j = i + 1; j < n; j++) {
            bool good = 0;
            if ((tg.first - p[i]) % (p[j] - p[i]) >= 0) {
                good = 1;
            }
            if ((tg.second - p[i]) % (p[j] - p[i]) <= 0) {
                good = 1;
            }
            if (inside(p[j], p[i], tg.first, tg.second)) {
                good = 1;
            }
            ans += good;
        }
    }
 
    cout << ans;
     