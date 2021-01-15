#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

#define int ll

const int INF = -1e18;

struct SegmentTree{
    int n;
    vector<int> tree, mod;
    SegmentTree() {}
    
    void push(int v) {
        mod[v * 2] += mod[v];
        mod[v * 2 + 1] += mod[v];
        mod[v] = 0;
    }

    int getVal(int v) {
        return tree[v] + mod[v];
    }

    void upd(int v, int tl, int tr, int l, int r, int x) {
        if (tl >= r || tr <= l) return;
        if (tl >= l && tr <= r) {
            mod[v] += x;
            return;
        }
        push(v);
        int tm = (tl + tr) / 2;
        upd(v * 2, tl, tm, l, r, x);
        upd(v * 2 + 1, tm, tr, l, r, x);
        tree[v] = max(getVal(v * 2), getVal(v * 2 + 1));
    }

    void upd(int l, int r, int x) {
        if (l > r) return;
        upd(1, 0, n, l, r + 1, x);
        /*for (int i = l; i <= r; ++i) {
            tree[i] += x;
        }*/
    }

    void upd(int pos, int x) {
        upd(pos, pos, x);
    }

    int get(int v, int tl, int tr, int l, int r) {
        if (tl >= r || tr <= l) return INF;
        if (tl >= l && tr <= r) return getVal(v);
        push(v);
        int tm = (tl + tr) / 2;
        int ans = max(get(v * 2, tl, tm, l, r), get(v * 2 + 1, tm, tr, l, r));
        tree[v] = max(getVal(v * 2), getVal(v * 2 + 1));
        return ans;
    }

    int get(int r) {
        return get(1, 0, n, 0, r + 1);
        /*int ans = 0;
        for (int i = 0; i <= r; ++i) {
            ans = max(ans, tree[i]);
        }
        return ans;*/
    }

    SegmentTree(vector<int>& a, vector<int>& b) {
        n = a.size();
        tree.assign(n * 4, 0);
        mod.assign(n * 4, 0);
        for (int i = 0; i < n; ++i) {
            upd(i, i, a[i]);
            upd(0, i - 1, b[i]);
        }
    }

    /*void write() {
        cout << "segTree = " << endl;
        for (auto i : tree) {
            cout << i << " ";
        }
        cout << endl;
    }*/
};

struct Fenwick{
    int n;
    vector<int> tree;
    Fenwick() {}

    void upd(int pos, int val) {
        pos = n - 1 - pos;
        /*for (int i = pos; i < n; ++i) {
            tree[i] += val;
        }*/
        //tree[pos] += val;
        for (; pos < n; pos |= pos + 1) {
            tree[pos] += val;
        }
    }

    Fenwick(vector<int>& b) {
        n = b.size();
        tree.assign(n, 0);
        for (int i = 0; i < n; ++i) {
            upd(i, b[i]);
        }
    }

    int get(int r) {
        r = n - 1 - r;
        int ans = 0;
        /*for (int i = 0; i <= r; ++i) {
            ans += tree[i];
        }*/
        for (; r >= 0; r = (r & (r + 1)) - 1) {
            ans += tree[r];
        }
        return ans;
    }

    /*void write() {
        cout << "fenwick = " << endl;
        for (auto i : tree) {
            cout << i << " ";
        }
        cout << endl;
    }*/
};

int n, m;
vector<int> a;
vector<int> b;

void solve() {
    a.resize(n);
    b.resize(n);
    for (auto& i : a) {
        cin >> i;
    }
    for (auto& i : b) {
        cin >> i;
    }
    SegmentTree tree(a, b);
    Fenwick suff(b);
    //tree.write();
    //suff.write();
    while (m--) {
        int t;
        cin >> t;
        if (t == 1) {
            int pos, val;
            cin >> pos >> val;
            --pos;
            tree.upd(pos, val - a[pos]);
            a[pos] = val;
        } else if (t == 2) {
            int pos, val;
            cin >> pos >> val;
            --pos;
            tree.upd(0, pos - 1, val - b[pos]);
            suff.upd(pos, val - b[pos]);
            b[pos] = val;
        } else if (t == 3) {
            int pos;
            cin >> pos;
            --pos;
            int ans = INF;
            ans = max(ans, tree.get(pos) - suff.get(pos + 1));
            ans = max(ans, suff.get(0) - suff.get(pos + 1));
            cout << ans << "\n";
        } else {
            assert(false);
        }
    }
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    while (cin >> n >> m) {
        solve();
    }
	return 0;
}