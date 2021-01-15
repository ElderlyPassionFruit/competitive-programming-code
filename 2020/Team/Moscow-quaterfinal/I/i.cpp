#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int L = 1e6 + 200000;
const int N = 1e5 + 10;
int x, y;
int n;
int a[N];

void read() {
    cin >> x >> y;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
}

const int A = 16;
int pref[L];

void init() {
    y -= x;
    for (int i = 0; i < n; ++i) {
        a[i] -= x;
        assert(a[i] >= 0 && a[i] <= y);
    }
    fill(pref, pref + L, 0);
    for (int i = 0; i < n; ++i) {
        ++pref[a[i]];
    }
    for (int i = 1; i < L; ++i) {
        pref[i] += pref[i - 1];
    }
}

int getSum(int l, int r) {
    chkmin(r, y);
    chkmax(l, 0);
    return pref[r] - (l > 0 ? pref[l - 1] : 0);
}

const int INF = 1e9 + 228;
int dp[L][A];
int par[L][A];

int len[5];

void initDp() {
    for (int i = 0; i < 5; ++i) {
        len[i] = (1 << (4 * i)) - 1;
    }
    for (int i = 0; i < L; ++i) {
        for (int j = 0; j < A; ++j) {
            dp[i][j] = INF;
            par[i][j] = -1;
        }
    }
}

void relax(int pos, int cnt, int cost, int fpar) {
    if (dp[pos][cnt] <= cost) return;
    dp[pos][cnt] = cost;
    par[pos][cnt] = fpar;
}

void calcDp() {
    for (int i = y; i >= 0; --i) {
        for (int cnt = 0; cnt < A; ++cnt) {
            for (int g = 0; g <= 4; ++g) {
                if (cnt == 0) {
                    if (i + len[g] + 1 <= y) continue;
                    relax(i, cnt, getSum(i, i + len[g]) * g, g);
                } else {
                    if (i + len[g] + 1 > y) continue;
                    if (dp[i + len[g] + 1][cnt - 1] == INF) continue;
                    relax(i, cnt, getSum(i, i + len[g]) * g + dp[i + len[g] + 1][cnt - 1], g);
                }
            }
        }
    }
}

int ans[A][2];

void makeAns() {

}

void run() {
    init();
    calcDp();
    makeAns();
}

void write() {
    for (int i = 0; i < A; ++i) {
        cout << ans[i][0] << " " << ans[i][1] << '\n';
    }
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