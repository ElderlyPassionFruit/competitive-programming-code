#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

const int MOD = 1e9 + 7;

void add(int &a, int b) {
    a += b;
    if (a >= MOD) a -= MOD;
}

int n;

void read() {
    cin >> n;
}

const int N = 1e6 + 10;
int dp[N][2][2];

void run() {
    dp[0][0][0] = 1;
    for (int i = 0; i < n; i++) {
        for (int flag0 = 0; flag0 <= 1; flag0++) {
            for (int flag1 = 0; flag1 <= 1; flag1++) {
                for (int nxtVal = 0; nxtVal <= 9; nxtVal++) {
                    add(dp[i + 1][flag0 | (nxtVal == 0)][flag1 | (nxtVal == 9)], dp[i][flag0][flag1]);
                }
            }
        }
    }
}

void write() {
    cout << dp[n][1][1] << endl;
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
    read();
    run();
    write();
    return 0;
}