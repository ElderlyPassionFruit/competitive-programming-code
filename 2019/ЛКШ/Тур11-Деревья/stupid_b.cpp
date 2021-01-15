#include <bits/stdc++.h>

using namespace std;
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 1e5 + 10, MAXLOG = 20;
int n;
vector<int> g[MAXN];
int dp[MAXN][MAXLOG], tin[MAXN], tout[MAXN], h[MAXN];
int timer = 0;

void dfs_lca(int v, int p, int len) {
    tin[v] = timer++;
    h[v] = len++;
    dp[v][0] = p;
    for (int i = 1; i < MAXLOG; i++)
        dp[v][i] = dp[dp[v][i - 1]][i - 1];
    for (auto i : g[v])
        if (i != p)
            dfs_lca(i, v, len);
    tout[v] = timer++;
}

bool is_upper(int v, int u) {
    return tin[v] <= tin[u] && tout[v] >= tout[u];
}

int lca(int v, int u) {
    if (is_upper(v, u)) return v;
    if (is_upper(u, v)) return u;
    for (int i = MAXLOG - 1; i >= 0; i--)
        if (!is_upper(dp[v][i], u))
            v = dp[v][i];
    return dp[v][0];
}

int col[MAXN];

int get_max(int v, int u) {
    int l = lca(v, u);
    int ans = 0;
    while (v != l) {
        chkmax(ans, col[v]);
        v = dp[v][0];
    }
    while (u != l) {
        chkmax(ans, col[u]);
        u = dp[u][0];
    }
    chkmax(ans, col[l]);
    return ans;
}

int root = 0;

void read() {
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> col[i];
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
}

vector<bool> ans;
void run() {
    dfs_lca(root, root, 0);
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int type;
        cin >> type;
        if (type == 2) {
            int u, v;
            cin >> u >> v;
            u--;
            v--;
            cout << get_max(u, v) << "\n";
        }    
        else {
            int pos, val;
            cin >> pos >> val;
            pos--;
            col[pos] = val;
        }
    }
}

void write() {
    for (auto i : ans)
        cout << i << "\n";
}

signed main() {
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    read();
    run();
    write();
    return 0;
}