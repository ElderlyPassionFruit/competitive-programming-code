#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 4e4 + 10;
int n;
vector<int> gr[MAXN], g[MAXN];
char a[MAXN];

void read() {
    cin >> n;
    for (int i = 1; i < n; i++) {
        int p;
        cin >> p;
        p--;
        gr[i].push_back(p);
        gr[p].push_back(i);
    }   
    //for (int i = 0; i < n; i++) {
    //    cin >> a[i];
    //}
}

int ans;

int sz[MAXN];
bool used[MAXN];
int centr;

void dfsCentr(int v, int p, int size) {
    sz[v] = 1;
    int mx = 0;
    for (auto i : g[v]) {
        if (used[i]) continue;
        if (i == p) continue;
        dfsCentr(i, v, size);
        sz[v] += sz[i];
        chkmax(mx, sz[i]);
    }
    chkmax(mx, size - sz[v]);
    if (mx * 2 <= size) {
        centr = v;
    }
}
/*
pair<int, int> merge(const pair<int, int> & a, const pair<int, int> & b) {
    return {min(a.first, b.first), max(a.second, b.second)};
}

const pair<int, int> INF = {1000000, -1000000};
*/
struct segment_tree{
    int n;
    /*vector<pair<int, int>> tree;
    vector<int> mod;
    vector<int> pos;*/
    segment_tree() {}
    /*void build(int v, int tl, int tr) {
        if (tl == tr - 1) {
            pos[tl] = v;
            return;
        }
        int tm = (tl + tr) / 2;
        build(v * 2, tl, tm);
        build(v * 2 + 1, tm, tr);
    }*/
    segment_tree(int _n) {
        n = _n;
       /* tree.assign(4 * n, make_pair(0, 0));
        mod.assign(4 * n, 0);
        pos.assign(n, -1);
        build(1, 0, n);*/
    }

  /*  pair<int, int> get_val(int v) {
        return {tree[v].first + mod[v], tree[v].second + mod[v]};
    }

    void push(int v) {
        if (!mod[v]) return;
        mod[v * 2] += mod[v];
        mod[v * 2 + 1] += mod[v];
        tree[v].first += mod[v];
        tree[v].second += mod[v];
        mod[v] = 0;
    }

    void upd(int v, int tl, int tr, int l, int r, int val) {
        if (tl >= r || tr <= l) return;
        if (tl >= l && tr <= r) {
            mod[v] += val;
            return;
        }
        push(v);
        int tm = (tl + tr) / 2;
        upd(v * 2, tl, tm, l, r, val);
        upd(v * 2 + 1, tm, tr, l, r, val);
        tree[v] = merge(get_val(v * 2), get_val(v * 2 + 1));
    }
*/
    vector<int> stMin;
    vector<int> stMax;

    void upd(int r, int val) {
        if (val == 1) {

        } else {
            assert(!stMin.empty() && !stMax.empty());
            stMin.pop_back();
            stMax.pop_back();
        }

       //      upd(1, 0, n, 0, r + 1, val);
    }

    /*pair<int, int> get(int v, int tl, int tr, int l, int r) {
        if (tl >= r || tr <= l) return INF;
        if (tl >= l && tr <= r) return get_val(v);
        push(v);
        int tm = (tl + tr) / 2;
        auto ans = merge(get(v * 2, tl, tm, l, r), get(v * 2 + 1, tm, tr, l, r));
        tree[v] = merge(get_val(v * 2), get_val(v * 2 + 1));
        return ans;
    }*/

    int get_min(int r) {
        return r;
       // return get(1, 0, n, 0, r + 1).first;
    }

    int get_max(int r) {
        return r;
       // return get(1, 0, n, 0, r + 1).second;
    }
};

segment_tree tree;

set<pair<int, int>> cnt[MAXN * 2];

void dfsAdd(int v, int p, int len, int bal, int add, int fans) {
    bal += (a[v] == '(' ? 1 : -1);
    chkmax(fans, bal);
    tree.upd(len, a[v] == '(' ? 1 : -1);
    int val = tree.get_min(len);
    if (val >= 0 && bal > 0) {
        if (add == 1) {
            cnt[bal + MAXN].insert({tree.get_max(len), v});
        } else {
            cnt[bal + MAXN].erase({tree.get_max(len), v});
        }
    }
    if (bal == 0) {
        chkmax(ans, tree.get_max(len));
        chkmax(ans, fans);
    }
    for (auto i : g[v]) {
        if (used[i]) continue;
        if (i == p) continue;
        dfsAdd(i, v, len + 1, bal, add, fans);
    }
    tree.upd(len, a[v] == '(' ? -1 : 1);
}

void dfsCalc(int v, int p, int len, int bal) {
    bal += (a[v] == '(' ? -1 : 1);
    tree.upd(len, a[v] == '(' ? -1 : 1);
    int val = tree.get_max(len);
    if (val > 0 && !cnt[bal + MAXN].empty()) {
        chkmax(ans, max((--cnt[bal + MAXN].end())->first, val));
    }
    for (auto i : g[v]) {
        if (used[i]) continue;
        if (i == p) continue;
        dfsCalc(i, v, len + 1, bal);
    }
    tree.upd(len, a[v] == '(' ? 1 : -1);
}

void Add(int i, int v, int add) {
    tree.upd(0, (a[v] == '(' ? 1 : -1));
    dfsAdd(i, v, 1, (a[v] == '(' ? 1 : -1), add, (a[v] == '(' ? 1 : -1));
    tree.upd(0, (a[v] == '(' ? -1 : 1));
}

void solve(int v, int size) {
    dfsCentr(v, -1, size);
    v = centr;
    for (auto i : g[v]) {
        if (used[i]) continue;
        Add(i, v, 1);
    }
    for (auto i : g[v]) {
        if (used[i]) continue;
        Add(i, v, -1);
        dfsCalc(i, v, 0, 0);
        Add(i, v, 1);
    }
    for (auto i : g[v]) {
        if (used[i]) continue;
        Add(i, v, -1);
    }
    used[v] = true;
    for (auto i : g[v]) {
        if (used[i]) continue;
        int fsz = sz[i];
        if (fsz > sz[v]) {
            fsz = size - sz[v];
        }
        solve(i, fsz);
    }
}

int tin[MAXN], rtin[MAXN];
int timer = 0;

void dfsTin(int v, int p) {
    tin[v] = timer++;
    rtin[timer - 1] = v;
    for (auto i : gr[v]) {
        if (i == p) continue;
        dfsTin(i, v);
    }
}

void renum() {
    dfsTin(0, 0);
    for (int i = 0; i < n; i++) {
        g[tin[i]] = gr[i];
        for (auto &v : g[tin[i]]) {
            v = tin[v];
        }
    }
    for (int i = 0; i < n; i++) {
        cin >> a[tin[i]];
    }
}

void run() {
    renum();
    ans = 0;
    tree = segment_tree(n);
    solve(0, n);
}

void write() {
    cout << ans << endl;
}

signed main() {
    freopen("btree.in", "r", stdin);
    freopen("btree.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    read();
    run();
    write();
    return 0;
}
