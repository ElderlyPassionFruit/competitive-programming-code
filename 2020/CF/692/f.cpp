#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

struct Fenwick{
    int n;
    vector<int> tree;
    Fenwick() {}
    Fenwick(int _n) {
        n = _n;
        tree.assign(n, 0);
    }
    void upd(int pos, int val) {
        // tree[pos] += val;
        for (; pos < n; pos |= pos + 1) {
            tree[pos] += val;
        }
    }
    int get(int r) {
        int ans = 0;
        // for (; r >= 0; --r) {
        for (; r >= 0; r = (r & (r + 1)) - 1) {
            ans += tree[r];
        }
        return ans;
    }
    int get(int l, int r) {
        return get(r) - get(l - 1);
    }
};

struct SegmentTreeMax{
    int n;
    vector<int> tree;
    vector<int> cnt;
    SegmentTreeMax() {}
    SegmentTreeMax(int _n) {
        n = _n;
        tree.assign(n, 0);
        cnt.assign(n, 0);
    }
    int get(int v, int tl, int tr, int l, int r) {
        if (tl >= r || tr <= l) return 0;
        if (tl >= l && tr <= r) return tree[v];
        int tm = (tl + tr) / 2;
        return max(get(v * 2, tl, tm, l, r), get(v * 2 + 1, tm, tr, l, r));
    }
    int get(int l, int r) {
        if (l > r) return 0;
        return get(1, 0, n, l, r + 1);
        // return *max_element(tree.begin() + l, tree.begin() + r + 1);
    }
    void upd(int v, int tl, int tr, int pos, int h) {
        if (tl >= pos + 1 || tr <= pos) return;
        if (tl == tr - 1) {
            tree[pos] += h;
            return;
        }
        int tm = (tl + tr) / 2;
        upd(v * 2, tl, tm, pos, h);
        upd(v * 2 + 1, tm, tr, pos, h);
    }
    void upd(int pos, int val, int h) {
        cnt[pos] += val;
        if (val == 1 && cnt[pos] == 1) {
            upd(1, 0, n, pos, h);
            // tree[pos] = h;
        } else if (val == -1 && cnt[pos] == 0) {
            upd(1, 0, n, pos, -h);
            // tree[pos] = 0;
        }
    }
};

const int N = 2e5 + 10;
int n, q;
vector<int> g[N];

void read() {
    cin >> n >> q;
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
}

const int LOG = 18;
int tin[N], tout[N], timer = 0;
int rtin[N];
int jump[N][LOG], h[N];

void dfsLCA(int v, int p) {
    tin[v] = timer;
    rtin[timer++] = v;
    jump[v][0] = p;
    for (int i = 1; i < LOG; ++i) {
        jump[v][i] = jump[jump[v][i - 1]][i - 1];
    }
    for (auto i : g[v]) {
        if (i == p) continue;
        h[i] = h[v] + 1;
        dfsLCA(i, v);
    }
    tout[v] = timer - 1;
}

int goUp(int v, int h) {
    for (int i = 0; i < LOG; ++i) {
        if (!((h >> i) & 1)) continue;
        v = jump[v][i];
    }
    return v;
}

int lca(int v, int u) {
    if (h[v] < h[u]) swap(u, v);
    v = goUp(v, h[v] - h[u]);
    assert(h[v] == h[u]);
    if (v == u) return v;
    for (int i = LOG - 1; i >= 0; --i) {
        if (jump[v][i] != jump[u][i]) {
            v = jump[v][i];
            u = jump[u][i];
        }
    }
    assert(jump[v][0] == jump[u][0]);
    return jump[v][0];
}

int dist(int v, int u) {
    return h[v] + h[u] - 2 * h[lca(v, u)];
}

Fenwick euler;
SegmentTreeMax treeDown;

void build() {
    dfsLCA(0, 0);
    euler = Fenwick(n);
    treeDown = SegmentTreeMax(n);
}

struct cmpHeigth{
    bool operator()(const int& a, const int& b) const {
        return tie(h[a], a) > tie(h[b], b);
    }
};

multiset<int, cmpHeigth> pathesLCA;

void upd(int u, int v, int type) {
    int l = lca(u, v);
    euler.upd(tin[u], type);
    euler.upd(tin[v], type);
    euler.upd(tin[l], -type);

    treeDown.upd(tin[l], type, h[l]);

    if (type == 1) {
        pathesLCA.insert(l);
    } else if (type == -1) {
        auto it = pathesLCA.find(l);
        assert(it != pathesLCA.end());
        pathesLCA.erase(it);
    } else {
        assert(false);
    }
}

int getMaxDistant(int v, int subtreeRoot) {
    int l, r;
    l = tin[subtreeRoot];
    r = tin[v];
    int ans = 0;
    for (int i = l; i < r; ++i) {
        if (pathesLCA.find(rtin[i]) == pathesLCA.end()) continue;
        chkmax(ans, dist(rtin[i], v));
    }
    l = tout[v];
    r = tout[subtreeRoot];
    for (int i = l + 1; i <= r; ++i) {
        if (pathesLCA.find(rtin[i]) == pathesLCA.end()) continue;
        chkmax(ans, dist(rtin[i], v));
    }
    return ans;
}

bool getAns(int d) {
    if (pathesLCA.empty()) return false;
    int v = *pathesLCA.begin();
    int subtreeRoot = goUp(v, d);
    int l = tin[subtreeRoot];
    int r = tout[subtreeRoot];
    if (euler.get(l, r) != pathesLCA.size()) return false;
    if (treeDown.get(l, r) - h[v] > 2 * d) return false;
    int myDist = getMaxDistant(v, subtreeRoot);
    return myDist <= 2 * d;
}

vector<bool> ans;

void run() {
    build();
    for (int it = 0; it < q; ++it) {
        int t;
        cin >> t;
        if (t == 1) {
            int u, v;
            cin >> u >> v;
            --u;
            --v;
            upd(u, v, 1);
        } else if (t == 2) {
            int u, v;
            cin >> u >> v;
            --u;
            --v;
            upd(u, v, -1);
        } else if (t == 3) {
            int d;
            cin >> d;
            ans.push_back(getAns(d));
        } else {
            assert(false);
        }
    }
}

void write() {
    for (auto i : ans) {
        if (i) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
    read();
    run();
    write();
    return 0;
}