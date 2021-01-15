#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()
#define Time (double)clock()/CLOCKS_PER_SEC

struct point{
    int x, y;
    point() {}
    point(int _x, int _y) {
        x = _x, y = _y;
    } 
};

point operator-(const point & a, const point & b) {
    return point(a.x - b.x, a.y - b.y);
}

int operator^(const point & a, const point & b) {
    return a.x * b.y - a.y * b.x;
}

ld sq(ld x) {
    return x * x;
}

ld dist(point a) {
    return sqrt(sq(a.x) + sq(a.y));
}

ld dist(point a, point b) {
    return dist(a - b);
}

int sign(point p1, point p2, point p3) {
    return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

bool PointInTriangle(point v1, point v2, point v3, point pt) {
    int d1, d2, d3;
    bool has_neg, has_pos;

    d1 = sign(pt, v1, v2);
    d2 = sign(pt, v2, v3);
    d3 = sign(pt, v3, v1);

    has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

    return !(has_neg && has_pos);
}

bool check(point a, point b, point c, point d) {
    return !PointInTriangle(a, b, c, d) && !PointInTriangle(a, c, d, b) && !PointInTriangle(a, b, d, c) && !PointInTriangle(b, c, d, a);
}

bool pointInPolygon(point a, point b, point c, point d, point x) {
    return PointInTriangle(a, b, c, x) || PointInTriangle(a, b, d, x) || PointInTriangle(a, c, d, x) || PointInTriangle(b, c, d, x);
}

vector<point> convexHull(vector<point> p) {
    if (p.empty()) return {};
    sort(all(p), [&] (point a, point b) {
        return tie(a.x, a.y) < tie(b.x, b.y);
    });
    sort(p.begin() + 1, p.end(), [&] (point a, point b) {
        point va = a - p[0];
        point vb = b - p[0];
        return (va ^ vb) > 0;
    });
    vector<point> hull;
    for (int i = 0; i < (int)p.size(); i++) {
        while (hull.size() >= 2) {
            int last = hull.size() - 1;
            point v1 = hull[last] - hull[last - 1];
            point v2 = p[i] - hull[last];
            if ((v1 ^ v2) > 0) break;
            hull.pop_back();
        }
        hull.push_back(p[i]);
    }
    return hull;
}

const int MAXN = 61;
int n, k;
point a[MAXN];

ld get(vector<point> a) {
    a = convexHull(a);
    ld ans = 0;
    for (int i = 0; i < (int)a.size(); i++) {
        ans += dist(a[i], a[(i + 1) % (int)a.size()]);
    }
    return ans;
}

ld ans = 1e18;
vector<int> fans;

int operator*(const point & a, const point & b) {
    return a.x * b.x + a.y * b.y;
}

bool operator==(const point & a, const point & b) {
    return tie(a.x, a.y) == tie(b.x, b.y);
}

bool check(point a, vector<point> have) {
    have = convexHull(have);
    ld ans = 0;
    int n = have.size();
    for (int i = 0; i < n; i++) {
        point x = have[i];
        point y = have[(i + 1) % n];
        if (x == a) return true;
        if (y == a) return true;
        x = x - a;
        y = y - a;
        ans += atan2(x ^ y, x * y);
    }
    return abs(ans) > 1;
}

bool checkCnt(vector<point> p, int sz) {
    p = convexHull(p);
    if (p.size() != sz) return false;
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        cnt += check(a[i], p);
        if (cnt == k) return true;
    }
    return false;
}

bool relax(ld myAns, vector<int> myFans) {
    vector<point> p;
    for (auto i : myFans) {
        p.push_back(a[i]);
    }
    p = convexHull(p);
    if (!checkCnt(p, p.size())) return false;
    if (ans <= myAns) return true;
    ans = myAns;
    fans = myFans;
    return true;
}

#define app push_back

bool checkCnt(point A, point B, point C) {
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        cnt += PointInTriangle(A, B, C, a[i]);
        if (cnt == k) return true;
    }
    return false;
}

void solve3() {
    if (k < 3) return;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = j + 1; k < n; k++) {
                if (checkCnt(a[i], a[j], a[k])) {
                    relax(get({a[i], a[j], a[k]}), {i, j, k});
                }
            }
        }
    }
}

bool checkCnt(point A, point B, point C, point D) {
    if (!check(A, B, C, D)) return false;
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        cnt += pointInPolygon(A, B, C, D, a[i]);
        if (cnt == k) return true;
    }
    return false;
}

