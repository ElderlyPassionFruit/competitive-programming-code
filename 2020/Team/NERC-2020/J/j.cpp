#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const ld EPS = 1e-9;

int sign(ld x) {
    if (x < -EPS) return -1;
    if (x > EPS) return 1;
    return 0;
}

struct Point{
    ld x, y;
    Point() {}
    Point(ld _x, ld _y) {
        x = _x, y = _y;
    }
};

#define Vec Point

Point operator-(const Point& a, const Point& b) {
    return Point(a.x - b.x, a.y - b.y);
}

ld operator^(const Point& a, const Point& b) {
    return a.x * b.y - a.y * b.x;
}

struct Line{
    ld a, b, c;
    Line() {}
    Line(Point x, Point y) {
        a = y.y - x.y;
        b = x.x - y.x;
        c = x.y * y.x - x.x * y.y;
    }
};

const ld INF = 1e9 + 228;
const int N = 51;
const int L = 110;
int n, len;
int d[N], h[N];
Point p[2 * N];

ld dp[2 * N][2 * N];

ld sq(ld x) {
    return x * x;
}

ld dist(const Point& a, const Point& b) {
    return sqrt(sq(a.x - b.x) + sq(a.y - b.y));
}

ld calc1(int i, int j) {
    int l = i / 2;
    int r = j / 2;
    Vec v1 = p[r] - p[l];

    for (int x = l + 1; x < r; ++x) {
        Vec v2 = p[x * 2] - p[l];
        if (sign(v1 ^ v2) == -1) {
            return INF;
        }
    }
    ld ans = dist(p[l], p[r]);
    if (sign(ans - l) == 1) {
        ans = INF;
    }
    return ans;
}

pair<ld, ld> getSegL(int l, int x, Vec v) {
    ld L = (x > 0 ? d[x - 1] : 0);
    ld R = d[x];

    for (int it = 0; it < 80; ++it) {
        ld mid = (L + R) / 2;

    }
}

pair<ld, ld> getSegR(int r, int x, Vec v) {

}

ld calc2(int i, int j) {

}

inline void chkmin(ld &x, ld y) {
    if (y < x) {
        x = y;
    }
}

ld calc3(int i, int j) {
    int l = i / 2;
    int r = j / 2;
    ld ans = INF;
    for (int x = l + 1; x < r; ++x) {
        if (h[x] >= min(h[l], h[r])) {
            return INF;
        }
        Vec v1 = p[x * 2] - p[i];
        for (int k = l + 1; k < x; ++k) {
            Vec have = p[k * 2 + 1] - p[i];
            if (sign(v1 ^ have) == 1) {
                v1 = have;
            }
        }
        Vec v2 = p[x * 2 + 1] - p[j];
        for (int k = x + 1; x < r; ++k) {
            Vec have = p[k * 2] - p[j];
            if (sign(v2 ^ have) == -1) {
                v2 = have;
            }
        }
        auto segL = getSegL(l, x, v1);
        auto segR = getSegR(r, x, v2);
        if (sign(dist({segL.first, h[x]}, p[i]) - len) == 1) continue;
        if (sign(dist({segR.second, h[x]}, p[j]) - len) == 1) continue;
        chkmin(ans, dist({segL.first, h[x]}, p[i]) + dist({segR.first, h[x]}, p[j]) + abs(segL.first - segR.first));
        chkmin(ans, dist({segL.first, h[x]}, p[i]) + dist({segR.second, h[x]}, p[j]) + abs(segL.first - segR.second));
        chkmin(ans, dist({segL.second, h[x]}, p[i]) + dist({segR.first, h[x]}, p[j]) + abs(segL.second - segR.first));
        chkmin(ans, dist({segL.second, h[x]}, p[i]) + dist({segR.second, h[x]}, p[j]) + abs(segL.second - segR.second));  
    }
    return ans;
}

void buildGraph() {
    for (int i = 0; i < n; ++i) {
        p[i * 2] = Point(i > 0 ? d[i - 1] : 0, h[i]);
        p[i * 2 + 1] = Point(d[i], h[i]);
    }
    for (int i = 0; i < 2 * N; ++i) {
        for (int j = 0; j < 2 * N; ++j) {
            dp[i][j] = INF;
        }
        dp[i][i] = 0;
    }
    for (int i = 0; i < n; ++i) {
        dp[2 * i][2 * i + 1] = dp[2 * i + 1][2 * i] = d[i] - (i > 0 ? d[i - 1] : 0);
    }
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            ld val;
            for (int it1 = 0; it1 <= 1; ++it1) {
                for (int it2 = 0; it2 <= 1; ++it2) {
                    val = calc1(i * 2, j * 2);
                    chkmin(dp[i * 2 + it1][j * 2 + it2], val);
                    chkmin(dp[j * 2 + it2][i * 2 + it1], val);    
                }
            }
            val = min(calc2(i * 2 + 1, j * 2), calc3(i * 2 + 1, j * 2));
            chkmin(dp[i * 2 + 1][j * 2], val);
            chkmin(dp[j * 2][i * 2 + 1], val);
        }
    }
}

ld ans;

void floyd() {
    for (int k = 0; k < 2 * n; ++k) {
        for (int i = 0; i < 2 * n; ++i) {
            for (int j = 0; j < 2 * n; ++j) {
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
            }
        }
    }
    if (dp[0][2 * n - 1] > INF / 2) {
        cout << "-1\n";
        exit(0);
    }
    ans = dp[0][2 * n - 1];
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    cin >> n >> len;
    for (int i = 0; i < n; ++i) {
        cin >> d[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> h[i];
    }
    buildGraph();
    floyd();
    cout << ans << '\n';
	return 0;
}