#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

mt19937 rnd(time(0));

struct Node{
    int l, r;
    int val;
    int sz;
    int prior;
    Node() {
        sz = 0;
    }
    Node(int _val) {
        val = _val;
        l = -1;
        r = -1;
        sz = 1;
        prior = rnd();
    }
};

const int MEM = 2e5 + 10;
Node tree[MEM];
int topQ = 0;

int sz(int v) {
    if (v == -1) return 0;
    return tree[v].sz;
}

void upd(int v) {
    if (v == -1) return;
    tree[v].sz = 1 + sz(tree[v].l) + sz(tree[v].r);
}

int merge(int L, int R) {
    if (L == -1) return R;
    if (R == -1) return L;
    if (tree[L].prior < tree[R].prior) {
        tree[L].r = merge(tree[L].r, R);
        upd(L);
        return L;
    } else {
        tree[R].l = merge(L, tree[R].l);
        upd(R);
        return R;
    }
}

pair<int, int> split(int root, int val) {
    if (root == -1) return {-1, -1};
    if (tree[root].val > val) {
        auto p = split(tree[root].l, val);
        tree[root].l = p.second;
        upd(root);
        return {p.first, root};
    } else {
        auto p = split(tree[root].r, val);
        tree[root].r = p.first;
        upd(root);
        return {root, p.second};
    }
}

int insert(int root, int v) {
    if (root == -1) return v;
    if (v == -1) return root;
    if (tree[v].prior < tree[root].prior) {
        auto p = split(root, tree[v].val);
        tree[v].l = p.first;
        tree[v].r = p.second;
        upd(v);
        return v;
    } else {
        if (tree[v].val < tree[root].val) {
            tree[root].l = insert(tree[root].l, v);
        } else {
            tree[root].r = insert(tree[root].r, v);
        }
        upd(root);
        return root;
    }
}

int Merge(int root, int forDel) {
    if (forDel == -1) return root;
    root = Merge(root, tree[forDel].l);
    root = Merge(root, tree[forDel].r);
    tree[forDel].l = -1;
    tree[forDel].r = -1;
    tree[forDel].sz = 1;
    root = insert(root, forDel);
    return root;
}

void wr(int root) {
    if (root == -1) return;
    wr(tree[root].l);
    cout << tree[root].val << endl;
    wr(tree[root].r);
}

int getR(int& root, int val) {
    auto p = split(root, val);
    int ans = sz(p.second);
    root = merge(p.first, p.second);
    return ans;
}


const int N = 2e5 + 10;
int n, root;
vector<int> g[N];

ll ansInv;
vector<int> ans[N];
int roots[N];

void calcInv(int& root, int v, ll& ans) {
    if (root == -1) return;
    if (v == -1) return;
    ans += getR(root, tree[v].val);
    calcInv(root, tree[v].l, ans);
    calcInv(root, tree[v].r, ans);
}

ll calcInv(int a, int b) {
    if (sz(roots[a]) < sz(roots[b])) {
        return (ll)sz(roots[a]) * sz(roots[b]) - calcInv(b, a);
    }
    ll ans = 0;
    calcInv(roots[a], roots[b], ans);
    return ans;
}

const int K = 7;
ll pairInv[K][K];
ll maskInv[1 << K][K];

void buildInv(int v) {
    int Sz = g[v].size();
    for (int i = 0; i < Sz; ++i) {
        for (int j = i + 1; j < Sz; ++j) {
            ll now = calcInv(g[v][i], g[v][j]);
            pairInv[i][j] = now;
            pairInv[j][i] = (ll)sz(roots[g[v][i]]) * (ll)sz(roots[g[v][j]]) - now;
        }
    }
    for (int mask = 0; mask < (1 << Sz); ++mask) {
        int firstBit = -1;
        for (int i = 0; i < Sz; ++i) {
            if ((mask >> i) & 1) {
                firstBit = i;
                break;
            }
        }
        for (int bit = 0; bit < Sz; ++bit) {
            if ((mask >> bit) & 1) continue;
            if (mask == 0) {
                maskInv[mask][bit] = 0;
            } else {
                maskInv[mask][bit] = pairInv[firstBit][bit] + maskInv[mask ^ (1 << firstBit)][bit];
            }
        }
    }
}

const ll INF = 1e18 + 228 + 1337;
ll dp[1 << K];
int par[1 << K];

void relax(int mask, ll inv, int last) {
    if (dp[mask] <= inv) return;
    dp[mask] = inv;
    par[mask] = last;
}

void calcDp(int v) {
    int sz = g[v].size();
    fill(dp, dp + (1 << sz), INF);
    dp[0] = 0;
    for (int mask = 1; mask < (1 << sz); ++mask) {
        for (int bit = 0; bit < sz; ++bit) {
            if (!((mask >> bit) & 1)) continue;
            relax(mask, dp[mask ^ (1 << bit)] + maskInv[mask ^ (1 << bit)][bit], bit);
        }
    }
}

void makeAns(int v) {
    int sz = g[v].size();
    int mask = (1 << sz) - 1;
    ansInv += dp[mask];
    while (mask) {
        ans[v].push_back(g[v][par[mask]]);
        mask ^= 1 << par[mask];
    }
    reverse(all(ans[v]));
}

void makeV(int v) {
    for (auto i : g[v]) {
        int add = getR(roots[i], v);
        ansInv += add;
    }
    roots[v] = topQ;
    tree[topQ++] = Node(v);
    for (auto i : g[v]) {
        if (sz(roots[i]) > sz(roots[v])) {
            swap(roots[i], roots[v]);
        }
        roots[v] = Merge(roots[v], roots[i]);
        
    }
}

void dfs(int v) {
    for (auto i : g[v]) {
        dfs(i);
    }
    buildInv(v);
    calcDp(v);
    makeAns(v);
    makeV(v);
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    cin >> n >> root;
    --root;
    for (int i = 0; i < n; ++i) {
        int sz;
        cin >> sz;
        g[i].resize(sz);
        for (auto& j : g[i]) {
            cin >> j;
            --j;
        }    
    }
    ansInv = 0;
    dfs(root);
    cout << ansInv << "\n";
    for (int i = 0; i < n; ++i) {
        cout << ans[i].size();
        for (auto j : ans[i]) {
            cout << " " << j + 1;
        }
        cout << "\n";
    }
	return 0;
}