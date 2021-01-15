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

const int N = 2010;
int dp[N];

void run() {
    dp[0] = 1;
    for (int sum = 1; sum <= n; ++sum) {
        for (int val = 3; val <= sum; ++val) {
            add(dp[sum], dp[sum - val]);
        }
    }
}

void write() {
    cout << dp[n] << endl;
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
    read();
    run();
    write();
    return 0;
}