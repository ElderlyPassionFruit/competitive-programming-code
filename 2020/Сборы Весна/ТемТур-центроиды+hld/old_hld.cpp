#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) (x).begin(), (x).end()
template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (x > y) x = y;};
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;};

const int MAXN = 5e4 + 10;
vector<int> g[MAXN];
int n;
vector<int> h;

void read() {  
    cin >> n;
    h.resize(n);
    for (auto &i : h)
        cin >> i;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
}

int sz[MAXN];

void dfs_sz(int v, int p) {
    sz[v] = 1;
    for (auto i : g[v]) {
        if (i != p) {
            dfs_sz(i, v);
            sz[v] += sz[i];
        }
    }
}

struct pos{
    int id_path, id_pos;
    pos() {}
    pos(int a, int b) {
        id_path = a, id_pos = b;
    }
};

const int INF = -1e9;

struct segment_tree{
    vector<int> tree;
    vector<int> pos;
    int n;
    segment_tree() {}
    void build(int v, int tl, int tr, const vector<int> & a) {
        if (tl == tr - 1) {
            tree[v] = a[tl];
            pos[tl] = v;
            return;
        }
        int tm = (tl + tr) / 2;
        build(v * 2, tl, tm, a);
        build(v * 2 + 1, tm, tr, a);
        tree[v] = max(tree[v * 2], tree[v * 2 + 1]);
    }

    segment_tree(const vector<int> & a) {
        n = a.size();
        tree.assign(n * 4, INF);
        pos.resize(n);
        build(1, 0, n, a);
    }

    void upd(int p, int val) {
        int v = pos[p];
        tree[v] = val;
        v /= 2;
        while (v) {
            tree[v] = max(tree[v * 2], tree[v * 2 + 1]);
            v /= 2;
        }
    }
    
    int get(int v, int tl, int tr, int l, int r) {
        if (tl >= r || tr <= l) return INF;
        if (tl >= l && tr <= r) return tree[v];
        int tm = (tl + tr) / 2;
        return max(get(v * 2, tl, tm, l, r), get(v * 2 + 1, tm, tr, l, r));
    }

    int get(int l, int r) {
        return get(1, 0, n, l, r + 1);
    }
};

vector<vector<int> > path;
vector<segment_tree> hld;
pos id[MAXN];

void dfs_path(int v, int p, int id1, int id2) {
    path[id1].push_back(v);
    id[v] = {id1, id2};
    for (auto i : g[v]) {
        if (i != p) {
            if (2 * sz[i] >= sz[v]) {
                dfs_path(i, v, id1, id2 + 1);
            }
            else {
                path.push_back({});
                dfs_path(i, v, path.size() - 1, 0);
            }
        }
    }
}

const int MAXLOG = 20;

int dp[MAXN][MAXLOG], tin[MAXN], tout[MAXN], timer = 0, H[MAXN];

void dfs_lca(int v, int p, int len) {
    tin[v] = timer++;
    dp[v][0] = p;
    for (int i = 1; i < MAXLOG; i++)
        dp[v][i] = dp[dp[v][i - 1]][i - 1];
    H[v] = len++;
    for (auto i : g[v]) {
        if (i != p) {
            dfs_lca(i, v, len);
        }
    }
    tout[v] = timer++;
}

bool is_upper(int v, int u) {
    return tin[v] <= tin[u] && tout[v] >= tout[u];
}

int lca(int v, int u) {
    if (is_upper(v, u)) return v;
    if (is_upper(u, v)) return u;
    for (int i = MAXLOG - 1; i >= 0; i--)
        if (!is_upper(dp[v][i], u))
            v = dp[v][i];
    return dp[v][0];
}

int dist(int v, int u) {
    return H[v] + H[u] - 2 * H[lca(v, u)];
}

void build() {
    dfs_sz(0, 0);
    path.push_back({});
    dfs_path(0, 0, 0, 0);
    for (auto i : path) {
        vector<int> a;
        for (auto j : i) {
            a.push_back(h[j]);
        }
        hld.push_back(segment_tree(a));
    }
    dfs_lca(0, 0, 0);
}

void upd(int v, int val) {
    int id1 = id[v].id_path;
    int id2 = id[v].id_pos;
    hld[id1].upd(id2, val);
    h[v] = val;
}

int get(int v, int l) {
    int cnt = H[v] - H[l] + 1;
    int ans = h[v];

    while (cnt) {
        int need = min(cnt, id[v].id_pos + 1);
        chkmax(ans, hld[id[v].id_path].get(id[v].id_pos - need + 1, id[v].id_pos));
        cnt -= need;
        v = dp[path[id[v].id_path][0]][0];
    }
    return ans;
}

int get_ans(int u, int v) {
    int l = lca(u, v);
    //cout << u << " " << v << " l = " << l << endl; 
    return max(get(u, l), get(v, l));
}

vector<int> ans;

void run() {
    build();
    /*cout << "path = " << endl;
    for (auto i : path) {
        for (auto j : i)
            cout << j << " ";
        cout << endl;
    }
    cout << endl;
    cout << "id = " << endl;
    for (int i = 0; i < n; i++)
        cout << id[i].id_path << " " << id[i].id_pos << endl;
    cout << endl;*/
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        char type;
        cin >> type;
        if (type == '!') {
            int v, val;
            cin >> v >> val;
            v--;
            upd(v, val);
        }
        else {
            int u, v;
            cin >> u >> v;
            u--;
            v--;
            ans.push_back(get_ans(u, v));
        }
    }
}

void write() {
    for (auto i : ans)
        cout << i << "\n";
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.setf(ios::fixed), cout.precision(20);
    read();
    run();
    write();
    return 0;
}