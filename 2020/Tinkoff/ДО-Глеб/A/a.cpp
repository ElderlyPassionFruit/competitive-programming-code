#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(), (x).end()

struct node{
    int ans, l, r, sz;
    node() {
        ans = 0, l = 0, r = 0, sz = 0;
    }
    node(int val) {
        if (val == 0) {
            val = 1;
        } else {
            val = 0;
        }
        ans = l = r = val;
        sz = 1;
    }
};

node merge(const node & a, const node & b) {
    if (a.sz == 0) return b;
    if (b.sz == 0) return a;
    node ans;
    ans.sz = a.sz + b.sz;
    ans.ans = max(a.ans, b.ans);
    if (a.sz == a.l && b.sz == b.l) {
        ans.l = ans.r = ans.ans = a.ans + b.ans;
    } else if (a.sz == a.l) {
        ans.ans = max(ans.ans, a.ans + b.l);
        ans.l = a.l + b.l;
        ans.r = b.r;
    } else if (b.sz == b.l) {
        ans.ans = max(ans.ans, a.r + b.ans);
        ans.l = a.l;
        ans.r = a.r + b.l;
    } else {
        ans.ans = max(ans.ans, a.r + b.l);
        ans.l = a.l;
        ans.r = b.r;
    }
    return ans;
}

struct segment_tree{
    vector<node> tree;
    int n;
    vector<int> pos;
    segment_tree() {}

    void build(int v, int tl, int tr, const vector<int> & a) {
        if (tl == tr - 1) {
            pos[tl] = v;
            tree[v] = node(a[tl]);
            return;
        }
        int tm = (tl + tr) / 2;
        build(v * 2, tl, tm, a);
        build(v * 2 + 1, tm, tr, a);
        tree[v] = merge(tree[v * 2], tree[v * 2 + 1]);
    }

    segment_tree(const vector<int> & a) {
        n = a.size();
        tree.resize(4 * n);
        pos.resize(n);
        build(1, 0, n, a);
    }

    node get(int v, int tl, int tr, int l, int r) {
        if (tl >= r || tr <= l) return node();
        if (tl >= l && tr <= r) return tree[v];
        int tm = (tl + tr) / 2;
        return merge(get(v * 2, tl, tm, l, r), get(v * 2 + 1, tm, tr, l, r));
    }

    int get(int l, int r) {
        return get(1, 0, n, l, r + 1).ans;
    }

    void upd(int v, int val) {
        v = pos[v];
        tree[v] = node(val);
        v /= 2;
        while (v) {
            tree[v] = merge(tree[v * 2], tree[v * 2 + 1]);
            v /= 2;
        }
    }
};

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cout.precision(20);
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &i : a)
        cin >> i;
    segment_tree tree(a);
    int m;
    cin >> m;
    while (m--) {
        string type;
        cin >> type;
        if (type == "QUERY") {
            int l, r;
            cin >> l >> r;
            l--;
            r--;
            cout << tree.get(l, r) << "\n";
        } else {
            int pos, val;
            cin >> pos >> val;
            pos--;
            tree.upd(pos, val);
        }
    }
    return 0;
}
