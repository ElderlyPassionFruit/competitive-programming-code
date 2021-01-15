#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 3000;
const int inf = 1e9;

int dp[N][N];
int best[N];

int cur[N];

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
    for (int i = 0; i < m; i++) best[i] = -inf;
    for (int i= 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            dp[i][j] = -inf;
        }
    }
    for (int i = 0; i < n; i++) {
        int cost = c[l[i]] - s[i];
        for (int i = 0; i <= n; i++) cur[i] = -inf;
        cur[1] = cost;
        for (int x = l[i] + 2; x < m; x++) {
            cur[1] = max(cur[1], best[x] + cost);
        }
        for (int x = 1; x <= n; x++) {
            cur[x] = max(cur[x], dp[l[i] + 1][x - 1] + cost);
        }
        cur[1] = max(cur[1], dp[l[i]][0] + cost);
        for (int x = 1; x < n; x++) {
            cur[0] = max(cur[0], dp[l[i]][x] + cost + f(l[i] + 1, l[i] + x));
        }
        for (int x = 0; x <= n; x++) {
            dp[l[i]][x] = max(dp[l[i]][x], cur[x]);
        }
        for (int x = 0; x <= n; x++) {
            best[l[i]] = max(best[l[i]], cur[x]);
        }
    }
    int ans = 0;
    for (int i = 0; i < m; i++) ans = max(ans, best[i]);
    cout << ans << endl;
}
