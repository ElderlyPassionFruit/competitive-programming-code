#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n, m, k;
vector<vector<int>> a;

void read() {
    cin >> n >> m >> k;
    a.resize(n);
    for (auto &i : a) {
        i.resize(3);
        for (auto &j : i) {
            cin >> j;
        }
    }
}

int get(int mask) {
    if (__builtin_popcount(mask) != m) return 1e9;
    int cnt1 = 0, cnt2 = 0, ans = 0;
    for (int i = 0; i < n; i++) {
        if ((mask >> i) & 1) {
            ans += a[i][0];
            cnt1 += a[i][1];
            cnt2 += a[i][2];
        }
    }
    if (min(cnt1, cnt2) < k) return 1e9;
    return ans;
}

int ans;

void run() {
    ans = 1e9;
    for (int mask = 0; mask < (1 << n); mask++) {
        chkmin(ans, get(mask));
    }
    if (ans == 1e9) {
        ans = -1;
    }
}

void write() {
    cout << ans << endl;
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