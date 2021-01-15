#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

string s;

void read() {
    cin >> s;
}

void solve() {
    int l1, r1, l2, r2;
    cin >> l1 >> r1 >> l2 >> r2;
    auto a = s.substr(l1, r1 - l1 + 1);
    auto b = s.substr(l2, r2 - l2 + 1);
    if (a > b) {
        cout << "1\n";
    } else if (a < b) {
        cout << "-1\n";
    } else {
        cout << "0\n";
    }
}

void run() {
    int q;
    cin >> q;
    while (q--) {
        solve();
    }
}

void write() {

}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
    read();
    run();
    write();
    return 0;
}