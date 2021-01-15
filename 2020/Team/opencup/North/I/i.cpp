#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

// dp[i][j] -> .........(j = 1)......(i = 1)
// dp[i][j] -> .........(j = 1)...[..(i = 1)..]
// dp[i][j] -> .......[..(j = 1).....(i = 1)..]
// dp[i][j] -> .......[..(j = 1)...].(i = 1)..
// x -> последнюю левую до неё

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

int getPow(int a, int n) {
    int ans = 1;
    for (int i = 0; i < n; ++i) {
        ans = mul(ans, a);
    }
    return ans;
}

const int N = 1e3 + 10;
int n, m;
int mxL[N];
int dp[N][N][2][2];

// 1, 2, 4, 5, 7, 8 -> 6
// 3, 6 -> 2
// 0, 9 -> 2

void calcDp() {
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            dp[i][j] = 0;
        }
    }
    dp[0][0] = 1;
}

int ans;

void makeAns() {

}

void solve() {
    fill(mxL, mxL + n, -1);
    for (int i = 0; i < m; ++i) {
        int l, r;
        cin >> l >> r;
        chkmax(mxL[r], l);
    }
    for (int i = 1; i <= n; ++i) {
        chkmax(mxL[i], mxL[i - 1]);
    }
    calcDp();
    makeAns();
    cout << ans << "\n";
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    while (cin >> n >> m) {
        solve();
    }
	return 0;
}