#include <bits/stdc++.h>

using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(a) a.begin(), a.end()

using namespace std;

template<typename T1, typename T2> inline void chkmin(T1& x, const T2& y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1& x, const T2& y) {if (x < y) x = y;}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.setf(ios::fixed), cout.precision(20);
    int q;
    cin >> q;
    multiset<ll> a;
    while (q--) {
        ll x;
        cin >> x;
        if (x < 0) {
            cout << *a.begin() << '\n';
            a.erase(a.begin());
        } else {
            a.insert(x);
        }
    }
    return 0;
}