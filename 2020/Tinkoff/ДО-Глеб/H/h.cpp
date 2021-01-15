#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(), (x).end()

struct node{
    ll ans;
    node() {
        ans = 0;
    }
    node(ll _val) {
        ans = _val;
    }
};

node merge(const node & a, const node & b) {
    return node(a.ans + b.ans);
}

struct segment_tree{
    vector<node> tree;
    int n;
    vector<int> pos;
    segment_tree() {}

    void build(int v, int tl, int tr) {
        if (tl == tr - 1) {
            pos[tl] = v;
            return;
        }
        int tm = (tl + tr) / 2;
        build(v * 2, tl, tm);
        build(v * 2 + 1, tm, tr);
    }

    segment_tree(int _n) {
        n = _n;
        tree.assign(4 * n, node());
        pos.resize(n);
        build(1, 0, n);
    }

    node get(int v, int tl, int tr, int l, int r) {
        if (tl >= r || tr <= l) return node();
        if (tl >= l && tr <= r) return tree[v];
        int tm = (tl + tr) / 2;
        return merge(get(v * 2, tl, tm, l, r), get(v * 2 + 1, tm, tr, l, r));
    }

    node get(int l, int r) {
        return get(1, 0, n, l, r + 1);
    }

    void upd(int v, node val) {
        v = pos[v];
        tree[v] = merge(tree[v], val);
        v /= 2;
        while (v) {
            tree[v] = merge(tree[v * 2], tree[v * 2 + 1]);
            v /= 2;
        }
    }
};

void Unique(vector<int> & a) {
    vector<int> have = a;
    sort(all(have));
    have.resize(unique(all(have)) - have.begin());
    for (auto &i : a) {
        i = lower_bound(all(have), i) - have.begin();
    }
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cout.precision(20);
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &i : a)
        cin >> i;
    Unique(a);
    segment_tree dp(a.size());
    vector<ll> help(n);
    for (int i = (int)a.size() - 1; i >= 0; i--) {
        help[i] = dp.get(0, a[i] - 1).ans;
        dp.upd(a[i], node(1));
    }
    dp = segment_tree(a.size());
    ll ans = 0;
    for (int i = (int)a.size() - 1; i >= 0; i--) {
        ans += dp.get(0, a[i] - 1).ans;
        dp.upd(a[i], help[i]);
    }
    cout << ans << endl;
    return 0;
}
