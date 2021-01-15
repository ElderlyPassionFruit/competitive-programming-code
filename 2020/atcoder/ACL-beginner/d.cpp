#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

const int N = 3e5 + 10;

int n, k;
int a[N];

void read() {
    cin >> n >> k;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
}

struct SegmentTree{
    int n;
    vector<int> tree;
    SegmentTree() {}
    vector<int> pos;

    void build(int v, int tl, int tr) {
        if (tl >= tr) return;
        if (tl == tr - 1) {
            pos[tl] = v;
            return;
        } 
        int tm = (tl + tr) / 2;
        build(v * 2, tl, tm);
        build(v * 2 + 1, tm, tr);
    }

    SegmentTree(int _n) {
        n = _n;
        tree.assign(4 * n, 0);
        pos.assign(n, 0);
        //cout << "buildStart = " << endl;
        build(1, 0, n);
        //cout << "buildOk" << endl;
    }

    int get(int v, int tl, int tr, int l, int r) {
        if (tl >= r || tr <= l) return 0;
        if (tl >= l && tr <= r) return tree[v];
        int tm = (tl + tr) / 2;
        return max(get(v * 2, tl, tm, l, r), get(v * 2 + 1, tm, tr, l, r)); 
    }

    int get(int l, int r) {
        l = max(0, l);
        r = min(n - 1, r);
        return get(1, 0, n, l, r + 1);
    }

    void upd(int v, int val) {
        v = pos[v];
        chkmax(tree[v], val);
        v /= 2;
        while (v) {
            tree[v] = max(tree[v * 2], tree[v * 2 + 1]);
            v /= 2;
        }
    } 
};

int ans;

void run() {
    SegmentTree tree(N);
    for (int i = 0; i < n; ++i) {
        int now = tree.get(a[i] - k, a[i] + k);
        tree.upd(a[i], now + 1);
    }
    ans = tree.get(0, N - 1);
}

void write() {
    cout << ans << endl;
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
    read();
    run();
    write();
    return 0;
}