#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

struct Edge{
    int to, cap, flow;
    Edge() {}
    Edge(int _to, int _cap) {
        to = _to, cap = _cap, flow = 0;
    }
    int getCap() {
        return cap - flow;
    }
};

struct MaxFlow{
    int n;
    int s, t;
    vector<vector<int>> g;
    vector<Edge> edges;
    MaxFlow() {}
    MaxFlow(int _n, int _s, int _t) {
        n = _n;
        s = _s;
        t = _t;
        g.assign(n, {});
        edges = {};
    }
    void addEdge(int u, int v, int cap) {
        g[u].push_back(edges.size());
        edges.push_back({v, cap});
        g[v].push_back(edges.size());
        edges.push_back({u, cap});
    }
    const int INF = 1e9;
    vector<int> dist;
    queue<int> q;
    void bfs() {
        dist.assign(n, INF);
        dist[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (auto i : g[v]) {
                if (edges[i].getCap() < 1) continue;
                int to = edges[i].to;
                if (dist[to] != INF) continue;
                dist[to] = dist[v] + 1;
                q.push(to);
            }
        }
    }
    vector<int> pos;
    int dfs(int v, int minFlow) {
        if (minFlow == 0) return 0;
        if (v == t) return minFlow;
        for (; pos[v] < (int)g[v].size(); ++pos[v]) {
            int ind = g[v][pos[v]];
            if (edges[ind].getCap() < 1) continue;
            int to = edges[ind].to;
            if (dist[v] + 1 != dist[to]) continue;
            int ans = dfs(to, min(minFlow, edges[ind].getCap()));
            if (!ans) continue;
            edges[ind].flow += ans;
            edges[ind ^ 1].flow -= ans;
            return ans;
        }
        return 0;
    }
    int getMaxFlow() {
        while (true) {
            bfs();
            if (dist[t] == INF) break;
            pos.assign(n, 0);
            while (dfs(s, INF)) {

            }
        }
        int ans = 0;
        for (int i = 0; i < (int)edges.size(); i += 2) {
            ans += edges[i].flow;
        }
        return ans;
    }
};

const int N = 210;
int n, m;
char a[N][N];

void read() {
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> a[i][j];
        }
    }
}

int ans;

bool checkCell(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

void run() {
    MaxFlow solver();
    ans = 0;

    ans -= solver.getMaxFlow(); 
}

void write() {
    cout << ans << endl;
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
    read();
    run();
    write();
    return 0;
}