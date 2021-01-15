// CEOI 2019 day1 B https://codeforces.com/contest/1192/submission/72896510

#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()
#define data data228
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct fDist{
    int dist, flag;
};

const int INF = -1e9;

struct Node{
    int dist, flag;
    int mod;
    int ans[2];
    Node() {
        dist = INF, flag = -1;
        mod = 0;
        fill(ans, ans + 2, INF);
    }
    Node(fDist a) {
        dist = a.dist;
        flag = a.flag;
        mod = 0;
        fill(ans, ans + 2, INF);
        ans[flag] = dist;
    }
};

Node merge(const Node& a, const Node& b) {
    Node ans;
    for (int flag = 0; flag <= 1; ++flag) {
        chkmax(ans.ans[flag], a.ans[flag]);
        chkmax(ans.ans[flag], b.ans[flag]);
    }
    return ans;
}

struct segment_tree{
    /*vector<ll> tree;
    vector<ll> mod;
    int n;
    segment_tree() {}

    void build(int v, int tl, int tr, const vector<ll> & a) {
        if (tl == tr - 1) {
            tree[v] = a[tl];
            return;
        }
        int tm = (tl + tr) / 2;
        build(v * 2, tl, tm, a);
        build(v * 2 + 1, tm, tr, a);
        tree[v] = max(tree[v * 2], tree[v * 2 + 1]);
    }

    segment_tree(vector<ll> a) {
        n = a.size();
        tree.assign(n * 4, 0);
        mod.assign(n * 4, 0);
        build(1, 0, n, a);
    }

    void push(int v) {
        mod[v * 2] += mod[v];
        mod[v * 2 + 1] += mod[v];
        tree[v] += mod[v];
        mod[v] = 0;
    }

    ll get_val(int v) {
        return tree[v] + mod[v];
    }

    void upd(int v, int tl, int tr, int l, int r, ll add) {
        if (tl >= r || tr <= l) return;
        if (tl >= l && tr <= r) {
            mod[v] += add;
            return;
        }
        push(v);
        int tm = (tl + tr) / 2;
        upd(v * 2, tl, tm, l, r, add);
        upd(v * 2 + 1, tm, tr, l, r, add);
        tree[v] = max(get_val(v * 2), get_val(v * 2 + 1));
    }

    void upd(int l, int r, ll add) {
        upd(1, 0, n, l, r + 1, add);
    }

    ll get() {
        return get_val(1);
    }*/

    int n;
    vector<Node> tree;

    segment_tree() {}
    
    void build(int v, int tl, int tr, const vector<fDist>& a) {
        if (tl >= tr) return;
        if (tl == tr - 1) {
            tree[v] = Node(a[tl]);
            return;
        }
        int tm = (tl + tr) / 2;
        build(v * 2, tl, tm, a);
        build(v * 2 + 1, tm, tr, a);
        tree[v] = merge(tree[v * 2], tree[v * 2 + 1]);
    }

    segment_tree(const vector<fDist>& a) {
        n = a.size();
        tree.resize(4 * n);
        /*for (int i = 0; i < n; ++i) {
            tree[i] = Node(a[i]);
        }*/
        build(1, 0, n, a);
    }

    Node getVal(int v) {
        Node ans = tree[v];
        if (ans.mod) {
            swap(ans.ans[0], ans.ans[1]);
        }
        return ans;
    }

    void push(int v) {
        if (tree[v].mod) {
            tree[v * 2].mod ^= tree[v].mod;
            tree[v * 2 + 1].mod ^= tree[v].mod;
            tree[v].mod = 0;
        }
    }

    void upd(int v, int tl, int tr, int l, int r) {
        if (tl >= r || tr <= l) return;
        if (tl >= l && tr <= r) {
            tree[v].mod ^= 1;
            return;
        }
        push(v);
        int tm = (tl + tr) / 2;
        upd(v * 2, tl, tm, l, r);
        upd(v * 2 + 1, tm, tr, l, r);
        tree[v] = merge(getVal(v * 2), getVal(v * 2 + 1));
    }

