#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

#define int ll

int h, l, h1, h2, l1, l2;

void read() {
    cin >> h >> l >> h1 >> h2 >> l1 >> l2;
}

const ld PI = acos(-1);
ld ans;

void run() {
    ans = 0;
    ans += acos((ld)h / sqrt(l * l + h * h)) / (2 * PI) * 2 * (l1 + l2);
    ans += acos((ld)l / sqrt(l * l + h * h)) / (2 * PI) * 2 * (h1 + h2);
    //ans =  + arccos((ld)l / sqrt(l * l + h * h)) / (2 * PI) * 2 * (h1 + h2)
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