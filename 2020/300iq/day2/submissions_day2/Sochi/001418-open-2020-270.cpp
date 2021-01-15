#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 5000;
const int inf = 1e9;

int dp[N][N];
int ndp[N][N];
int cnt[N];

int main() {
#ifdef iq
    freopen("a.in", "r", stdin);
#endif // iq
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector <int> l(n);
    for (int i = 0; i < n; i++) cin >> l[n - 1 - i];
    for (int i = 0; i < n; i++) l[i]--;
    for (int i = 0; i < n; i++) cnt[l[i]]++;
    vector <int> s(n);
    for (int i = 0; i < n; i++) cin >> s[n - 1 - i];
    vector <int> c(n + m);
    for (int i= 0; i < n + m; i++) cin >> c[i];
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            dp[i][j] = -inf;
        }
    }
    dp[0][0] = 0;
    int cur = 0;
    int ans = 0;
    for (int x = 0; x < n + m; x++) {
        cur += cnt[x];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= cur; j++) {
                dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);
                if (l[i] == x)
                    dp[i + 1][j + 1] = max(dp[i + 1][j + 1], dp[i][j] - s[i]);
            }
        }
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= cur; j++) {
                dp[i][j] += j * c[x];
            }
        }
        for (int i = 0; i <= n; i++) for (int j = 0; j <= cur; j++) ndp[i][j] = -inf;
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= cur; j++) {
                ndp[i][j / 2] = max(ndp[i][j / 2], dp[i][j]);
            }
        }
        for (int i = 0; i <= n; i++) for (int j = 0; j <= cur; j++) dp[i][j] = ndp[i][j];
        cur /= 2;
    }
    cout << dp[n][0] << endl;
}
