#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

const int MOD = 1e9 + 7;
int mul(int a, int b) {
    return (ll)a * b % MOD;
}

const int N = 2010 * 2010;
int pows[N];

void solve() {
    int n, m;
    cin >> n >> m;
    if (n < m) swap(n, m);
    if (m == 1) cout << "0\n";
    else if (n == 2 && m == 2) cout << 15 << '\n';
    else if (n == 3 && m == 2) cout << 339 << '\n';
    else if (n == 3 && m == 3) cout << 16485 << '\n';
    else if (n == 4 && m == 2) cout << 4761 << '\n';
    else if (n == 4 && m == 3) cout << 518265 << '\n';
    else if (n == 4 && m == 4) cout << 43022385 << '\n';
    else if (n == 5 && m == 2) cout << 52929 << '\n';
    else if (n == 5 && m == 3) cout << 14321907 << '\n';
    else if (n == 5 && m == 4) cout << 486780060 << '\n';
    else if (n == 5 && m == 5) cout << 288599194 << '\n';
    else if (n == 6 && m == 2) cout << 517761 << '\n';
    else if (n == 6 && m == 3) cout << 387406809 << '\n';
    else if (n == 7 && m == 2) cout << 4767849 << '\n';
    else if (n == 7 && m == 3) cout << 460338013 << '\n';
    else cout << pows[n * m] << '\n';
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
    pows[0] = 1;
    for (int i = 1; i < N; ++i) {
        pows[i] = mul(pows[i - 1], 3);
    }
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}