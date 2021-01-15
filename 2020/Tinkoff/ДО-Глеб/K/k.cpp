#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(), (x).end()

#define int ll

struct segment_tree{
    vector<int> mod;
    int n;

    segment_tree() {}

    segment_tree(int _n) {
        n = _n;
        mod.assign(4 * n, -1);
    }

    void push(int v) {
        if (mod[v] == -1) return;
        mod[v * 2] = mod[v];
        mod[v * 2 + 1] = mod[v];
        mod[v] = -1;
    }

    int get_val(int v) {
        if (mod[v] == -1) return 0;
        return mod[v];
    }

    void upd(int v, int tl, int tr, int l, int r, int val) {
        if (tl >= r || tr <= l) return;
        if (tl >= l && tr <= r) {
            mod[v] = val;
            return;
        }
        push(v);
        int tm = (tl + tr) / 2;
        upd(v * 2, tl, tm, l, r, val);
        upd(v * 2 + 1, tm, tr, l, r, val);
    }

    void upd(int l, int r, int val) {
        upd(1, 0, n, l, r + 1, val);
    }

    int get(int v, int tl, int tr, int pos) {
        if (tl >= pos + 1 || tr <= pos) return -1;
        if (tl == tr - 1) return get_val(v);
        push(v);
        int tm = (tl + tr) / 2;
        return max(get(v * 2, tl, tm, pos), get(v * 2 + 1, tm, tr, pos));
    }

    int get(int pos) {
        return get(1, 0, n, pos);
    }
};

int readInt() {
    string s;
    cin >> s;
    int ans = 0;
    bool flag = false;
    for (auto i : s) {
        if (i == '.') {
            flag = true;
            continue;
        }
        ans *= 10;
        ans += i - '0';
    }
    if (!flag) {
        ans *= 2;
    } else {
        ans *= 2;
        ans /= 10;
    }
    return ans;
}

struct pt{
    int x, y, ind;
    pt() {}
    pt(int _x, int _y) {
        x = _x, y = _y;
    }
};

bool operator<(const pt & a, const pt & b) {
    return tie(a.x, a.y) < tie(b.x, b.y);
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int w, h, n;
    cin >> w >> h >> n;
    vector<pt> a(n);
    for (int i = 0; i < n; i++) {
        a[i].x = readInt(), a[i].y = readInt(), a[i].ind = i;
        swap(a[i].x, a[i].y);
    }
    sort(all(a));
    vector<int> coord;
    for (auto i : a) {
        coord.push_back(i.y);
    }
    sort(all(coord));
    coord.resize(unique(all(coord)) - coord.begin());
    segment_tree tree(coord.size());
    vector<int> ans(n);
    for (auto[x, y, ind] : a) {
        int pos_y = lower_bound(all(coord), y) - coord.begin();
        ans[ind] = x - tree.get(pos_y);
        int l = lower_bound(all(coord), y - ans[ind]) - coord.begin();
        int r = --upper_bound(all(coord), y + ans[ind]) - coord.begin();
        tree.upd(l, r, x + ans[ind]);
    }

    for (auto i : ans) {
        cout << i << "\n";
    }
    return 0;
}
