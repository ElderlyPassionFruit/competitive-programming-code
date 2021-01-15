#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

#define int ll

struct Edge{
    int to, cap, cost;
};

const int N = 2e5 + 10;
int n, q;
int a[N];
int myCost[N];
vector<Edge> g[N];

int sz[N], nxt[N], h[N], par[N];

pair<ll, vector<ll>> del(ll a, ll b){
    ll z = a / b;
    a %= b;
    vector<ll> ans;
    for (int i = 0; i < 30; ++i){
        a *= 10;
        ans.push_back(a / b);
        a %= b;
    }
    return {z, ans};
}

void dfsSz(int v, int p) {
    par[v] = p;
    sz[v] = 1;
    nxt[v] = -1;
    for (auto i : g[v]) {
        if (i.to == p) continue;
        h[i.to] = h[v] + 1;
        dfsSz(i.to, v);
        sz[v] += sz[i.to];
        if (nxt[v] == -1 || sz[nxt[v]] < sz[i.to]) {
            nxt[v] = i.to;
        }
    }
}

int pos[N], pathPar[N], pathSz[N];
int cntPath = 0, timer = 0; 

void dfsOrder(int v, int p) {
    pos[v] = timer++;
    if (!pathSz[cntPath]) {
        pathPar[v] = v; 
    } else {
        pathPar[v] = pathPar[par[v]];
    }
    pathSz[cntPath]++;

    if (nxt[v] != -1) {
        dfsOrder(nxt[v], v);
    }
    
    for (auto i : g[v]) {
        if (i.to == p) continue;
        if (i.to == nxt[v]) continue;
        cntPath++;
        dfsOrder(i.to, v);
    }
}

const ld INF = 1e18;

struct SegmentTree{
    int n;
    vector<ll> tree;
    vector<ll> mod;
    SegmentTree() {}

    void build(int v, int tl, int tr, const vector<ll>& a) {
        if (tl >= tr) return;
        if (tl == tr - 1) {
            tree[v] = a[tl];
            return;
        }
        int tm = (tl + tr) / 2;
        build(v * 2, tl, tm, a);
        build(v * 2 + 1, tm, tr, a);
        tree[v] = min(tree[v * 2], tree[v * 2 + 1]);
    }

    SegmentTree(const vector<ll>& a) {
        n = a.size();
        tree.assign(4 * n, INF);
        mod.assign(4 * n, 0);
        build(1, 0, n, a);
    }

    void push(int v) {
        mod[v * 2] += mod[v];
        mod[v * 2 + 1] += mod[v];
        mod[v] = 0;
    }

    ld getVal(int v) {
        return tree[v] + mod[v];
    }

    void upd(int v, int tl, int tr, int l, int r, ll x) {
        if (tl >= r || tr <= l) return;
        if (tl >= l && tr <= r) {
            mod[v] += x;
            return;
        }
        int tm = (tl + tr) / 2;
        push(v);
        upd(v * 2, tl, tm, l, r, x);
        upd(v * 2 + 1, tm, tr, l, r, x);
        tree[v] = min(getVal(v * 2), getVal(v * 2 + 1));
    } 

    void upd(int l, int r, ll x) {
        upd(1, 0, n, l, r + 1, x);
        //for (int i = l; i <= r; ++i) {
        //    tree[i] += x;
        //}
    }

    ll get(int v, int tl, int tr, int l, int r) {
        if (tl >= r || tr <= l) return INF;
        if (tl >= l && tr <= r) return getVal(v);
        int tm = (tl + tr) / 2;
        push(v);
        ll ans = min(get(v * 2, tl, tm, l, r), get(v * 2 + 1, tm, tr, l, r));
        tree[v] = min(getVal(v * 2), getVal(v * 2 + 1));
        return ans; 
    }

    ll get(int l, int r) {
        return get(1, 0, n, l, r + 1);
        //ld ans = INF;
        //for (int i = l; i <= r; ++i) {
        //    chkmin(ans, tree[i]);
        //}
        //return ans;
    }
};

SegmentTree tree;

void build() {
    dfsSz(0, 0);
    dfsOrder(0, 0);
    vector<ll> now(n);
    for (int i = 0; i < n; i++) {
        now[pos[i]] = a[i];
    }
    tree = SegmentTree(now);
}

void upd(int v, ll x) {
    int u = 0;
    while (pathPar[u] != pathPar[v]) {
        if (h[pathPar[u]] > h[pathPar[v]]) {
            swap(u, v);
        }
        tree.upd(pos[pathPar[v]], pos[v], x);
        v = par[pathPar[v]];
    }
    if (h[u] > h[v]) swap(u, v);
    tree.upd(pos[u], pos[v], x);
}

ll get(int u, int v) {
    ll ans = INF;
    while (pathPar[u] != pathPar[v]) {
        if (h[pathPar[u]] > h[pathPar[v]]) {
            swap(u, v);
        }
        chkmin(ans, tree.get(pos[pathPar[v]], pos[v]));
        v = par[pathPar[v]];
    }
    if (h[u] > h[v]) swap(u, v);
    chkmin(ans, tree.get(pos[u], pos[v]));
    return ans;
}

vector<int> fans;

void dfsPrecalc(int v, int p) {
    if (v != p && g[v].size() == 1) {
        fans.push_back(v);
    }
    for (auto i : g[v]) {
        if (i.to == p) continue;
        myCost[i.to] = myCost[v] + i.cost;
        a[i.to] = i.cap;
        dfsPrecalc(i.to, v);
    }
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
    cin >> n;
    for (int i = 0; i < n - 1; ++i) {
        int u, v, cap, cost;
        cin >> u >> v >> cap >> cost;
        --u;
        --v;
        g[u].push_back({v, cap, cost});
        g[v].push_back({u, cap, cost});
    }
    a[0] = INF;
    dfsPrecalc(0, 0);
    build();
    sort(all(fans), [&] (int a, int b) {
        return myCost[a] < myCost[b];
    });
    ll ans = 0;
    ll sumCost = 0;
    for (auto v : fans) {
        ll nowCost = myCost[v];
        ll myCap = get(v, 0);
        //cout << "v = " << v << " nowCost = " << nowCost << " myCap = " << myCap << endl;
        if (nowCost <= 0 || nowCost * myCap <= sumCost) {
            ans += myCap;
            sumCost -= myCap * nowCost;
            upd(v, -myCap);
        } else {
            //cout << ans + (ld)sumCost / nowCost << "\n";
            auto res = del(sumCost, nowCost);
            ans += res.first;
            cout << ans << ".";
            for (auto elem : res.second)
                cout << elem;
            cout << "\n";
            exit(0);
        }
    }
    cout << ans << endl;
    return 0;
}