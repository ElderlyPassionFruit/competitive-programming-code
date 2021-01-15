#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int N = 110, S = 1010;
int n, s;
int a[N];

int dp[N];
int par[N];
int ans[N];

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cout.setf(ios::fixed), cout.precision(20);
    cin >> n >> s;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    dp[0] = 0;
    for (int i = 1; i <= n; ++i) {
        dp[i] = -1;
        if (a[i] > s) continue;
        for (int j = 0; j < i; ++j) {
            if (a[i] < a[j]) continue;
            if (dp[j] == -1) continue;
            if (dp[j] + 1 <= dp[i]) continue;
            dp[i] = dp[j] + 1;
            par[i] = j;
        }
    }
    int pos = max_element(dp, dp + n + 1) - dp;
    cout << dp[pos] << "\n";
    while (pos > 0) {
        ans[pos] = 1;
        pos = par[pos];
    }
    for (int i = 1; i <= n; ++i) {
        cout << ans[i] << " ";
    }
    cout << "\n";

    return 0;
}