#include <bits/stdc++.h>

using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(a) a.begin(), a.end()

using namespace std;

template<typename T1, typename T2> inline void chkmin(T1& x, const T2& y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1& x, const T2& y) {if (x < y) x = y;}

const int N = 2e5 + 10;
int a[2 * N];
int topA = 0;

int n, k;

void relax() {
    nth_element(a, a + k, a + 2 * k);
    topA = k;
}

void relax(int x) {
    a[topA++] = -x;
    if (topA == 2 * k) {
        relax();
    }
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.setf(ios::fixed), cout.precision(20);
    cin >> n >> k;
    int x1, x2, A, B, C;
    cin >> x1 >> x2 >> A >> B >> C;
    for (int i = 1; i <= n; ++i) {
        int xn = ((ll)x1 * A + (ll)x2 * B + C) & ((1LL << 31) - 1);
        relax(xn);
        x1 = x2;
        x2 = xn;    
    }
    relax();
    sort(a, a + k);
    for (int i = 0; i < k; ++i) {
        cout << -a[i] << ' ';
    }
    cout << '\n';
    return 0;
}