void solve4() {
    if (k < 4) return;
    for (int a1 = 0; a1 < n; a1++) {
        for (int a2 = a1 + 1; a2 < n; a2++) {
            for (int a3 = a2 + 1; a3 < n; a3++) {
                for (int a4 = a3 + 1; a4 < n; a4++) {
                    if (checkCnt(a[a1], a[a2], a[a3], a[a4])) {
                        relax(get({a[a1], a[a2], a[a3], a[a4]}), {a1, a2, a3, a4});
                    }
                }
            }
        }
    }
}

void solve5() {
    if (k < 5) return;
    for (int a1 = 0; a1 < n; a1++) {
        for (int a2 = a1 + 1; a2 < n; a2++) {
            for (int a3 = a2 + 1; a3 < n; a3++) {
                for (int a4 = a3 + 1; a4 < n; a4++) {
                    for (int a5 = a4 + 1; a5 < n; a5++) {
                        if (checkCnt({a[a1], a[a2], a[a3], a[a4], a[a5]}, 5)) {
                            relax(
                                get({a[a1], a[a2], a[a3], a[a4], a[a5]}),
                                 {a1, a2, a3, a4, a5}
                                 );
                        }
                    }
                }
            }
        }
    }
}

void solve6() {
    if (k < 6) return;
    for (int a1 = 0; a1 < n; a1++) {
        for (int a2 = a1 + 1; a2 < n; a2++) {
            for (int a3 = a2 + 1; a3 < n; a3++) {
                for (int a4 = a3 + 1; a4 < n; a4++) {
                    for (int a5 = a4 + 1; a5 < n; a5++) {
                        for (int a6 = a5 + 1; a6 < n; a6++) {
                            if (checkCnt({a[a1], a[a2], a[a3], a[a4], a[a5], a[a6]}, 6)) {
                                relax(
                                    get({a[a1], a[a2], a[a3], a[a4], a[a5], a[a6]}),
                                     {a1, a2, a3, a4, a5, a6}
                                     );
                            }
                        }
                    }
                }
            }
        }
    }
}

void makeAns() {
    vector<point> p;
    for (auto i : fans) {
        p.push_back(a[i]);
    }
    p = convexHull(p);
    set<int> s;
    for (auto i : fans) {
        s.insert(i);
    }
    for (int i = 0; i < n; i++) {
        if (s.count(i)) continue;
        if (check(a[i], p)) {
            fans.push_back(i);
        }
        if (fans.size() == k) break;
    }
    //assert(fans.size() == k);
}

void solve1() {
    cout << 0 << endl;
    cout << 1 << endl;
    exit(0);
}

void solve2() {
    pair<ld, pair<int, int>> ans;
    ans.first = 1e18;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            ans = min(ans, make_pair(dist(a[i], a[j]), make_pair(i, j)));
        }
    }
    cout << ans.first * 2 << endl;
    cout << ans.second.first + 1 << " " << ans.second.second + 1 << endl;
    exit(0);
}

void rec(int i, vector <point> p, vector <int> who) {
    if (convexHull(p).size() != p.size() || Time > 1.99)
        return;

    if (relax(get(p), who)) return;

    if (i == n)
        return;

    rec(i + 1, p, who);
    p.app(a[i]);
    who.app(i);
    rec(i + 1, p, who);
}

signed main() {
    freopen("convexset.in", "r", stdin);
    freopen("convexset.out", "w", stdout);
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cout.precision(20);
    cin >> n >> k;
    assert(k <= n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].x >> a[i].y;
    }
    if (k == 1) {
        solve1();
    }
    if (k == 2) {
        solve2();
    }
    //solve3();
    //solve4();
    //solve5();
    //solve6();
    rec(0, {}, {});
    vector<point> have;
    for (int i = 0; i < n; i++) {
        have.push_back(a[i]);
    }
    vector<int> ind(n);
    iota(all(ind), 0);
    //relax(get(have), ind);
    cout << ans << endl;
    assert(ans < 1e9);
    int sz = fans.size();
    sort(all(fans));
    fans.resize(unique(all(fans)) - fans.begin());
    assert(sz == fans.size());
    makeAns();
    while (fans.size() > k) {
        fans.pop_back();
    }
    assert(fans.size() == k);
    for (auto i : fans) {
        cout << i + 1 << " ";
    }
    cout << endl;
    return 0;
}