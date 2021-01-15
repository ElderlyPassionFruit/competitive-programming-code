#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

int n, m;
vector<vector<int>> g;
vector<pair<int, int>> path;

vector<int> h;
vector<int> par;

void dfs(int v, int p) {
    par[v] = p;
    for (auto i : g[v]) {
        if (i == p) continue;
        h[i] = h[v] + 1;
        dfs(i, v);
    }
}

int lca(int v, int u) {
    if (h[v] > h[u]) swap(u, v);
    while (h[v] < h[u]) {
        u = par[u];
    }
    return v;
}

int dist(int u, int v) {
    return h[u] + h[v] - 2 * h[lca(u, v)];
}

bool check(int a, int b, int x) {
    return dist(a, b) == dist(a, x) + dist(b, x);
}

vector<int> getPath(int v, int u) {
    int l = lca(v, u);
    vector<int> a, b;
    while (v != l) {
        a.push_back(v);
        v = par[v];
    }
    while (u != l) {
        b.push_back(u);
        u = par[u];
    }
    a.push_back(l);
    reverse(all(b));
    for (auto i : b) {
        a.push_back(i);
    }
    return a;
}

bool check(int a, int b, int c, int d) {
    auto A = getPath(a, b);
    auto B = getPath(c, d);
    if (A.size() < B.size()) swap(A, B);
    sort(all(A));
    sort(all(B));
    int cnt = 0;
    for (auto i : B) {
        cnt += binary_search(all(A), i);
        //if (!binary_search(all(A), i)) {
        //    return false;
        //}
    }
    return cnt == 0 && cnt == B.size();
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cout.setf(ios::fixed), cout.precision(20);
    cin >> n >> m;
    g.resize(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    path.resize(m);
    for (auto& [u, v] : path) {
        cin >> u >> v;
        --u;
        --v;
    }
    h.assign(n, 0);
    par.assign(n, -1);
    dfs(0, 0);
    for (auto [a, b] : path) {
        for (auto [c, d] : path) {
            if (check(a, b, c, d)) continue;
            //cout << a << " " << b << " " << c << " " << d << endl;
            cout << "No";
            exit(0);
        }
    }
    cout << "Yes";
    return 0;
}