#include <bits/stdc++.h>

using namespace std;
#define int long long
#define double long double
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int INF = 1e18;
const int MAXN = 2e5 + 228;
int dp[MAXN];
int ans;

struct line{
    int k, b;
    line() {
        k = 0;
        b = INF;
    }
    line(int x, int y) {
        k = x;
        b = y;
    }
};

double cross(line l, line m) {
    return (double)(l.b - m.b) / (m.k - l.k);
}

int eval(line l, int x) {
    return l.k * x + l.b;
}

struct cht{
    vector<line> l;
    vector<double> p;

    cht() {
        l = {};
        p = {};
    }

    void add(line x) {
        while (!p.empty() && p.back() >= cross(l.back(), x))
            l.pop_back(), p.pop_back();
        l.push_back(x);
        if (l.size() >= 2) {
            p.push_back(cross(l[l.size() - 1], l[l.size() - 2]));
        }
    }

    int get(int x) {
        int pos = lower_bound(p.begin(), p.end(), x) - p.begin();
        return eval(l[pos], x);
    }
};

struct rect{
    int x, y;
    rect() {}
};

bool operator<(rect a, rect b) {
    return tie(a.x, a.y) < tie(b.x, b.y);
}

int n;
vector<rect> a;

void read() {
    cin >> n;
    a.resize(n);
    for (auto &i : a)
        cin >> i.x >> i.y;
}

void run() {
    sort(a.begin(), a.end());
    vector<rect> help;
    help.push_back(a[0]);
    for (int i = 1; i < n; i++) {
        while (!help.empty() && a[i].y >= help.back().y)
            help.pop_back();
        help.push_back(a[i]);
    }
    a = help;
    n = a.size();
    cht hull;

    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        hull.add(line(a[i - 1].y, dp[i - 1]));
        dp[i] = hull.get(a[i - 1].x);
    }
    ans = dp[n];
}

void write() {
    cout << ans << endl;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    read();
    run();
    write();
    return 0;
}
