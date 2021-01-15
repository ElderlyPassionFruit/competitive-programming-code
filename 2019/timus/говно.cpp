#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
#define int ll
const ll INF = -1e18;

struct event{
    int t;
    int x, w;
    event() {}
    event(int _t, int _x) {
        t = _t;
        x = _x;
    }
    event(int _t, int _x, int _w) {
        t = _t, x = _x, w = _w;
    }
};

struct edge{
    int v;
    ll cost;
    edge() {
        v = -1;
    }
    edge(int _v, ll _cost) {
        v = _v, cost = _cost;
    }
};

const int MAXDP = 4;

struct fdp{
    bool flag;
    ll dp[2][MAXDP];
    fdp() {
        flag = false;
        for (int it = 0; it < 2; it++) {
            for (int i = 0; i < MAXDP; i++) {
                dp[it][i] = INF;
            }
        }
    }
    fdp(bool _flag) {
        flag = _flag;
        for (int it = 0; it < 2; it++) {
            for (int i = 0; i < MAXDP; i++) {
                dp[it][i] = INF;
            }
        }
        if (flag)
            dp[0][1] = dp[1][1] = 0;
        else
            dp[0][0] = dp[1][0] = 0;
    }
};

ll calc(fdp a) {
    ll ans = INF;
    for (int it = 0; it < 2; it++) {
        for (int i = 2; i < MAXDP; i++) {
            chkmax(ans, a.dp[it][i]);
        }
    }
    return ans;
}

ll calc(fdp a, fdp b, ll cost) {
    ll ans = INF;
    for (int i = 0; i < MAXDP; i++)
        for (int j = 0; j < MAXDP; j++)
            if (i + j >= 2 && a.dp[1][i] != INF && b.dp[0][i] != INF)
                chkmax(ans, a.dp[1][i] + b.dp[0][j] + cost);
    return ans;
}

const int MAXN = 1.5e5 + 10;

vector<edge> g;
vector<fdp> color;
vector<event> a;
vector<int> p;
int n, q;

void read() {
    cin >> n >> q;
    if (n == 1) {
        while (q--) {
            cout << "BAD\n";
        }
        exit(0);
    }
    color.resize(n);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        color[i] = fdp((bool)x);
    }
    g.resize(n);
    p.resize(n, -1);
    for (int i = 1; i < n; i++) {
        int w;
        cin >> p[i] >> w;
        p[i]--;
        g[i] = {p[i], w};
    }
    a.push_back({3, 1, g[1].cost});
    //a.push_back({1, 2});
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t <= 2) {
            int v;
            cin >> v;
            v--;
            a.push_back({t, v});
        }
        else {
            int v, w;
            cin >> v >> w;
            v--;
            a.push_back({t, v, w});
        }
    }
}

vector<ll> ans;

struct LCA{
    vector<vector<edge>> g;
    vector<vector<int>> dp;
    vector<ll> h;
    vector<int> tin, tout;
    int timer = 0;
    int lg = 20;
    int n;

    void dfs(int v, int p, ll len) {
        tin[v] = timer++;
        dp[v][0] = p;
        for (int i = 1; i < lg; i++)
            dp[v][i] = dp[dp[v][i - 1]][i - 1];
        h[v] = len;
        for (auto [i, cost] : g[v]) {
            dfs(i, v, len + cost);
        }
        tout[v] = timer++;
    }

    LCA(vector<edge> ed) {
        n = ed.size();
        g.assign(n, {});
        for (int i = 0; i < n; i++) {
            if (ed[i].v == -1) continue;
            g[ed[i].v].push_back({i, ed[i].cost});
        } 
        tin.assign(n, 0);
        tout.assign(n, 0);
        h.assign(n, 0);
        timer = 0;
        dp.assign(n, vector<int> (lg, 0));
        dfs(0, 0, 0);
    } 

    bool is_upper(int v, int u) {
        return tin[v] <= tin[u] && tout[v] >= tout[u];
    }

    int lca(int v, int u) {
        if (is_upper(v, u)) return v;
        if (is_upper(u, v)) return u;
        for (int i = dp[v].size() - 1; i >= 0; i--)
            if (!is_upper(dp[v][i], u))
                v = dp[v][i];
        return dp[v][0];
    }

    ll dist(int v, int u) {
        return h[v] + h[u] - 2 * h[lca(v, u)];
    }
};

