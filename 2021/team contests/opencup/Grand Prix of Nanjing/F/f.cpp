#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

void solve() {
    int n, m, p;
    cin >> n >> m >> p;
    // ld ans;
    // ld P = (ld)p / 10000;
    // ld steps = (P / (P - 1)) * (P / (P - 1));
    // cout << "steps = " << steps << endl;
    // ld steps = 10000.0 / p;
    ld steps = 0;
    ld myP = 1;
    for (int i = 1; i < 10000000; ++i) {
        steps += myP * p / 10000.0 * i;
        myP *= (1 - p / 10000.0);
        // cerr << "steps = " << steps << " myP = " << myP << endl;
    }
    cerr << "steps = " << steps << endl;
    ld ans = steps * n + m;
    cout << ans << '\n';
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

// 1/2 * 1 + 1/4 * 2 + 1/8 * 3 + 1/16 * 4 + 1/32 * 5 ... 

// n = 1, m = 1, p = 5000/10000 = 1/2
// 
// 
// 
// 
// 
// 
