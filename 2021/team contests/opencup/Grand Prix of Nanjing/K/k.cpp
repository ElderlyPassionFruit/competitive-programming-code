#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

int n, k;

void read() {
    cin >> n >> k;
}

void run() {

}

void write() {
    if (k == 0) {
        cout << "-1\n";
    } else {
        for (int i = 0; i < k; ++i) {
            cout << (i + 1) % k + 1 << ' ';
        }
        for (int i = k; i < n; ++i) {
            cout << i + 1 << ' ';
        }
        cout << '\n';
    }
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
    read();
    run();
    write();
    return 0;
}