#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(), (x).end()
#define int ll
const int INF = 1e9 + 10;

struct node{
    int val, sum, mod;
    node() {
        val = INF, sum = 0, mod = 0;
    }
    node(int x) {
        val = 0;
        mod = 0;
        sum = x;
    }
};

node merge(const node & a, const node & b) {
    if (a.val < b.val) return a;
    if (a.val > b.val) return b;
    node ans;
    ans.val = a.val;
    ans.sum = a.sum + b.sum;
    ans.mod = 0;
    return ans;
}

struct segment_tree{
    vector<node> tree;
    int n;
    segment_tree() {}

    void build(int v, int tl, int tr, const vector<int> & a) {
        if (tl == tr - 1) {
            tree[v] = node(a[tl]);
            return;
        }
        int tm = (tl + tr) / 2;
        build(v * 2, tl, tm, a);
        build(v * 2 + 1, tm, tr, a);
        tree[v] = merge(tree[v * 2], tree[v * 2 + 1]);
    }

    segment_tree(const vector<int> & a) {
        n = a.size();
        tree.resize(4 * n);
        build(1, 0, n, a);
    }

    void push(int v) {
        tree[v * 2].mod += tree[v].mod;
        tree[v * 2 + 1].mod += tree[v].mod;
        tree[v].val += tree[v].mod;
        tree[v].mod = 0;
    }

    node get_val(int v) {
        node ans = tree[v];
        ans.val += ans.mod;
        ans.mod = 0;
        return ans;
    }

    void upd(int v, int tl, int tr, int l, int r, int val) {
        if (tl >= r || tr <= l) return;
        if (tl >= l && tr <= r) {
            tree[v].mod += val;
            return;
        }
        push(v);
        int tm = (tl + tr) / 2;
        upd(v * 2, tl, tm, l, r, val);
        upd(v * 2 + 1, tm, tr, l, r, val);
        tree[v] = merge(get_val(v * 2), get_val(v * 2 + 1));
    }

    void upd(int l, int r, int val) {
        upd(1, 0, n, l, r, val);
    }

    node get() {
        return get_val(1);
    }
};

struct event{
    int pos, l, r, type;
    event() {}
    event(int _pos, int _l, int _r, int _type) {
        pos = _pos, l = _l, r = _r, type = _type;
    }
};

bool operator<(const event & a, const event & b) {
    return a.pos < b.pos;
}

int n;
vector<event> a;

void read() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        if (x1 > x2) swap(x1, x2);
        if (y1 > y2) swap(y1, y2);
        x2++;
        y1--;
        a.push_back({x1, y1, y2, 1});
        a.push_back({x2, y1, y2, -1});
    }
}

vector<int> coord;
segment_tree tree;
int full;

void build() {
    sort(all(a));
    for (auto i : a) {
        coord.push_back(i.l), coord.push_back(i.r);
    }
    sort(all(coord));
    coord.resize(unique(all(coord)) - coord.begin());
    for (auto &i : a) {
        i.l = lower_bound(all(coord), i.l) - coord.begin();
        i.r = lower_bound(all(coord), i.r) - coord.begin();
    }
    full = coord.back() - coord[0];
    vector<int> have = coord;
    for (int i = (int)coord.size() - 1; i > 0; i--) {
        have[i] -= have[i - 1];
    }
    have.erase(have.begin());
    tree = segment_tree(have);
}

ll ans;

void run() {
    ans = 0;
    build();
    int last = a[0].pos;
    int l = 0, r = 0;
    while (l < (int)a.size()) {
        node have = tree.get();
        int len = full - (int)(have.val == 0) * have.sum;
        ans += (a[l].pos - last) * len;
        while (r < (int)a.size() && a[l].pos == a[r].pos) {
            tree.upd(a[r].l, a[r].r, a[r].type);
            r++;
        }
        last = a[l].pos;
        l = r;
    }
}

void write() {
    cout << ans << endl;
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cout.precision(20);
    read();
    run();
    write();
    return 0;
}
