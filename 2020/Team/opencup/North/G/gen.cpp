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

const int C = 100000000;

void tryBuild() {
    int test = 10;
    for (int i = 0; i < test; ++i) {
        int n = 200000;
        int m = 200000;
        cout << n << " " << m << '\n';
        cout << -C << " " << -C << '\n';
        for (int i = 0; i < n / 2 - 2; ++i) {
            cout << -C << " " << -C + i + 1 << '\n';
        }
        cout << -C << " " << C << '\n';
        
        cout << C << " " << C << '\n';
        for (int i = n / 2 - 3; i >= 0; --i) {
            cout << C << " " << -C + i + 1 << '\n';
        }
        cout << C << " " << -C << '\n';
        for (int i = 0; i < m; ++i) {
            cout << get(-C + 1, C - 1) << " " << get(-C + 1, C - 1) << '\n';
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