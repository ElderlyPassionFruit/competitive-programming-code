#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

const int MOD = 1e9 + 7;

int add(int a, int b) {
    a += b;
    if (a >= MOD) return a - MOD;
    return a;
}

int sub(int a, int b) {
    a -= b;
    if (a < 0) return a + MOD;
    return a;
}

int mul(int a, int b) {
    return (ll) a * b % MOD;
}

int binpow(int a, int n) {
    int ans = 1;
    while (n) {
        if (n & 1) {
            ans = mul(ans, a);
        }
        a = mul(a, a);
        n >>= 1;
    }
    return ans;
}

int getInv(int a) {
    return binpow(a, MOD - 2);
}

const int N = 10;
int n;
int a[N];

void read() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
}

int dp[N][N];
int len;
int x[N];
int have[N];

int getPos(int x) {
    return lower_bound(have, have + len, x) - have;
}

int calc() {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            dp[i][j] = 0;
        }
    }
    for (int i = 0; i < len; ++i) {
        have[i] = x[i];
    }
    sort(have, have + len);
    dp[0][0] = 1;
    for (int i = 1; i <= len; ++i) {
        int now = x[i - 1];
        int posNow = getPos(now) + 1;
        for (int prevPos = 0; prevPos < )
    }
}

int calc(int mask) {
    len = 0;
    for (int i = 0; i < n; ++i) {
        if ((mask >> i) & 1) {
            x[len++] = a[i]; 
        }
    }    
    return calc();
}

int getLen(int mask) {
    return __builtin_popcount(mask);
}

int ans;

void run() {
    int sumLen = 0;
    int sumCnt = 0;
    for (int mask = 1; mask < (1 << n); ++mask) {
        int cnt = calc(mask);
        sumLen = add(sumLen, mul(cnt, getLen(mask)));
        sumCnt = add(sumCnt, cnt);
    }
    ans = mul(sumLen, getInv(sumCnt));
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