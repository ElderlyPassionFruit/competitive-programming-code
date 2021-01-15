#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

const int N = 1e5 + 10;
int n, m;
int a[N], b[N];

bool check(int l, int r) {
    int pos = lower_bound(b, b + m, a[l]) - b;
    // cerr << "l = " << l << " r = " << r << " pos = " << pos << " b[pos] = " << b[pos] << " " << a[l] << " " << a[r] << endl;
    if (pos < m && b[pos] <= a[r]) return false;
    pos = upper_bound(b, b + m, a[r]) - b;
    --pos;
    if (pos >= 0 && b[pos] >= a[l]) return false;
    return true;
}

void solve() {
    // int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < m; ++i) {
        cin >> b[i];
    }
    sort(a, a + n);
    sort(b, b + m);
    // cerr << "a = " << endl;
    // for (int i = 0; i < n; ++i) {
    //     cerr << a[i] << " ";
    // }
    // cerr << endl;
    // cerr << "b = " << endl;
    // for (int i = 0; i < m; ++i) {
    //     cerr << b[i] << " ";
    // }
    // cerr << endl;
    
    int ans = 0;
    for (int l = 0; l < n; ++l) {
        if (!check(l, l)) continue;
        int r = l;
        while (r < n && check(l, r)) {
            ++r;
        }
        chkmax(ans, r - l);
        l = r - 1;
    }
    if (ans == 0) {
        cout << "Impossible\n";
    } else {
        cout << ans << '\n';
    }
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