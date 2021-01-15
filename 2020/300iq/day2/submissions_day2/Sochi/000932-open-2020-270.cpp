#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 3000;
const int inf = 1e9;

int dp[N][N];
int best[N];

int main() {
#ifdef iq
    freopen("a.in", "r", stdin);
#endif // iq
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector <int> l(n);
    for (int i = 0; i < n; i++) cin >> l[i];
    for (int i = 0; i < n; i++) l[i]--;
    vector <int> s(n);
    for (int i = 0; i < n; i++) cin >> s[i];
    vector <int> c(n + m);
    for (int i= 0; i < n + m; i++) cin >> c[i];
    vector <int> p(n + m);
    int sm = 0;
    for (int i = 0; i < n + m; i++) {
        sm += c[i];
        p[i] = sm;
    }
    auto f = [&] (int l, int r) {
        return p[r] - p[l - 1];
    };
    for (int i = 0; i < n; i++) best[i] = -inf;
    for (int i= 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            dp[i][j] = -inf;
        }
    }
    for (int i = 0; i < n; i++) {
        int cost = c[l[i]] - s[i];
        dp[i][1] = cost;
        for (int j = 0; j < i; j++) {
            if (l[j] > l[i]) {
                if (l[j] != l[i] + 1)
                    dp[i][1] = max(dp[i][1], best[j] + cost);
                else
                    for (int x = 1; x <= n; x++) {
                        dp[i][x] = max(dp[i][x], dp[j][x - 1] + cost);
                    }
            }
            else if (l[j] == l[i]) {
                dp[i][1] = max(dp[i][1], dp[j][0] + cost);
                for (int x = 1; x < n; x++) {
                    dp[i][0] = max(dp[i][0], dp[j][x] + cost + f(l[i] + 1, l[i] + x));
                }
            }
        }
        for (int x = 0; x <= n; x++) {
            best[i] = max(best[i], dp[i][x]);
        }
    }
    int ans = -inf;
    for (int i = 0; i < n; i++) ans = max(ans, best[i]);
    cout << ans << endl;
}
