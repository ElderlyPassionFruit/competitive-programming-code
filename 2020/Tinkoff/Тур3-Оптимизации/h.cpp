#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int INF = 3e18;

struct line{
    int k, b;
    line() {
        k = 0, b = INF;
    }
    line(int x, int y) {
        k = x, b = y;
    }
};

double cross(line l, line m) {
    return (double) (l.b - m.b) / (m.k - l.k);
}

int eval(line l, int x) {
    return l.k * x + l.b;
}

struct cht{
    vector<line> l;
    vector<double> p;
    cht() {
        l = {};
        p = {};
    }

    void add(line x) {
        while (!p.empty() && p.back() >= cross(l.back(), x))
            p.pop_back(), l.pop_back();
        l.push_back(x);
        if (l.size() >= 2) {
            p.push_back(cross(l[l.size() - 1], l[l.size() - 2]));
        }
    }

    int get(int x) {
        int pos = lower_bound(p.begin(), p.end(), x) - p.begin();
        return eval(l[pos], x);
    }
};

bool operator<(line a, line b) {
    return tie(a.k, a.b) > tie(b.k, b.b);
}

struct segment_tree{
    vector<cht> tree;
    int n;
    segment_tree() {
        n = 0;
        tree = {};
    }

    void build(int v, int tl, int tr, vector<line> & a) {
        if (tl == tr - 1) {
            tree[v].add(a[tl]);
            return;
        }
        int tm = (tl + tr) / 2;
        build(v * 2, tl, tm, a);
        build(v * 2 + 1, tm, tr, a);
        vector<line> help(tree[v * 2].l.size() + tree[v * 2 + 1].l.size());
        merge(tree[v * 2].l.begin(), tree[v * 2].l.end(), tree[v * 2 + 1].l.begin(), tree[v * 2 + 1].l.end(), help.begin());
        for (auto i : help)
            tree[v].add(i);
    }

    segment_tree(vector<line> a) {
        n = a.size();
        tree.resize(n * 4);
        build(1, 0, n, a);
    }

    int get(int v, int tl, int tr, int l, int r, int x) {
        if (tl >= r || tr <= l) return INF;
        if (tl >= l && tr <= r) return tree[v].get(x);
        int tm = (tl + tr) / 2;
        return min(get(v * 2, tl, tm, l, r, x), get(v * 2 + 1, tm, tr, l, r, x));
    }

    int get(int l, int r, int x) {
        return get(1, 0, n, l, r + 1, x);
    }
};

const int MAXN = 2e5 + 10;
int n, m;
int s[MAXN], p[MAXN];

void read() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> s[i] >> p[i];
    }
}

segment_tree tree;
vector<line> a;

void build() {
    for (int i = 0; i < n; i++) {
        a.push_back(line(-2 * s[i], s[i] * s[i] + p[i]));
    }
    tree = segment_tree(a);
}

int get(int pos, vector<int> & cant) {
    int ans = INF;
    for (int i = 0; i < (int)cant.size() - 1; i++) {
        chkmin(ans, tree.get(cant[i] + 1, cant[i + 1] - 1, pos) + pos * pos);
    }
    return ans;
}

vector<int> ans;

void run() {
    build();
    for (int test = 0; test < m; test++) {
        int c, k;
        cin >> c >> k;
        vector<int> x(k);
        for (auto &i : x) {
            cin >> i;
            i--;
        }
        x.push_back(-1);
        x.push_back(n);
        sort(x.begin(), x.end());
        ans.push_back(get(c, x));
    }
}

void write() {
    for (auto i : ans)
        cout << i << endl;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    read();
    run();
    write();
    return 0;
}
