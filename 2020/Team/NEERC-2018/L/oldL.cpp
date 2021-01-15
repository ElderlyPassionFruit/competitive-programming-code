#include <bits/stdc++.h>

#define f first
#define s second
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
#define ll long long
#define ull unsigned long long
#define db double
#define ld long double
#define pii pair<int, int>
#define pil pair<int, ll>
#define pli pair<ll, int>
#define pll pair<ll, ll>
#define px pair<db, db>
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define input(a) for (auto& el : a) cin >> el;
#define output(a) cout << '!'; for (auto& el : a) cout << el << ' '; cout << '\n'; cout.flush();
#define sz(el) int(el.size())
#define sq(a) ((a) * (a))
#define xll __int128
#define xmin(a,b) a = min(a, b)
#define xmax(a,b) a = max(a, b)
#define sun(a) sort(all(a)); a.resize(unique(all(a)) - a.begin());

using namespace std;

template <class T1, class T2>
ostream& operator<<(ostream& out, const pair<T1, T2>& p) {
    return (out << p.f << ' ' << p.s << endl);
}

const int INF = 1000000017;
const ll LLINF = 1000000000000000017LL;
const ld inf = 1.0 / 0.0;
const ld eps = 1e-9;
const int MOD = 1e9 + 7;
const int MOD2 = 1e9 + 9;

//mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

//uniform_int_distribution<int> uid(l, r); [l, r]
//int x = uid(rng);

/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> tret;

/// *find_by_order - val by index, order_of_key - # less than x
*/

const int N = 1e5 + 7, LOGN = 18;

int t[N];

void add(int _x, int val) {
    for (int x = _x; x < N; x |= (x + 1)) {
        t[x] += val;
    }
}

int get(int _x) {
    int res = 0;
    for (int x = _x; x >= 0; x = (x & (x + 1)) - 1) {
        res += t[x];
    }
    return res;
}

int get(int l, int r) {
    return get(r) - get(l - 1);
}

vector<int> g[N];
int tin[N], tout[N];
int T = -1;

int up[N][LOGN];
void dfs_help(int v, int p = 0) {
    tin[v] = ++T;
    up[v][0] = p;
    for (int k = 1; k < LOGN; ++k) {
        up[v][k] = up[up[v][k - 1]][k - 1];
    }
    for (int u : g[v]) {
        if (u != p)
            dfs_help(u, v);
    }
    tout[v] = T;
}

bool is_p(int u, int v) {
    return !u || (tin[u] <= tin[v] && tout[u] >= tout[v]);
}

int lca(int u, int v) {
    if (is_p(u, v)) {
        return u;
    }
    if (is_p(v, u)) {
        return v;
    }
    for (int k = LOGN - 1; k >= 0; --k) {
        if (!is_p(up[u][k], v)) {
            u = up[u][k];
        }
    }
    return up[u][0];
}

ll cnt = 0;
vector<int> path[N];
void dfs(int v, int p = 0) {
    for (int u : path[v]) {
        add(tin[u], 1);
        //cout << '!' << tin[u] << endl;
    }

    //cout << '&' << cnt << endl;
    cnt += 1ll * get(tin[v], tin[v]) * sz(path[v]);
    //cout << v << ' ' << tin[v] << ' ' << cnt << endl;

    ll s = 0;
    vector<int> tmp;
    for (int u : g[v]) {
        if (u != p) {
            dfs(u, v);
            tmp.eb(get(tin[u], tout[u]));
            s += tmp.back();
        }
    }
    reverse(all(tmp));

    ll cur = 0;
    for (int u : g[v]) {
        if (u != p) {
            cur += 1ll * (s - tmp.back()) * tmp.back();
            tmp.pop_back();
        }
    }

    cnt += (cur >> 1);

    for (int u : path[v]) {
        add(tin[u], -1);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, f;
    cin >> n >> f;
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].eb(v);
        g[v].eb(u);
    }

    dfs_help(1);

    for (int i = 0; i < f; ++i) {
        int u, v;
        cin >> u >> v;
        if (u == v) {
            continue;
        }
        int w = lca(u, v);
        //cout << tin[u] << ' ' << tout[u] << endl;
        //cout << tin[v] << ' ' << tout[v] << endl;
        //cout << u << ' ' << v << ' ' << w << endl;
        if (w == u) {
            path[u].eb(v);
        } else if (w == v) {
            path[v].eb(u);
        } else {
            --cnt;
            path[w].eb(v);
            path[w].eb(u);
        }
    }

    //cout << cnt << endl;

    dfs(1);

    //cout << cnt << endl;

    if (cnt > 0) {
        cout << "No";
    } else {
        cout << "Yes";
    }
    return 0;
}
