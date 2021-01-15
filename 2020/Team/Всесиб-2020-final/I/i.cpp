#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int N = 11;
const int SUM = 10 * 20;

ld dp[N][SUM];

void clear() {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < SUM; ++j) {
            dp[i][j] = 0;
        }
    }
}

ld solve(int D) {
    int n, f, m;
    cin >> n >> f >> m;
    D -= m;
    clear();
    dp[0][0] = 1;
    for (int i = 0; i < n; ++i) {
        for (int sum = 0; sum < n * f; ++sum) {
            for (int val = 1; val <= f && sum + val <= n * f; ++val) {
                dp[i + 1][sum + val] += dp[i][sum] / f;
            }
        }
    }
    ld ans = 0;
    for (int sum = 0; sum < SUM; ++sum) {
        if (sum >= D) {
            ans += dp[n][sum];
        }
    }
    return ans;
}

void solve() {
    int myT, D;
    cin >> myT >> D;
    ld ans = 0;
    while (myT--) {
        ld fans = solve(D);
        if (fans > ans) {
            ans = fans;
        }
    }
    cout << ans << "\n";
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.setf(ios::fixed);
    cout.precision(20);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
	return 0;
}