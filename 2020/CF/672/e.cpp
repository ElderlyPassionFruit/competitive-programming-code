#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

const int N = 81;
const int M = N * N / 2;
int n;
int myN;
int a[N];
int fullSum;

void read() {
    cin >> n;
    fullSum = 0;
    myN = 0;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        fullSum += x == 0;
        if (x == 1) {
            a[myN++] = fullSum;
        } 
    }
    a[myN++] = fullSum;
}

const int INF = 1e9 + 228;
int dp[2][N][M];

void Swap() {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            dp[0][i][j] = dp[1][i][j];
            dp[1][i][j] = INF;
        }
    }
}

int sq(int x) {
    return x * x;
}

void calcDp() {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            dp[0][i][j] = dp[1][i][j] = INF;
        }
    } 
    dp[0][0][0] = 0;
    for (int i = 0; i < myN; ++i) {
        for (int sum = 0; sum <= fullSum; ++sum) {
            for (int op = abs(sum - a[i]); op <= fullSum * myN; ++op) {
                for (int now = 0; now <= sum; ++now) {
                    chkmin(dp[1][sum][op], dp[0][sum - now][op - abs(sum - a[i])] + sq(now));
                }
            }
        }
        Swap();
    } 
}

int ans[M];

void makeAns() {
    fill(ans, ans + M, INF);
    for (int op = 0; op <= n * (n + 1) / 2; ++op) {
        ans[op] = dp[0][fullSum][op];
        if (op > 0) {
            chkmin(ans[op], ans[op - 1]);
        }
    }
}

void run() {
    calcDp();
    makeAns();
}

void write() {
    for (int i = 0; i <= n * (n - 1) / 2; ++i) {
        cout << (sq(fullSum) - ans[i]) / 2 << " ";
    }
    cout << "\n";
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
    read();
    run();
    write();
    return 0;
}
