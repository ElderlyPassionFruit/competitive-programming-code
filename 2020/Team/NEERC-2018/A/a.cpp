#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int N = 1e6 + 10;
int n;
int t[N], x[N], y[N];
int coord[N];
int topC = 0;

void compress() {
    for (int i = 0; i < n; ++i) {
        coord[topC++] = x[i];
        if (t[i] == 1) {
            coord[topC++] = x[i] + y[i];
            coord[topC++] = x[i] - y[i];
        }
    }
    sort(coord, coord + topC);
    topC = unique(coord, coord + topC) - coord;
}

int getCoord(int x) {
    return lower_bound(coord, coord + topC, x) - coord;
}

bool check(int ind, int my_x, int my_y) {
    return (ll)(x[ind] - my_x) * (x[ind] - my_x) + (ll) (y[ind] - my_y) * (y[ind] - my_y) < (ll) y[ind] * y[ind];
}

namespace SegmentTree{
    set<int> tree[4 * N];
    int n;

    void init(int _n) {
        n = _n;
    }

    void add(int v, int tl, int tr, int l, int r, int x) {
        if (tl >= r || tr <= l) return;
        if (tl >= l && tr <= r) {
            tree[v].insert(x);
            return;
        }
        int tm = (tl + tr) / 2;
        add(v * 2, tl, tm, l, r, x);
        add(v * 2 + 1, tm, tr, l, r, x);
    }

    void add(int l, int r, int x) {
        add(1, 0, n, l, r + 1, x);
    }

    void del(int v, int tl, int tr, int l, int r, int x) {
        if (tl >= r || tr <= l) return;
        if (tl >= l && tr <= r) {
            tree[v].erase(x);
            return;
        }
        int tm = (tl + tr) / 2;
        del(v * 2, tl, tm, l, r, x);
        del(v * 2 + 1, tm, tr, l, r, x);
    }

    void del(int l, int r, int x) {
        del(1, 0, n, l, r + 1, x);
    }

    int getAns(int v, int tl, int tr, int pos, int x, int y) {
        if (tl >= pos + 1 || tr <= pos) return -1;
        for (auto ind : tree[v]) {
            if (check(ind, x, y)) {
                return ind;
            }
        }
        if (tl == tr - 1) return -1;
        int tm = (tl + tr) / 2;
        int ans = getAns(v * 2, tl, tm, pos, x, y);
        if (ans == -1) {
            ans = getAns(v * 2 + 1, tm, tr, pos, x, y);
        }
        return ans;
    }

    int getAns(int pos, int x, int y) {
        return getAns(1, 0, n, pos, x, y);
    }
};

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> t[i] >> x[i] >> y[i];
    }
    compress();
    SegmentTree::init(topC);
    for (int i = 0; i < n; ++i) {
        if (t[i] == 1) {
            int l = getCoord(x[i] - y[i]);
            int r = getCoord(x[i] + y[i]);
            SegmentTree::add(l, r, i);
        } else {
            int pos = getCoord(x[i]);
            int ans = SegmentTree::getAns(pos, x[i], y[i]);
            if (ans != -1) {
                int l = getCoord(x[ans] - y[ans]);
                int r = getCoord(x[ans] + y[ans]);
                SegmentTree::del(l, r, ans);   
                ++ans;
            }
            cout << ans << '\n';
        }
    }
	return 0;
}