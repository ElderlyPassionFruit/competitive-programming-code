#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int N = 2e5 + 10, LOG = 20;
int n;
vector<int> g[N];

int dp[N][LOG], h[N];

void dfs(int v, int p) {
    dp[v][0] = p;
    for (int i = 1; i < LOG; ++i) {
        dp[v][i] = dp[dp[v][i - 1]][i - 1];
    }
    for (auto i : g[v]) {
        if (i == p) continue;
        h[i] = h[v] + 1;
        dfs(i, v);
    }
}

int jump(int v, int len) {
    for (int i = LOG - 1; i >= 0; --i) {
        if ((1 << i) <= len) {
            len -= (1 << i);
            v = dp[v][i];
        }
    }
    return v;
}

int lca(int u, int v) {
    if (h[u] < h[v]) swap(u, v);
    u = jump(u, h[u] - h[v]);
    if (u == v) return v;
    for (int i = LOG - 1; i >= 0; --i) {
        if (dp[u][i] != dp[v][i]) {
            u = dp[u][i];
            v = dp[v][i];
        }
    }
    return dp[v][0];
}

int solve(int u, int v) {
    int l = lca(u, v);
    if (l != u) {
        return jump(u, 1);
    }
    return jump(v, h[v] - h[u] - 1);
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    freopen("treefirstedge.in", "r", stdin);
    freopen("treefirstedge.out", "w", stdout);
    cin >> n;
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(0, 0);
    int q;
    cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        cout << solve(u, v) + 1 << "\n";
    }
	return 0;
}