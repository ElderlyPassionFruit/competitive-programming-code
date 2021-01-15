#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(), (x).end()

struct segment_tree{
    vector<pair<int, int>> tree;
    int n;
    segment_tree() {}

    void build(int v, int tl, int tr, const vector<int> & a) {
        if (tl == tr - 1) {
            tree[v] = {a[tl], tl + 1};
            return;
        }
        int tm = (tl + tr) / 2;
        build(v * 2, tl, tm, a);
        build(v * 2 + 1, tm, tr, a);
        tree[v] = max(tree[v * 2], tree[v * 2 + 1]);
    }

    segment_tree(const vector<int> & a) {
        n = a.size();
        tree.resize(4 * n);
        build(1, 0, n, a);
    }

    pair<int, int> get(int v, int tl, int tr, int l, int r) {
        if (tl >= r || tr <= l) return {0, 0};
        if (tl >= l && tr <= r) return tree[v];
        int tm = (tl + tr) / 2;
        return max(get(v * 2, tl, tm, l, r), get(v * 2 + 1, tm, tr, l, r));
    }

    int get(int l, int r) {
        return get(1, 0, n, l, r + 1).second;
    }
};

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cout.precision(20);
    freopen("index-max.in", "r", stdin);
    freopen("index-max.out", "w", stdout);
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &i : a)
        cin >> i;
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
