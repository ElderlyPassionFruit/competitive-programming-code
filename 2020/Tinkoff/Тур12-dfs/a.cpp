#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 1e5 + 10;
vector<int> g[MAXN];
int n, m;
int f;

void read() {
    cin >> n >> m;
    cin >> f;
    f--;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
}

struct ed{
    int u, v;
    ed() {}
    ed(int a, int b) {
        u = a;
        v = b;
        if (u > v) swap(u, v);
    }
};

bool operator<(const ed & a, const ed & b) {
    return tie(a.u, a.v) < tie(b.u, b.v);
}

int tin[MAXN], up[MAXN], timer = 0;
set<ed> bridges;
bool used[MAXN];

void dfs_bridges(int v, int p) {
    tin[v] = timer++;
    up[v] = tin[v];
    used[v] = true;
    for (auto i : g[v]) {
        if (i == p) continue;
        if (used[i]) {
            chkmin(up[v], tin[i]);
        } else {
            dfs_bridges(i, v);
            chkmin(up[v], up[i]);
            if (tin[v] < up[i]) {
                bridges.insert({v, i});
            }
        }
    }
}

int color[MAXN];

void dfs_color(int v, int c) {
    color[v] = c;
    used[v] = true;
    for (auto i : g[v]) {
        if (used[i]) continue;
        if (bridges.count({v, i})) continue;
        dfs_color(i, c);
    }
}

const int MAXLOG = 20;

int tout[MAXN], h[MAXN], dp[MAXN][MAXLOG];

void dfs_lca(int v, int p, int len) {
    tin[v] = timer++;
    dp[v][0] = p;
    for (int i = 1; i < MAXLOG; i++)
        dp[v][i] = dp[dp[v][i - 1]][i - 1];
    h[v] = len++;
    for (auto i : g[v]) {
        if (i != p) {
            dfs_lca(i, v, len);
        }
    }
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

int dist(int v, int u) {
    return h[v] + h[u] - 2 * h[lca(v, u)];
}

void build() {
    dfs_bridges(0, 0);
    for (int i = 0; i < n; i++)
        used[i] = false;
    int c = 0;
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            dfs_color(i, c++);
        }
    }
    for (int i = 0; i < n; i++) {
        g[i].clear();
    }
    for (auto edge : bridges) {
        g[color[edge.u]].push_back(color[edge.v]);
        g[color[edge.v]].push_back(color[edge.u]);
    }
    for (int i = 0; i < c; i++) {
        sort(all(g[i]));
        g[i].resize(unique(all(g[i])) - g[i].begin());
    }
    for (int i = 0; i < c; i++)
        tin[i] = 0;
    timer = 0;
    dfs_lca(color[f], color[f], 0);
}

int get(int u, int v) {
    return dist(lca(color[u], color[v]), color[f]);
}

vector<int> ans;

void run() {
    build();
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        ans.push_back(get(u, v));
    }
}

void write() {
    for (auto i : ans)
        cout << i << "\n";
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    read();
    run();
    write();
    return 0;
}
