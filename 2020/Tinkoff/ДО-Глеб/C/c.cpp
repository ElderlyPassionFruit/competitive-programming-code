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
    node(char val) {
        ans = 0;
        sz = 1;
        l = r = 0;
        if (val == '(') {
            r++;
        } else {
            l++;
        }
    }
};

node merge(const node & a, const node & b) {
    if (a.sz == 0) return b;
    if (b.sz == 0) return a;
    node ans;
    ans.sz = a.sz + b.sz;
    ans.ans = a.ans + b.ans;
    int x = min(a.r, b.l);
    ans.ans += x * 2;
    ans.l = a.l + b.l - x;
    ans.r = a.r + b.r - x;
    return ans;
}

struct segment_tree{
    vector<node> tree;
    int n;
    vector<int> pos;
    segment_tree() {}

    void build(int v, int tl, int tr, const string & a) {
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

    segment_tree(const string & a) {
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
};

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cout.precision(20);
    string a;
    cin >> a;
    segment_tree tree(a);
    int m;
    cin >> m;
    while (m--) {
        int l, r;
        cin >> l >> r;
        l--;
        r--;
        cout << tree.get(l, r) << "\n";
    }
    return 0;
}
