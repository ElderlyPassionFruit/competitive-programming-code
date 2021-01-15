#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

struct node{
    int val, sz;
    int l, r;
    node() {
        val = 0;
        sz = 1;
        l = -1;
        r = -1;
    }
    node(int new_val) {
        val = new_val;
        sz = 1;
        l = -1;
        r = -1;
    }
};

int SZ = 0;
const int MAXN = 1e7;
node root[MAXN];

int clone(int tree) {
    int ans = SZ++;
    root[ans].val = root[tree].val;
    root[ans].sz = root[tree].sz;
    root[ans].l = root[tree].l;
    root[ans].r = root[tree].r;
    return ans;
}

int sz(int tree) {
    if (tree == -1) return 0;
    return root[tree].sz;
}

void upd(int tree) {
    if (tree == -1) return;
    root[tree].sz = sz(root[tree].l) + sz(root[tree].r) + 1;
}

mt19937 rnd(time(0) + 228 + 1337);

int merge(int L, int R) {
    if (L == -1) return R;
    if (R == -1) return L;
    if (rnd() % (sz(L) + sz(R)) < sz(L)) {
        L = clone(L);
        root[L].r = merge(root[L].r, R);
        upd(L);
        return L;
    } else {
        R = clone(R);
        root[R].l = merge(L, root[R].l);
        upd(R);
        return R;
    }
}

pair <int, int> split(int tree, int size) {
    if (tree == -1) return {-1, -1};
    tree = clone(tree);
    if (sz(root[tree].l) >= size) {
        auto p = split(root[tree].l, size);
        root[tree].l = p.second;
        upd(tree);
        return {p.first, tree};
    } else {
        auto p = split(root[tree].r, size - sz(root[tree].l) - 1);
        root[tree].r = p.first;
        upd(tree);
        return {tree, p.second};
    }
}

int get(int tree, int l, int r) {
    auto R = split(tree, r);
    auto L = split(R.first, l - 1);
    auto ans = L.second;
    R.first = merge(L.first, L.second);
    tree = merge(R.first, R.second);
    return ans;
}

int insert(int tree, int v, int l, int r) {
    auto R = split(tree, r);
    auto L = split(R.first, l - 1);
    L.second = v;
    R.first = merge(L.first, L.second);
    tree = merge(R.first, R.second);
    return tree;
}

vector<int> ans;

void make_ans(int tree) {
    if (tree == -1) return;
    make_ans(root[tree].l);
    ans.push_back(root[tree].val);
    make_ans(root[tree].r);
}

int tree = -1;

void rebuild() {
    ans.clear();
    make_ans(tree);
    tree = -1;
    SZ = 0;
    for (auto i : ans) {
        root[SZ] = node(i);
        int x = SZ;
        SZ++;
        tree = merge(tree, x);
    }
}

void wr() {
    ans.clear();
    make_ans(tree);
    for (auto i : ans)
        cout << i << " ";
    cout << endl;
}

struct event{
    int cnt, from, to;
    event() {}
};

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cout.precision(20);
    int n, m;
    cin >> n >> m;
    vector<event> q(m);
    for (auto &i : q)
        cin >> i.cnt >> i.from >> i.to;
    reverse(all(q));

    for (int i = 1; i <= n; i++) {
        root[SZ] = node(i);
        int x = SZ;
        SZ++;
        tree = merge(tree, x);
    }
    for (auto i : q) {
        tree = insert(tree, get(tree, i.to, i.to + i.cnt - 1), i.from, i.from + i.cnt - 1);
        if (SZ + 5000 > MAXN)
            rebuild();
    }
    wr();
    return 0;
}
