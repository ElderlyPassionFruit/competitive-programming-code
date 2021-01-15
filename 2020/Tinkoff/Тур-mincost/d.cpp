#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
#define int ll

struct edge{
    int to, cap, flow, cost;
    edge() {}
    edge(int _to, int _cap, int _cost) {
        to = _to, cap = _cap, cost = _cost, flow = 0;
    }
    int get_cap() {
        return cap - flow;
    }
};

struct min_cost_max_flow{
    vector<edge> Edge;
    vector<vector<int>> g;
    int s, f;
    int n;

    min_cost_max_flow() {}

    min_cost_max_flow(int _n, int _s, int _f) {
        n = _n, s = _s, f = _f;
        g.assign(n, {});
        Edge.clear();
    }

    void add_edge(int v, int u, int cap, int cost) {
        g[v].push_back(Edge.size());
        Edge.push_back({u, cap, cost});
        g[u].push_back(Edge.size());
        Edge.push_back({v, 0, -cost});
    }

    const int INF = 1e18;

    vector<int> d;
    vector<bool> used;
    vector<int> par;
    vector<int> P;

    void rebuild() {
        set<pair<int, int>> q;
        d.assign(n, INF);
        d[s] = 0;
        q.insert({0, s});

        while (!q.empty()) {
            int v = (*q.begin()).second;
            q.erase(q.begin());
            for (auto i : g[v]) {
                if (Edge[i].get_cap() < 1) continue;
                int cost = d[v] + Edge[i].cost + P[v] - P[Edge[i].to];
                int to = Edge[i].to;
                if (d[to] <= cost) continue;
                q.erase({d[to], to});
                d[to] = cost;
                q.insert({d[to], to});
            }
        }
        for (int i = 0; i < n; i++)
            P[i] += d[i];
    }

    bool push() {
        set<pair<int, int>> q;
        d.assign(n, INF);
        par.assign(n, -1);
        d[s] = 0;
        q.insert({0, s});

        while (!q.empty()) {
            int v = (*q.begin()).second;
            q.erase(q.begin());
            for (auto i : g[v]) {
                if (Edge[i].get_cap() < 1) continue;
                int cost = d[v] + Edge[i].cost + P[v] - P[Edge[i].to];
                int to = Edge[i].to;
                if (d[to] <= cost) continue;
                par[to] = i;
                q.erase({d[to], to});
                d[to] = cost;
                q.insert({d[to], to});
            }
        }

        if (d[f] == INF) return false;
        int flow = INF;

        int v = f;
        while (v != s) {
            chkmin(flow, Edge[par[v]].get_cap());
            v = Edge[par[v] ^ 1].to;
        }

        v = f;
        while (v != s) {
            Edge[par[v]].flow += flow;
            Edge[par[v] ^ 1].flow -= flow;
            v = Edge[par[v] ^ 1].to;
        }

        rebuild();
        return true;
    }

    void build() {
        queue<int> q;
        P.assign(n, INF);
        used.assign(n, false);
        P[s] = 0;
        used[s] = true;
        q.push(s);

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            used[v] = false;
            for (auto i : g[v]) {
                if (Edge[i].get_cap() < 1) continue;
                if (P[Edge[i].to] <= P[v] + Edge[i].cost) continue;
                P[Edge[i].to] = P[v] + Edge[i].cost;
                if (!used[Edge[i].to])
                    q.push(Edge[i].to), used[Edge[i].to] = true;
            }
        }
    }

    int get_cost() {
        build();

        while (push()) {}

        int ans = 0;
        for (int i = 0; i < (int)Edge.size(); i += 2) {
            ans += Edge[i].flow * Edge[i].cost;
        }
        return ans;
    }
};

const int MAXN = 110;
int n, m;
int x[MAXN], y[MAXN], b[MAXN];
int p[MAXN], q[MAXN], c[MAXN];

int get_dist(int i, int j) {
    return abs(x[i] - p[j]) + abs(y[i] - q[j]) + 1;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        cin >> x[i] >> y[i] >> b[i];
    for (int i = 0; i < m; i++)
        cin >> p[i] >> q[i] >> c[i];
    int fans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int x;
            cin >> x;
            fans += get_dist(i, j) * x;
        }
    }
    min_cost_max_flow solver(n + m + 2, n + m, n + m + 1);
    for (int i = 0; i < n; i++) {
        solver.add_edge(n + m, i, b[i], 0);
    }
    for (int i = 0; i < m; i++) {
        solver.add_edge(i + n, n + m + 1, c[i], 0);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            solver.add_edge(i, j + n, b[i], get_dist(i, j));
        }
    }
    int ans = solver.get_cost();
    if (fans == ans) {
        cout << "OPTIMAL" << endl;
    } else {
        cout << "SUBOPTIMAL" << endl;
        vector<int> fans(m);
        for (int i = 0; i < n; i++) {
            for (auto j : solver.g[i]) {
                fans[solver.Edge[j].to - n] = solver.Edge[j].flow;
            }
            for (auto j : fans)
                cout << j << " ";
            cout << endl;
        }
    }
    return 0;
}
