#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int N = 1010;
int n, m, k;
ll a[N][N];

void read() {
    cin >> n >> m >> k;
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> a[i][j];
            if (j > 0) {
                a[i][j] += a[i][j - 1];
            }
        }
    }
}

ll ans[N];

ll now[N];

void run() {
    for (int j = 0; j < n; ++j) {
        for (int i = 0; i < k; ++i) {
            now[i] = a[i][j];
        }
        nth_element(now, now + k / 2, now + k);
        ans[j] = now[k / 2];
    }
    for (int i = n - 1; i > 0; --i) {
        ans[i] -= ans[i - 1];
    }
}

void write() {
    for (int i = 0; i < n; ++i) {
        cout << ans[i] << ' ';
    }
    cout << endl;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    read();
    run();
    write();
    return 0;
}