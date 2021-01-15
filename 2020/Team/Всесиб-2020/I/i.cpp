#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int N = 2200;
int n, m;
char a[N][N];
int have[N][N];

void buildCost() {
    for (int i = 0; i < n; ++i) {
        int now = 0;
        for (int j = 0; j < m; ++j) {
            if (a[i][j] == '@') {
                now = 0;
            } else if (a[i][j] == 'm') {
                ++now;
            }
            have[i][j] += now;
        }
    }
    for (int i = 0; i < n; ++i) {
        int now = 0;
        for (int j = m - 1; j >= 0; --j) {
            if (a[i][j] == '@') {
                now = 0;
            } else if (a[i][j] == 'm') {
                ++now;
            }
            have[i][j] += now;
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (a[i][j] == 'm') {
                --have[i][j];
            }
        }
    }
}

int color[N][N];

void buildG() {
    int c = 1;
    for (int i = 0; i < n; ++i) {
        ++c;
        for (int j = 0; j < m; ++j) {
            if (a[i][j] == '@') {
                ++c;
            } else {
                color[i][j] = c;
            }
        }
    }
    assert(c < N * N);
}

int dp[N * N];

void djkstra() {
    fill(dp, dp + N * N, -1);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (a[i][j] == 'S') {
                dp[color[i][j]] = have[i][j];
                //break;
            }
        }
    }
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (a[i - 1][j] == '@') continue;
            if (a[i][j] == '@') continue;
            if (dp[color[i - 1][j]] == -1) continue;
            dp[color[i][j]] = max(dp[color[i][j]], dp[color[i - 1][j]] + have[i][j]);
        }
    } 
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> a[i][j];
            have[i][j] = 0;
        }
    }
    buildCost();
    buildG();
	djkstra();
    int ans = -1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (a[i][j] == 'E') {
                ans = max(ans, dp[color[i][j]]);
                //cout << dp[color[i][j]] << "\n";
                //exit(0);
            }
        }
    }
    cout << ans << endl;
    //assert(false);
    return 0;
}