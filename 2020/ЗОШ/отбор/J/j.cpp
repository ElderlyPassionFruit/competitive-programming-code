#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;

#define all(x) (x).begin(), (x).end()
template <typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;};
template <typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (y > x) x = y;};

struct point{
    int x, y;
    point() {}
    point(int a, int b) {
        x = a, y = b;
    }
};

const ll INF = 1e18;

void solve() {
    int n;
    cin >> n;
    vector<point> a(n);
    for (auto &i : a)
        cin >> i.x >> i.y;
    ll ans = INF;
    for (int mask = 0; mask < (1 << n); mask++) {
        ll min_x = INF, max_x = -INF, min_y = INF, max_y = -INF;
        for (int i = 0; i < n; i++) {
            if ((mask >> i) & 1) {
                chkmin(min_x, a[i].x);
                chkmin(min_y, a[i].y);
                chkmax(max_x, a[i].x);
                chkmax(max_y, a[i].y);
            }
        }
        ll fans = 0;
        if (mask) {
            ll dx = max_x - min_x;
            ll dy = max_y - min_y;
            ll d = max(dx, dy);
            fans += d * d;
        }
        min_x = INF, max_x = -INF, min_y = INF, max_y = -INF;
        for (int i = 0; i < n; i++) {
            if (!((mask >> i) & 1)) {
                chkmin(min_x, a[i].x);
                chkmin(min_y, a[i].y);
                chkmax(max_x, a[i].x);
                chkmax(max_y, a[i].y);
            }
        }
        if (mask != (1 << n) - 1) {
            ll dx = max_x - min_x;
            ll dy = max_y - min_y;
            ll d = max(dx, dy);
            fans += d * d;
        }
        //cout << mask << " " << fans << endl;
        chkmin(ans, fans);
    }
    cout << ans << endl;
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cout.setf(ios::fixed), cout.precision(20);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}