void dfs_down(int v, vector<vector<edge>> & g, vector<fdp> & color) {
    for (auto [i, cost] : g[v]) {
        dfs_down(i, g, color);
    }
    for (auto [u, cost] : g[v]) {
        if (color[v].flag) {
            for (int i = 1; i < MAXDP; i++) {
                if (color[u].dp[0][i - 1] == INF) continue;
                chkmax(color[v].dp[0][i], color[u].dp[0][i - 1] + cost);
            }
            color[v].dp[0][0] = INF;
        }
        else {
            for (int i = 0; i < MAXDP; i++) {
                if (color[u].dp[0][i] == INF) continue;
                chkmax(color[v].dp[0][i], color[u].dp[0][i] + cost);
            }
        }
    }
}

void relax_dp_up(fdp & now, const fdp & can, ll cost) {
    if (now.flag) {
        for (int i = 1; i < MAXDP; i++) {
            if (can.dp[0][i - 1] == INF) continue;
            chkmax(now.dp[1][i], can.dp[0][i - 1] + cost);
        }
        now.dp[1][0] = INF;
    }
    else {
        for (int i = 0; i < MAXDP; i++) {
            if (can.dp[0][i] == INF) continue;
            chkmax(now.dp[1][i], can.dp[0][i] + cost);
        }
    }
}

void dfs_up(int v, vector<vector<edge>> & g, vector<fdp> & color) {
    for (auto [u, cost] : g[v]) {
        //relax_dp_up(color[u], color[v], cost);
        if (color[u].flag) {
            for (int i = 1; i < MAXDP; i++) {
                if (color[v].dp[1][i - 1] == INF) continue;
                chkmax(color[u].dp[1][i], color[v].dp[1][i - 1] + cost);
            }
        }
        else {
            for (int i = 0; i < MAXDP; i++) {
                if (color[v].dp[1][i] == INF) continue;
                chkmax(color[u].dp[1][i], color[v].dp[1][i] + cost);
            }
        }
    }

    vector<fdp> a, pref, suff;
    for (auto [u, cost] : g[v]) {
        a.push_back(color[u]);
        auto & dp = color[u].dp; 
        for (int i = 0; i < MAXDP; i++) {
            if (dp[0][i] == INF) continue;
            dp[0][i] += cost; 
        }
    }
    
    pref = a;
    for (int pos = 1; pos < pref.size(); pos++) {
        for (int i = 0; i < MAXDP; i++) {
            chkmax(pref[pos].dp[0][i], pref[pos - 1].dp[0][i]);
        }
    }
    
    suff = a;
    for (int pos = suff.size() - 2; pos >= 0; pos--) {
        for (int i = 0; i < MAXDP; i++) {
            chkmax(suff[pos].dp[0][i], suff[pos + 1].dp[0][i]);
        }
    }

    for (int i = 0; i < g[v].size(); i++) {
        int u = g[v][i].v;
        int cost = g[v][i].cost;
        if (i > 0) {
            relax_dp_up(color[u], pref[i - 1], cost);
        }
        if (i + 1 < n) {
            relax_dp_up(color[u], suff[i + 1], cost);
        }
    }

    for (auto [i, cost] : g[v]) {
        dfs_up(i, g, color);
    }
}

void calc_dp(vector<edge> & ed, vector<fdp> & color) {
    int n = ed.size();
    vector<vector<edge>> g(n);
    for (int i = 0; i < n; i++) {
        if (ed[i].v == -1) continue;
        g[ed[i].v].push_back({i, ed[i].cost});
    }
    dfs_down(0, g, color);
    dfs_up(0, g, color);
}

void rebuild(vector<edge> & g, vector<fdp> & color, vector<event> & a) {
    LCA graph(g);
    vector<int> need;
    for (auto i : a) {
           if (i.t == 1 || i.t == 2) {
            need.push_back(i.x);
        }
        else if (i.t == 3) {
            need.push_back(i.x);
            if (g[i.x].v != -1) {
                need.push_back(g[i.x].v);
            }
        }
    }
    
    sort(all(need), [&] (int a, int b) {
        return graph.tin[a] < graph.tin[b];
    });
    need.resize(unique(all(need)) - need.begin());
    
    int sz = need.size();
    for (int i = 0; i < sz - 1; i++) {
        need.push_back(graph.lca(need[i], need[i + 1]));
    }   
    
    sort(all(need), [&] (int a, int b) {
        return graph.tin[a] < graph.tin[b];       
    });
    need.resize(unique(all(need)) - need.begin());

    cout << "need = " << endl;
    for (auto i : need)
        cout << i << " ";
    cout << endl;

    vector<edge> gr(need.size());
    vector<int> st;

    for (int i = 0; i < need.size(); i++) {
        while (!st.empty() && !graph.is_upper(st.back(), need[i])) 
            st.pop_back();
        if (!st.empty()) {
            int v = i;
            int p = lower_bound(all(need), st.back()) - need.begin();
            gr[v] = {p, graph.dist(need[v], st.back())};
        }
        st.push_back(need[i]);
    }


    calc_dp(g, color);
    g = gr;

    vector<fdp> ncolor;
    for (int i = 0; i < need.size(); i++) {
        ncolor.push_back(color[need[i]]);
    }
    color = ncolor;

    for (auto &i : a) {
        i.x = lower_bound(all(need), i.x) - need.begin();
    }
}