    void upd(int l, int r) {
        upd(1, 0, n, l, r + 1);
        /*
        for (int i = l; i <= r; ++i) {
            tree[i].flag ^= 1;
            swap(tree[i].ans[0], tree[i].ans[1]);
        }*/
    }

    Node get() {
        /*Node ans;
        for (int i = 0; i < n; ++i) {
            chkmax(ans.ans[0], tree[i].ans[0]);
            chkmax(ans.ans[1], tree[i].ans[1]);
        }
        return ans;*/
        return getVal(1);
    }
};

struct fsetik{
    int v;
    ll dist;
    fsetik() {}
    fsetik(int _v, ll _dist) {
        v = _v, dist = _dist;
    }
};

bool operator<(const fsetik & a, const fsetik & b) {
    return tie(a.dist, a.v) < tie(b.dist, b.v);
}

struct edge{
    int to;
    int type;
    edge() {}
    edge(int _to, int _type) {
        to = _to, type = _type;
    }
};

struct event{
    int u, v;
    int type;
    event() {}
    event(int _u, int _v, int _type) {
        u = _u, v = _v, type = _type;
    }
};

const int MAXN = 5e5 + 10, MAXLOG = 21;
vector<edge> g[MAXN];
vector<event> ed;

int n, q;
ll w;

bool used[MAXN];
int sz[MAXN];
int centr;

int tin[MAXLOG][MAXN], tout[MAXLOG][MAXN], ind[MAXLOG][MAXN];
int timer;
vector<vector<fDist>> dist[MAXN];
int par[MAXLOG][MAXN];
int h[MAXN];

vector<segment_tree> data[MAXN];
set<fsetik> help[MAXN][2];
set<fsetik> fans[2];

vector<ll> ans;

void read() {
    /*cin >> n >> q >> w;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        ll c;
        cin >> u >> v >> c;
        u--;
        v--;
        ed.push_back({u, v, c});
        g[u].push_back({v, c});
        g[v].push_back({u, c});
    }*/
    cin >> n;
    for (int i = 0; i < n - 1; ++i) {
        int u, v, type;
        cin >> u >> v >> type;
        --u;
        --v;
        ed.push_back({u, v, type});
        g[u].push_back({v, type});
        g[v].push_back({u, type});
    }
    //cout << "read : ok" << endl;
}

void dfs_centroid(int v, int p, int size) {
    sz[v] = 1;
    int mx = 0;
    for (auto [to, cost] : g[v]) {
        if (to == p) continue;
        if (used[to]) continue;
        dfs_centroid(to, v, size);
        chkmax(mx, sz[to]);
        sz[v] += sz[to];
    }
    chkmax(mx, size - sz[v]);
    if (mx <= size / 2) {
        centr = v;
    }
}

void dfs_calc(int v, int p, int centr, int Ind, int H, int len, int flag) {
    tin[H][v] = timer++;
    ind[H][v] = Ind;
    dist[centr][dist[centr].size() - 1].push_back({len, flag});
    par[H][v] = centr;

    for (auto [to, myFlag] : g[v]) {
        if (used[to]) continue;
        if (to == p) continue;
        dfs_calc(to, v, centr, Ind, H, len + 1, flag ^ myFlag);
    }   
    tout[H][v] = timer - 1;
}

void find_centroid(int v, int H, int size) {
    dfs_centroid(v, -1, size);
    v = centr;
    par[H][v] = v;
    used[v] = true;
    h[v] = H;
    int Ind = 0;
    tin[H][v] = -1;
    tout[H][v] = n + 1;
    for (auto [to, flag] : g[v]) {
        if (used[to]) continue;
        dist[v].push_back({});
        timer = 0;
        dfs_calc(to, -1, v, Ind++, H, 1, flag);
    }
    
    for (auto [to, flag] : g[v]) {
        if (used[to]) continue;
        int fsz = sz[to];
        if (fsz > sz[v]) fsz = size - sz[v];
        find_centroid(to, H + 1, fsz);
    }
}

