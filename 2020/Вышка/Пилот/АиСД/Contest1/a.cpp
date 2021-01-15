#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

const int N = 1e3 + 10;
int n, l;
int a[N][2];

void read() {
    cin >> n >> l;
    for (int i = 0; i < n; ++i) {
        cin >> a[i][0] >> a[i][1];
    }
}

int ans1, ans2;

void run() {
    ans1 = ans2 = 0;
    for (int i = 0; i < n; ++i) {
        int add = 2;
        if (a[i][1] > l) {
            ++add;
        } else if (a[i][1] == -1) {
            --add;
        }
        if (a[i][0] == 1) {
            ans1 += add;
        } else {
            ans2 += add;
        }
    }
}

void write() {
    cout << ans1 << ":" << ans2 << endl;
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
    read();
    run();
    write();
    return 0;
}