void apply(vector<edge> & g, vector<fdp> & color, vector<event> a) {
    for (auto i : a) {
        if (i.t == 1) {
            int v = i.x;
            color[v].flag = 1;
            auto & dp = color[v].dp;
            for (int it = 0; it < 2; it++) {
                for (int i = MAXDP - 1; i >= 1; i--) {
                    dp[it][i] = dp[it][i - 1];
                }
                dp[it][0] = INF;
            }
        }
        else if (i.t == 2) {
            int v = i.x;
            color[v].flag = 0;
            auto & dp = color[v].dp;
            for (int it = 0; it < 2; it++) {
                for (int i = 0; i < MAXDP - 1; i++) {
                    dp[it][i] = dp[it][i + 1];
                }
                dp[it][MAXDP - 1] = INF;
            }
        }
        else if (i.t == 3) {
            int v = i.x;
            int w = i.w;
            g[v].cost = w;
        }
    }
}

void calc(vector<edge> g, vector<fdp> color, vector<event> a) {
    apply(g, color, a);
    if (color.size() == 1) {
        ans.push_back(calc(color[0]));
    }
    else {
        if (g[0].v == -1)
            ans.push_back(calc(color[0], color[1], g[1].cost));
        else
            ans.push_back(calc(color[1], color[0], g[0].cost));
    }
}

void solve(vector<edge> g, vector<fdp> color, vector<event> a, int l, int r) {
    cout << l << " " << r << endl;
    if (a.empty()) return;
    /*cout << endl;
    cout << "before" << endl;
    cout << "g = " << endl;
    for (int i = 0; i < g.size(); i++)
        cout << g[i].v << " ";
    cout << endl;
    cout << "a = " << endl;
    for (auto i : a) {
        cout << "type = " << i.t << " v = " << i.x << endl; 
    }
    cout << "end" << endl;
    cout << "color = " << endl;
    for (auto i : color) {
        cout << "it = " << endl;
        cout << i.flag << endl;
        for (int it = 0; it < 2; it ++) {
            for (int j = 0; j < MAXDP; j++) {
                cout << i.dp[it][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    cout << endl;*/ 

    rebuild(g, color, a);
    
    cout << endl;
    cout << "after" << endl;
    cout << "g = " << endl;
    for (int i = 0; i < g.size(); i++)
        cout << g[i].v << " ";
    cout << endl;
    cout << "a = " << endl;
    for (auto i : a) {
        cout << "type = " << i.t << " v = " << i.x << endl; 
    }
    cout << endl;
    cout << "color = " << endl;
    for (auto i : color) {
        cout << "it = " << endl;
        cout << i.flag << endl;
        for (int it = 0; it < 2; it ++) {
            for (int j = 0; j < MAXDP; j++) {
                cout << i.dp[it][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    cout << endl;
    cout << "end" << endl;
    cout << endl;
    //return;

    if (a.size() == 1) { calc(g, color, a); return;  } vector<event> L, R; int
    n = a.size() / 2; for (auto i : a) { if (L.size() < n) { L.push_back(i); }
    else { R.push_back(i); } }

    /*cout << "L = " << endl;
    for (auto i : L)
        cout << i.t << " " << i.x << endl;
    cout << endl;
    cout << "R = " << endl;
    for (auto i : R)
        cout << i.t << " " << i.x << endl;
    cout << endl;

    cout << "g = " << endl;
    for (int i = 0; i < g.size(); i++)
        cout << g[i].v << " ";
    cout << endl;*/

    int m = (l + r) / 2;

    solve(g, color, L, l, m);
    apply(g, color, L);
    
    /*cout << "g = " << endl;
    for (int i = 0; i < g.size(); i++)
        cout << g[i].v << " ";
    cout << endl;*/

    solve(g, color, R, m, r);
} 

void run() {
    solve(g, color, a, 0, a.size());
}

void write() {
    cout << "опа ответ = " << endl;

    for (auto i : ans) {
        if (i == INF) {
            cout << "BAD\n";
        }
        else {
            cout << i << "\n";
        }
    }
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