int get_best(int v, int flag) {
    /*if (help[v].empty()) return 0;
    if (help[v].size() == 1) return help[v].begin()->dist;
    ll have = 0;
    auto it = help[v].end();
    --it;
    have += it->dist;
    --it;
    have += it->dist;
    return have;*/
    if (flag == 1) {
        if (help[v][flag].size() < 2) return 0;
        int have = 0;
        auto it = help[v][flag].end();
        --it;
        have += it->dist;
        --it;
        have += it->dist;
        return have;
    } else if (flag == 0) {
        if (help[v][flag].empty()) return 0;
        if (help[v][flag].size() == 1) return help[v][flag].begin()->dist;
        int have = 0;
        auto it = help[v][flag].end();
        --it;
        have += it->dist;
        --it;
        have += it->dist;
        return have;    
    } else {
        assert(false);
        return -1;
    }
}

void build() {
    find_centroid(0, 0, n);
    //cout << "centroid : ok" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < dist[i].size(); j++) {
            data[i].push_back(segment_tree(dist[i][j]));
            for (int flag = 0; flag <= 1; ++flag) {
                //cout << "puhh" << endl;
                help[i][flag].insert({j, data[i][j].get().ans[flag]});
                //cout << "puhh" << endl;
            }
        }
        for (int flag = 0; flag <= 1; ++flag) {
            fans[flag].insert({i, get_best(i, flag)});
        }
    }
    //cout << "build : ok" << endl; 
}

void upd(int v, int Tin, int Tout, int ind) {
    /*fans.erase(fans.find({v, get_best(v)}));
    help[v].erase({ind, data[v][ind].get()});
    data[v][ind].upd(Tin, Tout, add);
    help[v].insert({ind, data[v][ind].get()});
    fans.insert({v, get_best(v)});*/

    for (int flag = 0; flag <= 1; ++flag) {
        fans[flag].erase(fans[flag].find({v, get_best(v, flag)}));
        help[v][flag].erase({ind, data[v][ind].get().ans[flag]});
    }
    data[v][ind].upd(Tin, Tout);
    for (int flag = 0; flag <= 1; ++flag) {
        help[v][flag].insert({ind, data[v][ind].get().ans[flag]});
        fans[flag].insert({v, get_best(v, flag)});
    }
}

void upd(int pos) {
    int v = ed[pos].v;
    int u = ed[pos].u;
    
    for (int i = 0; i <= min(h[u], h[v]); i++) {
        assert(par[i][v] == par[i][u]);
        int find = ind[i][v];
        if (v == par[i][v])
            find = ind[i][u];

        int nv = par[i][v], Tin = max(tin[i][v], tin[i][u]), Tout = min(tout[i][v], tout[i][u]);
        upd(nv, Tin, Tout, find);      
    }
}

int get() {
    //assert(fans.size());
    //return (--fans.end())->dist;
    int ans = 0;
    for (int flag = 0; flag <= 1; ++flag) {
        if (fans[flag].empty()) continue;
        chkmax(ans, (--fans[flag].end())->dist);
    }
    return ans;
}

void run() {
    build();
    /*ll last = 0;

    while (q--) {
        int ind;
        ll c;
        cin >> ind >> c;
        ind = (ll) (ind + last) % (n - 1);
        c = (c + last) % w;
        upd(ind, c);
        last = get();
        ans.push_back(last);
    }*/
    int q;
    cin >> q;
    while (q--) {
        int ind;
        cin >> ind;
        --ind;
        upd(ind);
        cout << get() << "\n";
    }
}

void write() {
    /*for (auto i : ans) {
        cout << i << "\n";
    }*/
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