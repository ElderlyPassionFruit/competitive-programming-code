#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

const int B = 10;
const int DpMOD = 2 * 2 * 2 * 3 * 3 * 5 * 7;
const int MOD = 999'999'001;

int add(int a, int b) {
    a += b;
    if (a >= MOD) return a - MOD;
    return a;
}

int b, n;

void read() {
    cin >> b >> n;
}

int dp[2][1 << B][DpMOD];
int ans[1 << B];

void mySwap() {
    for (int i = 0; i < (1 << b); ++i) {
        for (int j = 0; j < DpMOD; ++j) {
            dp[0][i][j] = dp[1][i][j];
            dp[1][i][j] = 0;
        }
    }
}

const int LEN = 100;
int pows[LEN];

void build() {
    pows[0] = 1;
    for (int i = 1; i < LEN; ++i) {
        pows[i] = pows[i - 1] * b % DpMOD;
    }
}

string getMask(int mask) {
    string ans = "";
    for (int i = 0; i < b; ++i) {
        ans += '0' + ((mask >> i) & 1);
    }
    return ans;
}

void calcDp() {
    dp[0][0][0] = 1;
    for (int len = 0; len < n; ++len) {
        for (int mask = 0; mask < (1 << b); ++mask) {
            for (int mod = 0; mod < DpMOD; ++mod) {
                if (dp[0][mask][mod] == 0) continue;
                for (int bit = 1; bit < b; ++bit) {
                    int nxtMask = mask | (1 << bit);
                    int nxtMod = (mod + bit * pows[len]) % DpMOD;
                    assert(nxtMask >= 0 && nxtMask < (1 << b));
                    assert(nxtMod >= 0 && nxtMod < DpMOD);
                    dp[1][nxtMask][nxtMod] = add(dp[1][nxtMask][nxtMod], dp[0][mask][mod]); 
                }
            }
        }
        mySwap();
    }
}

int lcm(int a, int b) {
    return a * b / __gcd(a, b);
}

void makeAns() {
    for (int mask = 1; mask < (1 << b); ++mask) {
        int myMod = 1;
        for (int bit = 1; bit < b; ++bit) {
            if ((mask >> bit) & 1) {
                myMod = lcm(myMod, bit);
            }
        }
        for (int mod = 0; mod < DpMOD; ++mod) {
            if (mod % myMod == 0) {
                ans[mask] = add(ans[mask], dp[0][mask][mod]);
            }
        }
    }
    for (int mask = (1 << b) - 1; mask >= 0; --mask) {
        for (int submask = (mask - 1) & mask; ; submask = (submask - 1) & mask) {
            ans[mask] = add(ans[mask], ans[submask]);
            if (submask == 0) break;
        }
    }
}

void run() {
    build();
    calcDp();
    makeAns();
}

void write() {
    int t;
    cin >> t;
    for (int i = 0; i < t; ++i) {
        string s;
        cin >> s;
        int mask = 0;
        for (int bit = 0; bit < b; ++bit) {
            mask |= (1 << bit) * (s[bit] - '0');
        } 
        cout << ans[mask] << '\n';
    }
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
    read();
    run();
    write();
    return 0;
}