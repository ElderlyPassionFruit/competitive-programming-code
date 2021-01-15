#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(), (x).end()

const int MOD = 1e9 + 7;

int add(int a, int b) {
    a += b;
    if (a >= MOD)
        a -= MOD;
    return a;
}

struct node{
    int len, ans;
    node() {
        ans = 0, len = 0;
    }
    node(int _val) {
        _val = 1;
        ans = _val;
        len = _val;
    }
};

node merge(const node & a, const node & b) {
    if (a.len > b.len) return a;
    if (a.len < b.len) return b;
    node ans;
    ans.len = a.len;
    ans.ans = add(a.ans, b.ans);
    return ans;
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
    for (int i = 0; i < n; i++) {
        node have = dp.get(0, a[i] - 1);
        have.len++;
        if (have.len == 1) have.ans = 1;
        dp.upd(a[i], have);
    }
    cout << dp.get(0, (int)a.size()).ans << '\n';
    return 0;
}
