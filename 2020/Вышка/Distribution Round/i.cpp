#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

#define int ll

const int INF = 1e10 + 228 + 1337;

struct node{
    int max_val, second_max_val, cnt_max_val;
    ll sum;
    int mod;
    int sz;
    node() {
        sz = 0;
        mod = INF;
        max_val = -INF;
        second_max_val = -INF;
        cnt_max_val = 0;
        sum = 0;
    }
    node(int x) {
        max_val = x;
        second_max_val = -INF;
        cnt_max_val = 1;
        sum = x;
        mod = INF;
        sz = 1;
    }
    void wr() {

    }
};

node merge(const node & a, const node & b) {
    if (!a.sz) return b;
    if (!b.sz) return a;
    node ans;
    ans.mod = INF;
    ans.sum = a.sum + b.sum;
    ans.sz = a.sz + b.sz;
    ans.max_val = max(a.max_val, b.max_val);
    if (a.max_val == ans.max_val) ans.cnt_max_val += a.cnt_max_val;
    if (b.max_val == ans.max_val) ans.cnt_max_val += b.cnt_max_val;
    if (a.max_val == b.max_val) {
        ans.second_max_val = max(a.second_max_val, b.second_max_val);
    } else if (a.max_val > b.max_val) {
        ans.second_max_val = max(a.second_max_val, b.max_val);
    } else if (a.max_val < b.max_val) {
        ans.second_max_val = max(a.max_val, b.second_max_val);
    }
    return ans;
}

struct segment_tree{
    vector<node> tree;
    int n;

    segment_tree() {}

    void build(int v, int tl, int tr, const vector<int>& a) {
        if (tl == tr - 1) {
            tree[v] = node(a[tl]);
            return;
        }
        int tm = (tl + tr) / 2;
        build(v * 2, tl, tm, a);
        build(v * 2 + 1, tm, tr, a);
        tree[v] = merge(tree[v * 2], tree[v * 2 + 1]);
    }

    segment_tree(const vector<int>& a) {
        n = a.size();
        tree.assign(n * 4, {});
        build(1, 0, n, a);
    }

    void push(int v, int tl, int tr) {
        if (tree[v].mod == -1) return;
        if (tl != tr - 1) {
            chkmin(tree[v * 2].mod, tree[v].mod);
            chkmin(tree[v * 2 + 1].mod, tree[v].mod);
        }
        if (tree[v].max_val <= tree[v].mod) return;
        assert(tree[v].mod > tree[v].second_max_val);
        tree[v].sum -= (ll)(tree[v].max_val - tree[v].mod) * tree[v].cnt_max_val;
        tree[v].max_val = tree[v].mod;
        tree[v].mod = INF;
    }

    void upd(int v, int tl, int tr, int l, int r, int val) {
        push(v, tl, tr);
        if (tl >= r || tr <= l || tree[v].max_val <= val) return;
        if (tl >= l && tr <= r && tree[v].second_max_val < val) {   
            tree[v].mod = val;
            push(v, tl, tr);
            return;
        }
        if (tl == tr - 1) return;
        int tm = (tl + tr) / 2;
        upd(v * 2, tl, tm, l, r, val);
        upd(v * 2 + 1, tm, tr, l, r, val);
        tree[v] = merge(tree[v * 2], tree[v * 2 + 1]);
    }

    void upd(int l, int r, int val) {
        upd(1, 0, n, l, r + 1, val);
    }

    ll getSum(int v, int tl, int tr, int l, int r) {
        if (tl >= r || tr <= l) return 0;
        push(v, tl, tr);
        if (tl >= l && tr <= r) {
            return tree[v].sum;
        }
        int tm = (tl + tr) / 2;
        ll ans = getSum(v * 2, tl, tm, l, r) + getSum(v * 2 + 1, tm, tr, l, r);
        return ans;
    }

    ll getSum(int l, int r) {
        return getSum(1, 0, n, l, r + 1);
    }
  
    ll getMax(int v, int tl, int tr, int l, int r) {
        if (tl >= r || tr <= l) return 0;
        push(v, tl, tr);
        if (tl >= l && tr <= r) {
            return tree[v].max_val;
        }
        int tm = (tl + tr) / 2;
        ll ans = max(getMax(v * 2, tl, tm, l, r), getMax(v * 2 + 1, tm, tr, l, r));
        return ans;
    }

    ll getMax(int l, int r) {
        return getMax(1, 0, n, l, r + 1);
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (auto& i : a) {
        cin >> i;
    }
    segment_tree tree(a);
    while (q--) {
        char t;
        cin >> t;
        if (t == 'o') {
            int l, r, t2;
            cin >> l >> r >> t2;
            l--;
            r--;
            tree.upd(l, r, t2);
        } else if (t == 'm') {
            int l, r;
            cin >> l >> r;
            l--;
            r--;
            cout << tree.getMax(l, r) << "\n";
        } else {
            int l, r;
            cin >> l >> r;
            l--;
            r--;
            cout << tree.getSum(l, r) << "\n";        
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}