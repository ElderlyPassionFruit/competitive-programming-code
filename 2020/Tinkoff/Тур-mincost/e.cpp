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
    vector<int> p;
    queue<int> q;

    bool push() {
        d.assign(n, INF);
        used.assign(n, false);
        p.assign(n, -1);
        d[s] = 0;
        used[s] = true;
        q.push(s);

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            used[v] = false;
            for (auto i : g[v]) {
                if (Edge[i].get_cap() < 1) continue;
                if (d[Edge[i].to] <= d[v] + Edge[i].cost) continue;
                d[Edge[i].to] = d[v] + Edge[i].cost;
                p[Edge[i].to] = i;
                if (!used[Edge[i].to])
                    q.push(Edge[i].to), used[Edge[i].to] = true;
            }
        }

        if (d[f] == INF) return false;
        int flow = INF;

        int v = f;
        while (v != s) {
            chkmin(flow, Edge[p[v]].get_cap());
            v = Edge[p[v] ^ 1].to;
        }

        v = f;
        while (v != s) {
            Edge[p[v]].flow += flow;
            Edge[p[v] ^ 1].flow -= flow;
            v = Edge[p[v] ^ 1].to;
        }
        return true;
    }

    int get_cost(int k) {
        while (k--) {
            if (!push()) break;
        }
        int ans = 0;
        for (int i = 0; i < (int)Edge.size(); i += 2) {
            ans += Edge[i].flow * Edge[i].cost;
        }
        return ans;
    }
};

const int MAXN = 1010;
int n, k;
int s[MAXN], t[MAXN], c[MAXN];

vector<int> have;

int get_id(int t) {
    return lower_bound(all(have), t) - have.begin();
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> s[i] >> t[i] >> c[i];
        have.push_back(s[i]);
    }
    sort(all(have));
    have.resize(unique(all(have)) - have.begin());

    min_cost_max_flow solver(2 * n + 2, 2 * n, 2 * n + 1);
    for (int i = 0; i < n; i++) {
        int S = get_id(s[i]);
        int F = get_id(s[i] + t[i]);
        if (F < n) {
            solver.add_edge(2 * S + 1, 2 * F, k, 0);
        }
        if (S + 1 < n) {
            solver.add_edge(2 * S, 2 * S + 2, k, 0);
        }
        /*for (int j = 0; j < n; j++) {
            if (s[i] + t[i] <= s[j]) {
                solver.add_edge(2 * i + 1, 2 * j, 1, -c[j]);
            }
        }*/
    }
    for (int i = 0; i < n; i++) {
        int ind = get_id(s[i]);
        solver.add_edge(2 * ind, 2 * ind + 1, 1, -c[i]);
    }
 
    for (int i = 0; i < n; i++) {
        solver.add_edge(2 * n, 2 * i, k, 0);
    }
 
    for (int i = 0; i < n; i++) {
        solver.add_edge(2 * i + 1, 2 * n + 1, k, 0);
    }

    cout << solver.get_cost(k) << endl;
    solver.get_cost(k);
    for (int i = 0; i < n; i++) {
        int ans = 0;
        for (auto j : solver.g[2 * i]) {
            if (solver.Edge[j].to != 2 * i + 1) continue;
            if (solver.Edge[j].flow == 1) ans = 1;
            break;
        }
        cout << ans << " ";
    }
    cout << endl;
    return 0;
}
