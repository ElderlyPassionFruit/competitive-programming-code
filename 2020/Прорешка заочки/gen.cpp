#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

mt19937 rnd(time(0));

int get(int l, int r) {
    return rnd() % (r - l + 1) + l;
}

void read() {
    cout << 500 << " " << 500 << endl;
    for (int i = 0; i < 500; ++i) {
        cout << get(1, 1e6) << " " << get(1, 1e6) << endl;
    }
    for (int i = 0; i < 500; ++i) {
        cout << get(1, 1e6) << " " << get(1, 1e6) << " " << get(1, 500) << endl;
    }
}

void run() {

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