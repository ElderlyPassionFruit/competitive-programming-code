#include <bits/stdc++.h>

using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(a) a.begin(), a.end()

using namespace std;

template<typename T1, typename T2> inline void chkmin(T1& x, const T2& y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1& x, const T2& y) {if (x < y) x = y;}

mt19937 rnd(time(0));

int query(int x, int y) {
    cout << x << " " << y << endl;
    int ans;
    cin >> ans;
    return ans;
}

void outAns(int x, int y) {
    cout << "A " << x << " " << y << endl;
    exit(0);
}

const int B = 1000000001;

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.setf(ios::fixed), cout.precision(20);
    int x = (rnd() % B + B) % B;
    int ly = 0, ry = B - 1;
    while (ly < ry - 2) {
        int midL = ly + (ry - ly) / 3;
        int midR = ry - (ry - ly) / 3;
        query(x, midL);
        if (query(x, midR)) {
            ly = midL;
        } else {
            ry = midR;
        }
    }
    int y = ly;
    for (int i = ly + 1; i <= ry; ++i) {
        query(x, y);
        if (query(x, i)) {
            y = i;
        }
    }
    int lx = 0, rx = B - 1;
    while (lx < rx - 2) {
        int midL = lx + (rx - lx) / 3;
        int midR = rx - (rx - lx) / 3;
        query(midL, y);
        if (query(midR, y)) {
            lx = midL;
        } else {
            rx = midR;
        }
    }
    x = lx;
    for (int i = lx + 1; i <= rx; ++i) {
        query(x, y);
        if (query(i, y)) {
            x = i;
        }
    }
    outAns(x, y);
    return 0;
}