#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

struct edge{
    int to, cap, flow, cost;
    edge() {}
    edge(int _to, int _cap, int _cost) {
        to = _to, cap = _cap, cost = _cost, flow = 0;
    }
    int getCap() {
        return cap - flow;
    }
};
 
const int INF = 1e9;
 
struct MinCostMaxFlow{
    vector<vector<int>> g;
    vector<edge> Edges;
    int n;
    int s, t;
    
    void addEdge(int u, int v, int cap, int cost) {
        assert(u < n && v < n);
        g[u].push_back(Edges.size());
        Edges.push_back({v, cap, cost});
        g[v].push_back(Edges.size());
        Edges.push_back({u, 0, -cost});
    }
 
    MinCostMaxFlow() {}
    MinCostMaxFlow(int _n, int _s, int _t) {
        n = _n, s = _s, t = _t;
        assert(s < n && t < n);
        g.assign(n, {});
        Edges = {};
    }
 
    vector<int> dist;
    vector<int> p;
    queue<int> q;
    vector<bool> used;
 
    void FB() {
        dist.assign(n, INF);
        p.assign(n, -1);
        used.assign(n, false);
        q.push(s);
        dist[s] = 0;
        used[s] = true;
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            used[v] = false;
            for (auto i : g[v]) {
                assert(i < Edges.size());
                if (Edges[i].getCap() < 1) continue;
                int to = Edges[i].to;
                int cost = Edges[i].cost;
                if (dist[to] <= dist[v] + cost) continue;
                dist[to] = dist[v] + cost;
                p[to] = i;
                if (!used[to]) {
                    q.push(to);
                    used[to] = true;
                }
            }
        }
    }
 
    void push() {
        FB();
        assert(dist[t] != INF);
        int v = t;
        while (v != s) {
            Edges[p[v]].flow++;
            Edges[p[v] ^ 1].flow--;
            v = Edges[p[v] ^ 1].to; 
        }
    }
 
    int getAns() {
        int ans = 0;
        for (int i = 0; i < (int)Edges.size(); i += 2) {
            ans += Edges[i].flow * Edges[i].cost;
        }
        return ans;
    }

    void dfs(int v, vector<int>& path, int myN) {
        if (v < myN) {
            path.push_back(v);
        }
        if (v == t) return;
        for (auto ind : g[v]) {
            if (Edges[ind].flow == 0) continue;
            if (ind & 1) continue;
            Edges[ind].flow--;
            dfs(Edges[ind].to, path, myN);
            return;
        }
        assert(false);
    }

    void makeAns(int myN) {
        vector<int> path;
        dfs(s, path, myN);
        path.resize(unique(all(path)) - path.begin());
        for (auto i : path) {
            cout << i + 1 << " ";
        }
        cout << "\n";
    }
};

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    int n, k, x, y;
    cin >> n >> k >> x >> y;
    x--;
    y--;
    vector<string> g(n);
    for (auto& i : g) {
        cin >> i;
    }
    MinCostMaxFlow solver(n + 2 * n * n, x, y);
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (g[i][j] == 'N') continue;
            int indS = n + 2 * (min(i, j) * n + max(i, j));
            int indF = indS + 1;
            solver.addEdge(i, indS, INF, 0);
            solver.addEdge(indF, j, INF, 0);
            solver.addEdge(j, indS, INF, 0);
            solver.addEdge(indF, i, INF, 0);
            for (int cost = 0; cost < k; ++cost) {
                //solver.addEdge(i, j, 1, cost);
                solver.addEdge(indS, indF, 1, cost);
            }
        }
    }
    for (int i = 0; i < k; ++i) {
        solver.push();
    }
    int cost = solver.getAns();
	cout << cost << endl;
    //vector<vector<int>> myG(n);
    /*for (int i = 0; i < n; ++i) {
        for (auto ind : solver.g[i]) {
            if (ind & 1) continue;
            if (solver.Edges[ind].flow != 1) continue;
            myG[i].push_back(solver.Edges[ind].to);
        }
    }*/
    /*for (int i = 0; i < k; ++i) {
        int now = x;
        cout << now + 1;
        while (now != y) {
            assert(!myG[now].empty());
            int last = now;
            now = myG[now].back();
            myG[last].pop_back();
            cout << " " << now + 1;
        }
        cout << "\n";
    }*/
    for (int i = 0; i < k; ++i) {
        solver.makeAns(n);
    }
    return 0;
}