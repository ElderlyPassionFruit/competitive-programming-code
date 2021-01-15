#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

const int LOG = 31;
int l, r;

void read() {
    cin >> l >> r;
}

int ans;

int getCnt(int r, int bit) {
    if (r <= 0) return 0;
    /*int ans = 0;
    for (int i = 0; i <= r; ++i) {
        ans += (i >> bit) & 1;
    }*/
    int myAns = ((((r >> bit) - ((r >> bit) & 1) + 1) / 2) << bit) + ((r >> bit) & 1) * ((r & ((1 << bit) - 1)) + 1);
    /*if (myAns != ans) {
        cout << r << " " << bit << " " << ans << " " << myAns << endl;
    }*/
    return myAns;
}

int getCnt(int l, int r, int bit) {
    return getCnt(r, bit) - getCnt(l - 1, bit);
}

void run() {
    ans = 0;
    for (int bit = 0; bit < LOG; ++bit) {
        int len = r - l + 1;
        int cnt = getCnt(l, r, bit);
        if (cnt * 2 <= len) {
            continue;
        } else {
            ans |= 1 << bit;
        }
    }
}

void write() {
    cout << ans << endl;
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
    read();
    run();
    write();
    return 0;
}