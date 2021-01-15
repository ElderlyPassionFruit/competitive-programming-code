#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

//#define int ll

const int MOD = 998244353;

//const int MOD = 1e10;

int add(int a, int b) {
    a += b;
    if (a >= MOD) return a - MOD;
    return a;
}

int sub(int a, int b) {
    a -= b;
    if (a < 0) return a + MOD;
    return a;
}

int mul(int a, int b) {
    return (ll) a * b % MOD;
}

const int N = 2e5 + 10;

int pows[N];
int pref[N];

void initPows() {
    pows[0] = 1;
    for (int i = 1; i < N; ++i) {
        pows[i] = mul(pows[i - 1], 10);
    }
    /*cout << "pows = " << endl;
    for (int i = 0; i < 10; ++i) {
        cout << pows[i] << " ";
    }
    cout << endl;*/
    pref[0] = 1;
    for (int i = 1; i < N; ++i) {
        pref[i] = add(pref[i], pref[i - 1]);
        pref[i] = add(pref[i], pows[i]);
    }
}

struct SegmentTree{
    int n;
    vector<int> tree;
    vector<int> mod;
    SegmentTree() {}

    int get(int val1, int val2, int sz2) {
        return add(mul(val1, pows[sz2]), val2);
    }

    void build(int v, int tl, int tr) {
        if (tl >= tr) return;
        if (tl == tr - 1) {
            tree[v] = 1;
            return;
        } 
        int tm = (tl + tr) / 2;
        build(v * 2, tl, tm);
        build(v * 2 + 1, tm, tr);
        tree[v] = get(tree[v * 2], tree[v * 2 + 1], tr - tm);
    }

    SegmentTree(int _n) {
        n = _n;
        tree.assign(4 * n, 0);
        mod.assign(4 * n, 0);
        //pos.assign(n, 0);
        //cout << "buildStart = " << endl;
        build(1, 0, n);
        //cout << "tree = " << endl;
        //for (auto i : tree) {
        //    cout << i << " ";
        //}
        //cout << endl;
        //cout << "buildOk" << endl;
    }

    /*
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
    }*/

    void push(int v) {
        if (!mod[v]) return;
        mod[v * 2] = mod[v];
        mod[v * 2 + 1] = mod[v];
        mod[v] = 0;
    }

    int getVal(int v, int sz) {
        if (!mod[v]) return tree[v];
        return mul(pref[sz - 1], mod[v]);
    }

    void upd(int v, int tl, int tr, int l, int r, int x) {
        if (tl >= r || tr <= l) return;
        //cout << "v = " << v << " tl = " << tl << " tr = " << tr << " l = " << l << " r = " << r << " x = " << x << endl;
        if (tl >= l && tr <= r) {
        //    cout << "tl = " << tl << " tr = " << tr << endl;
            mod[v] = x;
            return;
        }
        push(v);
        int tm = (tl + tr) / 2;
        upd(v * 2, tl, tm, l, r, x);
        upd(v * 2 + 1, tm, tr, l, r, x);
        //cout << "getVal(v * 2) = " << getVal(v * 2, tm - tl) << " getVal(v * 2 + 1) = " << getVal(v * 2 + 1, tr - tm) << endl;
        tree[v] = get(getVal(v * 2, tm - tl), getVal(v * 2 + 1, tr - tm), tr - tm);
    }

    int getAns() {
        return getVal(1, n);
    }

    void upd(int l, int r, int x) {
        upd(1, 0, n, l, r + 1, x);
    }

    /*
    void upd(int v, int val) {
        v = pos[v];
        chkmax(tree[v], val);
        v /= 2;
        while (v) {
            tree[v] = max(tree[v * 2], tree[v * 2 + 1]);
            v /= 2;
        }
    } */
};

int n, q;

void read() {
    cin >> n >> q;
}

void run() {
    SegmentTree tree(n);
    //cout << tree.getAns() << endl;
    //exit(0);
    while (q--) {
        int l, r, x;
        cin >> l >> r >> x;
        --l;
        --r;
        tree.upd(l, r, x);
        cout << tree.getAns() << "\n";
    }
}

void write() {

}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
    initPows();
    read();
    run();
    write();
    return 0;
}