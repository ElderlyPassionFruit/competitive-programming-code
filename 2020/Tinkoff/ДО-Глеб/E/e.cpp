#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(), (x).end()

struct segment_tree{
    vector<int> tree;
    vector<int> mod;
    int n;

    segment_tree() {}

    segment_tree(int _n) {
        n = _n;
        tree.assign(n * 4, 0);
        mod.assign(n * 4, 0);
    }

    void push(int v) {
        mod[v * 2] += mod[v];
        mod[v * 2 + 1] += mod[v];
        tree[v] += mod[v];
        mod[v] = 0;
    }

    int get_val(int v) {
        return tree[v] + mod[v];
    }

    int get() {
        return get_val(1);
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
        tree[v] = min(get_val(v * 2), get_val(v * 2 + 1));
    }

    void upd(int l, int val) {
        upd(1, 0, n, 0, l + 1, val);
    }
};

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cout.precision(20);
    int n;
    cin >> n;
    segment_tree A(n), B(n);
    for (int i = 0; i < n; i++) {
        int val, t;
        cin >> val >> t;
        val--;
        if (t == 1) {
            A.upd(val, 1);
            B.upd(val, -1);
        } else {
            A.upd(val, -1);
            B.upd(val, 1);
        }
        if (A.get() >= 0) {
            cout << ">" << "\n";
        } else if (B.get() >= 0) {
            cout << "<" << "\n";
        } else {
            cout << "?" << "\n";
        }
    }
    return 0;
}
