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
        tree[v] = tree[v * 2] + tree[v * 2 + 1];
    }

    segment_tree(const vector<int> & a) {
        n = a.size();
        tree.assign(4 * n, 0);
        pos.resize(n);
        build(1, 0, n, a);
    }

    int get_sum(int v, int tl, int tr, int l, int r) {
        if (tl >= r || tr <= l) return 0;
        if (tl >= l && tr <= r) return tree[v];
        int tm = (tl + tr) / 2;
        return get_sum(v * 2, tl, tm, l, r) + get_sum(v * 2 + 1, tm, tr, l, r);
    }

    int get(int v, int tl, int tr, int l, int r, int k) {
        if (tl >= r || tr <= l) return -1;
        if (tree[v] < k) return -1;
        if (tl == tr - 1) return tl + 1;
        int tm = (tl + tr) / 2;
        int ans = get(v * 2, tl, tm, l, r, k);
        if (ans == -1)
            ans = get(v * 2 + 1, tm, tr, l, r, k - get_sum(v * 2, tl, tm, l, r));
        return ans;
    }

    int get(int l, int r, int k) {
        return get(1, 0, n, l, r + 1, k);
    }

    void upd(int v, int val) {
        v = pos[v];
        tree[v] = val;
        v /= 2;
        while (v) {
            tree[v] = tree[v * 2] + tree[v * 2 + 1];
            v /= 2;
        }
    }
};

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cout.precision(20);
    freopen("kthzero.in", "r", stdin);
    freopen("kthzero.out", "w", stdout);
    int n, q;
    cin >> n;
    vector<int> a(n);
    for (auto &i : a) {
        cin >> i;
        if (i == 0) {
            i = 1;
        } else {
            i = 0;
        }
    }
    segment_tree tree(a);
    cin >> q;
    while (q--) {
        char type;
        cin >> type;
        if (type == 'u') {
            int pos, val;
            cin >> pos >> val;
            pos--;
            if (val == 0) {
                val = 1;
            } else {
                val = 0;
            }
            tree.upd(pos, val);
        } else {
            int l, r, k;
            cin >> l >> r >> k;
            l--;
            r--;
            cout << tree.get(l, r, k) << "\n";
        }
    }
    return 0;
}
