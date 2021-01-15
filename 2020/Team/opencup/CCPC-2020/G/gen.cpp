#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

#define int ll

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

int get(int l, int r) {
    return rnd() % (r - l + 1) + l;
}

const int INF = 1e18 + 228;

const int N = 10000;
const int A = 65536;

void tryBuild() {
    int n = get(1, N);
    int q = get(1, N);
    cout << n << " " << q << endl;
    for (int i = 0; i < n; ++i) {
        cout << get(1, A - 1) << " ";
    }
    cout << endl;
    while (q--) {
        int t = get(1, 2);
        if (t == 1) {
            int l = get(1, n);
            int r = get(l, n);
            cout << t << " " << l << " " << r << endl;
        } else {
            int x = get(1, n);
            int y = get(1, n);
            int len = get(1, n - max(x, y) + 1);
            cout << t << " " << x << " " << y << " " << len << endl;
        }
    }
    exit(0);
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
    while (true) {
        tryBuild();
    }
    return 0;
}