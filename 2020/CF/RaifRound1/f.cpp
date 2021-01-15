#include <bits/stdc++.h>

using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(a) a.begin(), a.end()

using namespace std;

template<typename T1, typename T2> inline void chkmin(T1& x, const T2& y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1& x, const T2& y) {if (x < y) x = y;}

int n;
string s;

void read() {
    cin >> n;
    cin >> s;
}

struct Node{
    ll sum;
    int minVal;
    int add;
    int setVal;
    Node() :sum(0), minVal(0), add(0), setVal(-1) {}
};

Node merge(const Node& a, const Node& b) {
    Node ans;
    ans.sum = a.sum + b.sum;
    ans.minVal = min(a.minVal, b.minVal);
    return ans;
}

struct SegmentTree{
    int n;
    vector<Node> tree;
    SegmentTree() {}
    SegmentTree(int _n) {
        n = _n;
        tree.assign(4 * n, Node());
    }

    Node getVal(int v, int tl, int tr) {
        if (tree[v].setVal != -1) {
            Node ans = tree[v];
            ans.sum = (ll)(tr - tl) * tree[v].setVal;
            ans.minVal = tree[v].setVal;
            ans.add = 0;
            ans.setVal = -1;
            return ans;
        } else if (tree[v].add) {
            Node ans = tree[v];
            ans.sum += (ll)(tr - tl) * tree[v].add;
            ans.minVal += tree[v].add;
            ans.add = 0;
            ans.setVal = -1;
            return ans;
        } else {
            return tree[v];
        }
    }

    void push(int v, int tl, int tr) {
        if (tl == tr - 1) {
            tree[v] = getVal(v, tl, tr);
            return;
        }
        if (tree[v].setVal != -1) {
            tree[v * 2].setVal = tree[v].setVal;
            tree[v * 2 + 1].setVal = tree[v].setVal;
            tree[v].setVal = -1;
        }
        if (tree[v].add) {
            tree[v * 2].add += tree[v].add;
            tree[v * 2 + 1].add += tree[v].add;
            tree[v].add = 0;
        }
        int tm = (tl + tr) / 2;
        tree[v] = merge(getVal(v * 2, tl, tm), getVal(v * 2 + 1, tm, tr));
    }

    void setSegm(int v, int tl, int tr, int l, int r, int x) {
        if (tl >= r || tr <= l) return;
        push(v, tl, tr);
        if (tl >= l && tr <= r) {
            tree[v].setVal = x;
            return;
        }
        int tm = (tl + tr) / 2;
        setSegm(v * 2, tl, tm, l, r, x);
        setSegm(v * 2 + 1, tm, tr, l, r, x);
        tree[v] = merge(getVal(v * 2, tl, tm), getVal(v * 2 + 1, tm, tr));
    }

    void setSegm(int l, int r, int x) {
        setSegm(1, 0, n, l, r + 1, x);
    }

    void addOne(int v, int tl, int tr, int l, int r) {
        if (tl >= r || tr <= l) return;
        push(v, tl, tr);
        if (tl >= l && tr <= r) {
            tree[v].add++;
            return;
        }
        int tm = (tl + tr) / 2;
        addOne(v * 2, tl, tm, l, r);
        addOne(v * 2 + 1, tm, tr, l, r);
        tree[v] = merge(getVal(v * 2, tl, tm), getVal(v * 2 + 1, tm, tr));
    }

    void addOne(int l, int r) {
        addOne(1, 0, n, l, r + 1);
    }
    
    int getFirstLess(int v, int tl, int tr, int r, int x) {
        if (tl >= r) return -1;
        push(v, tl, tr);
        if (tree[v].minVal >= x) return -1;
        if (tl == tr - 1) return tl;
        int tm = (tl + tr) / 2;
        int ans = getFirstLess(v * 2, tl, tm, r, x);
        if (ans == -1) {
            ans = getFirstLess(v * 2 + 1, tm, tr, r, x);
        }
        return ans;
    }

    int getFirstLess(int r, int x) {
        return getFirstLess(1, 0, n, r + 1, x);
    }

    ll getSum() {
        return getVal(1, 0, n).sum;
    }
};

ll ans;

void run() {
    ans = 0;
    SegmentTree tree(n);
    int now = 0;
    for (int i = 0; i < n; ++i) {
        if (s[i] == '0') {
            now = 0;
        } else {
            ++now;
            tree.addOne(i - now + 1, i);
            int pos = tree.getFirstLess(i - now, now);
            if (pos != -1) {
                tree.setSegm(pos, i - now, now);
            }
        }
        ans += tree.getSum();
    }
}

void write() {
    cout << ans << endl;
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.setf(ios::fixed), cout.precision(20);
    read();
    run();
    write();
    return 0;
}