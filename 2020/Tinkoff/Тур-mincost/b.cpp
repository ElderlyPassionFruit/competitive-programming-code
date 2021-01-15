#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

#define FAST_ALLOCATOR_MEMORY 54*1024*1024
#ifdef FAST_ALLOCATOR_MEMORY
int allocator_pos = 0;
char allocator_memory[(int) FAST_ALLOCATOR_MEMORY];
inline void *operator new(size_t n) {
    char *res = allocator_memory + allocator_pos;
    allocator_pos += n;
    assert(allocator_pos <= (int) FAST_ALLOCATOR_MEMORY);
    return (void *) res;
}

inline void operator delete(void *) noexcept {}
inline void operator delete(void *, size_t) {}
#endif

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

    const int INF = 2e9;

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

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    int s = 2 * n, f = 2 * n + 1;
    min_cost_max_flow solver(2 * n + 2, s, f);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int x;
            cin >> x;
            solver.add_edge(i, j + n, 1, x);
        }
    }
    for (int i = 0; i < n; i++) {
        solver.add_edge(s, i, 1, 0);
    }
    for (int i = 0; i < n; i++) {
        solver.add_edge(i + n, f, 1, 0);
    }
    cout << solver.get_cost() << "\n";
    for (int i = 0; i < n; i++) {
        for (auto j : solver.g[i]) {
            if (solver.Edge[j].flow != 1) continue;
            cout << i + 1 << " " << solver.Edge[j].to - n + 1 << "\n";
            break;
        }
    }
    return 0;
}
