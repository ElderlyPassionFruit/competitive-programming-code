#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

int n, m, k;
vector<vector<int>> g;

vector<int> order;
vector<bool> used;

void dfs(int v) {
    used[v] = true;
    for (auto i : g[v]) {
        if (used[i]) continue;
        dfs(i);
    }
    order.push_back(v);
}

vector<int> dist;

void bfs(int v) {
    dist[v] = 0;
    queue<int> q;
    q.push(v);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (auto i : g[v]) {
            if (dist[i] <= dist[v] + 1) continue;
            dist[i] = dist[v] + 1;
            q.push(i);
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cout.setf(ios::fixed), cout.precision(20);
    cin >> n >> m >> k;
    g.resize(n);
    vector<pair<int, int>> ed;
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        ed.push_back({u, v});
        g[u].push_back(v);
    }
    used.assign(n, 0);
    for (int i = 0; i < n; ++i) {
        if (used[i]) continue;
        dfs(i);
    }
    g.assign(n, {});
    for (auto [u, v] : ed) {
        g[v].push_back(u);
    }
    dist.assign(n, k + 1);
    //reverse(all(order));
    for (auto i : order) {
        if (dist[i] == k + 1) {
            bfs(i);
        }
    }
    if (!dist[0]) {
        cout << "Denis\n";
    } else {
        cout << "Dasha\n";
    }
    return 0;
}