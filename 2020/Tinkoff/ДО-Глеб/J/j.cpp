#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(), (x).end()

struct segment_tree{
    vector<vector<int>> tree;
    int n;
    segment_tree() {}

    void build(int v, int tl, int tr, const vector<int> & a) {
        if (tl == tr - 1) {
            tree[v] = {a[tl]};
            return;
        }
        int tm = (tl + tr) / 2;
        build(v * 2, tl, tm, a);
        build(v * 2 + 1, tm, tr, a);
        vector<int> &L = tree[v * 2], &R = tree[v * 2 + 1];
        tree[v].resize(L.size() + R.size());
        merge(all(L), all(R), tree[v].begin());
    }

    segment_tree(const vector<int> & a) {
        n = a.size();
        tree.assign(4 * n, {});
        build(1, 0, n, a);
    }

    int get(int v, int tl, int tr, int l, int r, int x, int y) {
        if (tl >= r || tr <= l) return 0;
        if (tl >= l && tr <= r) {
            return upper_bound(all(tree[v]), y) - lower_bound(all(tree[v]), x);
        }
        int tm = (tl + tr) / 2;
        return get(v * 2, tl, tm, l, r, x, y) + get(v * 2 + 1, tm, tr, l, r, x, y);
    }

    int get(int l, int r, int x, int y) {
        return get(1, 0, n, l, r + 1, x, y);
    }
};

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cout.precision(20);
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (auto &i : a)
        cin >> i;
    segment_tree tree(a);
    while (q--) {
        int l, r, x, y;
        cin >> l >> r >> x >> y;
        l--;
        r--;
        cout << tree.get(l, r, x, y) << '\n';
    }
    return 0;
}
