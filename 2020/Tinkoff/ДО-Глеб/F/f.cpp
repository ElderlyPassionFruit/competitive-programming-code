#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(), (x).end()

struct segment_tree{
    vector<int> tree;
    int n;
    vector<int> pos;
    segment_tree() {}

    void build(int v, int tl, int tr, const vector<int> & a) {
        if (tl == tr - 1) {
            pos[tl] = v;
            tree[v] = a[tl];
            return;
        }
        int tm = (tl + tr) / 2;
        build(v * 2, tl, tm, a);
        build(v * 2 + 1, tm, tr, a);
        tree[v] = max(tree[v * 2], tree[v * 2 + 1]);
    }

    segment_tree(const vector<int> & a) {
        n = a.size();
        tree.assign(4 * n, 0);
        pos.resize(n);
        build(1, 0, n, a);
    }

    int get(int v, int tl, int tr, int l, int r, int k) {
        if (tl >= r || tr <= l) return -1;
        if (tree[v] < k) return -1;
        if (tl == tr - 1) return tl + 1;
        int tm = (tl + tr) / 2;
        int ans = get(v * 2, tl, tm, l, r, k);
        if (ans == -1)
            ans = get(v * 2 + 1, tm, tr, l, r, k);
        return ans;
    }

    int get(int l, int k) {
        return get(1, 0, n, l, n, k);
    }

    void upd(int v, int val) {
        v = pos[v];
        tree[v] = val;
        v /= 2;
        while (v) {
            tree[v] = max(tree[v * 2], tree[v * 2 + 1]);
            v /= 2;
        }
    }
};

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cout.precision(20);
    freopen("nearandmore.in", "r", stdin);
    freopen("nearandmore.out", "w", stdout);
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (auto &i : a)
        cin >> i;
    segment_tree tree(a);
    while (q--) {
        int type;
        cin >> type;
        if (type == 0) {
            int pos, val;
            cin >> pos >> val;
            pos--;
            tree.upd(pos, val);
        } else {
            int l, k;
            cin >> l >> k;
            l--;
            cout << tree.get(l, k) << "\n";
        }
    }
    return 0;
}
