#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

#define int ll

struct Edge{
    int to, len;
};

const int LOG = 17;
int n;
vector<vector<Edge>> g;
vector<int> a[3];

vector<int> tin, tout;
int timer = 0;
vector<vector<int>> dp;
vector<int> h;

void dfs(int v, int p) {
    tin[v] = timer++;
    dp[v][0] = p;
    for (int i = 1; i < LOG; ++i) {
        dp[v][i] = dp[dp[v][i - 1]][i - 1];
    }
    for (auto [to, len] : g[v]) {
        if (to == p) continue;
        h[to] = h[v] + len;
        dfs(to, v);
    }
    tout[v] = timer++;
}

void init() {
    tin.assign(n, 0);
    tout.assign(n, 0);
    h.assign(n, 0);
    dp.assign(n, vector<int> (LOG, 0));
    dfs(0, 0);
}

bool isUpper(int v, int u) {
    return tin[v] <= tin[u] && tout[v] >= tout[u];
}

int lca(int v, int u) {
    if (isUpper(v, u)) return v;
    if (isUpper(u, v)) return u;
    for (int i = LOG - 1; i >= 0; --i) {
        if (!isUpper(dp[v][i], u)) {
            v = dp[v][i];
        }
    }    
    return dp[v][0];
}

int dist(int u, int v) {
    return h[u] + h[v] - 2 * h[lca(u, v)];
} 

int get(int a, int b, int c) {
    //cout << "a = " << a << " b = " << b << " c = " << c << endl;
    //cout << dist(a, b) << 
    int sum = dist(a, b) + dist(b, c) + dist(a, c);
    assert(sum % 2 == 0);
    return sum / 2;
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cout.setf(ios::fixed), cout.precision(20);
    cin >> n;
    g.resize(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v, len;
        cin >> u >> v >> len;
        --u;
        --v;
        g[u].push_back({v, len});
        g[v].push_back({u, len});
    }
    
    init();
    //cout << "init : ok" << endl;
    for (int it = 0; it < 3; ++it) {
        int m;
        cin >> m;
        a[it].resize(m);
        for (int i = 0; i < m; ++i) {
            cin >> a[it][i];
            --a[it][i];
        }
    }
    //cout << "read : ok" << endl;
    int sum = 0;
    for (auto x : a[0]) {
        for (auto y : a[1]) {
            for (auto z : a[2]) {
                sum += get(x, y, z);
            }
        }
    }
    //cout << "sum = " << sum << endl;
    cout << (ld) sum / ((ll)a[0].size() * a[1].size() * a[2].size()) << endl;
    return 0;
}