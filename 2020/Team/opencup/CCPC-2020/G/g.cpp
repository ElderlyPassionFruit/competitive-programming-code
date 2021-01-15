#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

//#define int ll

const int N = 5e5 + 10;
//const int N = 1000;
const int BASE = 65536;

namespace SegmentTreeMax{
    pair<int, int> tree[N * 4];
    int mod[N * 4];
    int n;

    void build(int v, int tl, int tr, const vector<int>& a) {
        if (tl >= tr) return;
        if (tl == tr - 1) {
            tree[v] = {a[tl], tl};
            return;
        }
        int tm = (tl + tr) / 2;
        build(v * 2, tl, tm, a);
        build(v * 2 + 1, tm, tr, a);
        tree[v] = max(tree[v * 2], tree[v * 2 + 1]);    
    }

    void init(const vector<int>& a) {
        n = a.size();
        fill(tree, tree + n * 4, make_pair(0, 0));
        fill(mod, mod + n * 4, 0);
        build(1, 0, n, a);
    }

    void push(int v) {
        mod[v * 2] += mod[v];
        mod[v * 2 + 1] += mod[v];
        mod[v] = 0;
    }

    pair<int, int> getVal(int v) {
        return {tree[v].first + mod[v], tree[v].second};
    }

    void upd(int v, int tl, int tr, int l, int r, int add) {
        if (tl >= r || tr <= l) return;
        if (tl >= l && tr <= r) {
            mod[v] += add;
            return;
        }
        push(v);
        int tm = (tl + tr) / 2;
        upd(v * 2, tl, tm, l, r, add);
        upd(v * 2 + 1, tm, tr, l, r, add);
        tree[v] = max(getVal(v * 2), getVal(v * 2 + 1));
    }

    void addOne(int l, int r) {
        upd(1, 0, n, l, r + 1, 1);
    }

    void setZero(int pos) {
        upd(1, 0, n, pos, pos + 1, -BASE);
    }

    pair<int, int> getMax() {
        return getVal(1);
    }
};

mt19937 rnd(time(0));

namespace SegmentTreeHash{
    const int MOD[2] = {998244353, (int)1e9 + 7};
    const int base[2] = {(int)rnd() % 228 + 1337, (int)rnd() % 228 + 1337};
    int pows[2][N];
    int pref[2][N];

    int getMod(int x, int it) {
        while (x < 0) {
            x += MOD[it];
        } 
        while (x >= MOD[it]) {
            x -= MOD[it];
        }
        return x;
    }

    int mul(int a, int b, int it) {
        a = getMod(a, it);
        b = getMod(b, it);
        return (ll) a * b % MOD[it];
    }

    int add(int a, int b, int it) {
        a = getMod(a, it);
        b = getMod(b, it);
        a += b;
        if (a >= MOD[it]) {
            return a - MOD[it];
        }
        return a;
    } 

    int sub(int a, int b, int it) {
        a = getMod(a, it);
        b = getMod(b, it);
        a -= b;
        if (a < 0) {
            return a + MOD[it];
        }
        return a;
    }

    struct Node{
        int sz;
        int hash[2];
        Node() {
            sz = 0;
            hash[0] = hash[1] = 0;
        }
        Node(int a) {
            sz = 1;
            hash[0] = hash[1] = a;
        }
    };

    bool operator==(const Node& a, const Node& b) {
        return a.hash[0] == b.hash[0] && a.hash[1] == b.hash[1];
    }

    Node merge(const Node& a, const Node& b) {
        if (!a.sz) return b;
        if (!b.sz) return a;
        Node ans;
        ans.sz = a.sz + b.sz;
        for (int it = 0; it < 2; ++it) {
            ans.hash[it] = add(mul(a.hash[it], pows[it][b.sz], it), b.hash[it], it);
        }
        return ans;
    }

    Node tree[N * 4];
    int mod[N * 4];
    int n;

    void build(int v, int tl, int tr, const vector<int>& a) {
        if (tl >= tr) return;
        if (tl == tr - 1) {
            tree[v] = Node(a[tl]);
            return;
        }
        int tm = (tl + tr) / 2;
        build(v * 2, tl, tm, a);
        build(v * 2 + 1, tm, tr, a);
        tree[v] = merge(tree[v * 2], tree[v * 2 + 1]);
    }

    void init(const vector<int>& a) {
        for (int it = 0; it < 2; ++it) {
            pows[it][0] = 1;
            pref[it][0] = 1;
            for (int i = 1; i < N; ++i) {
                pows[it][i] = mul(pows[it][i - 1], base[it], it);
                pref[it][i] = add(pref[it][i - 1], pows[it][i], it);
            }
        }
        n = a.size();
        fill(mod, mod + n * 4, 0);
        build(1, 0, n, a);
    }

    void push(int v) {
        mod[v * 2] += mod[v];
        mod[v * 2 + 1] += mod[v];
        mod[v] = 0;
    }

    Node getVal(int v) {
        Node ans = tree[v];
        for (int it = 0; it < 2; ++it) {
            ans.hash[it] = add(ans.hash[it], mul(pref[it][ans.sz - 1], mod[v], it), it);
        }
        return ans;
    }

    void upd(int v, int tl, int tr, int l, int r, int add) {
        if (tl >= r || tr <= l) return;
        if (tl >= l && tr <= r) {
            mod[v] += add;
            return;
        }
        push(v);
        int tm = (tl + tr) / 2;
        upd(v * 2, tl, tm, l, r, add);
        upd(v * 2 + 1, tm, tr, l, r, add);
        tree[v] = merge(getVal(v * 2), getVal(v * 2 + 1));
    }

    void addOne(int l, int r) {
        upd(1, 0, n, l, r + 1, 1);
    }

    void setZero(int pos) {
        upd(1, 0, n, pos, pos + 1, -BASE);
    }

    Node get(int v, int tl, int tr, int l, int r) {
        if (tl >= r || tr <= l) return Node();
        if (tl >= l && tr <= r) return getVal(v);
        push(v);
        int tm = (tl + tr) / 2;
        Node ans = merge(get(v * 2, tl, tm, l, r), get(v * 2 + 1, tm, tr, l, r));
        tree[v] = merge(getVal(v * 2), getVal(v * 2 + 1));
        return ans;
    }

    bool check(int x, int y, int len) {
        return get(1, 0, n, x, x + len) == get(1, 0, n, y, y + len);
    }
};

int n, q;
vector<int> a;    

void relax() {
    while (true) {
        auto have = SegmentTreeMax::getMax();
        if (have.first < BASE) return;
        SegmentTreeMax::setZero(have.second);
        SegmentTreeHash::setZero(have.second);
    }
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    cin >> n >> q;
    a.resize(n);
    for (auto &i : a) {
        cin >> i;
    }
    SegmentTreeMax::init(a);
    SegmentTreeHash::init(a);
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int l, r;
            cin >> l >> r;
            --l;
            --r;
            SegmentTreeMax::addOne(l, r);
            SegmentTreeHash::addOne(l, r);
            relax();
        } else {
            int x, y, len;
            cin >> x >> y >> len;
            --x;
            --y;
            cout << (SegmentTreeHash::check(x, y, len) ? "yes\n" : "no\n");
        }
    }
	return 0;
}