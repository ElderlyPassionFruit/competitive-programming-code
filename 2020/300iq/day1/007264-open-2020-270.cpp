#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 5e5 + 7;
const int K = 20;

int st[N][K];

vector <int> g[N];
int tin[N], tout[N];
int dad[N];

int tt = 0;
int dep[N];
bool knch[N];
int dsu[N];

int get(int v) {
    if (v == dsu[v]) {
        return v;
    } else {
        return dsu[v] = get(dsu[v]);
    }
}

void uni(int u, int v) {
    dsu[get(u)] = get(v);
}

void dfs(int v, int pr) {
    if (pr == -1) st[v][0] = 0;
    else st[v][0] = pr;
    for (int i= 1; i < K; i++) {
        st[v][i] = st[st[v][i - 1]][i - 1];
    }
    tin[v] = tt++;
    dad[v] = pr;
    for (int to : g[v]) {
        if (to != pr) {
            dep[to] = dep[v] + 1;
            dfs(to, v);
        }
    }
    tout[v] = tt++;
}

bool par(int a, int b) {
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int lca(int a, int b) {
    if (par(a, b)) return a;
    for (int i = K - 1; i >= 0; i--) {
        if (!par(st[a][i], b)) {
            a = st[a][i];
        }
    }
    return st[a][0];
}

int np(int a, int b) {
    int need = dep[a] - dep[b] - 1;
    for (int i = K - 1; i >= 0; i--) {
        if ((need >> i) & 1) {
            a = st[a][i];
        }
    }
    return a;
}

void ban_path(int a, int b) {
    if (a == b) return;
    int c = np(a, b);
    while (true) {
        a = get(a);
        if (par(a, c)) return;
        knch[a] = true;
        uni(a, dad[a]);
    }
}

vector <int> gr[N];
vector <pair <int, int> > f[N];

void add_edge(int a, int b) {
    gr[a].push_back(b);
    gr[b].push_back(a);
}

bool u[N];

vector <int> qr_ord;

void dfs_comp(int v) {
    u[v] = true;
    qr_ord.push_back(v);
    for (int x : gr[v]) {
        if (!u[x]) {
            dfs_comp(x);
        }
    }
}

vector <int> tg[N];
bool vis[N];
vector <int> ts;

void zhfs(int v) {
    vis[v] = true;
    for (int to : tg[v]) {
        if (!vis[to]) {
            zhfs(to);
        }
    }
    ts.push_back(v);
}

mt19937 rnd(228);

int dp[N][2];
vector <pair <int, int>> lc[N];
int not_lca[N];

int zz[N];

int zzz = 0;

struct event {
    int id, a, b;
};

const int inf = 1e9;

bool operator < (event a, event b) {
    return a.a < b.a;
}

bool roots[N];
int mp[N];

vector <int> zg[N];
int col[N];
bool kkk[N];

vector <int> ss;

void ma(int v, int c) {
    if (kkk[v]) {
        if (col[v] != c) {
            cout << -1 << endl;
            exit(0);
        }
        return;
    }
    ss.push_back(v);
    kkk[v] = true;
    for (int x : zg[v]) {
        if (!kkk[x]) {
            ma(x, c ^ 1);
        }
    }
}

vector <pair <vector <int>, vector <int> > > orz[N];

void preprocess(int v, int pr) {
    for (int to : g[v]) {
        if (to != pr && !roots[to]) {
            preprocess(to, v);
        }
    }
    for (auto c : lc[v]) {
        zg[c.first].push_back(c.second);
        zg[c.second].push_back(c.first);
    }
    for (auto c : lc[v]) {
        if (!kkk[c.first]) {
            ss.clear();
            ma(c.first, 0);
            vector <int> a, b;
            for (int v : ss) {
                if (col[v]) {
                    a.push_back(v);
                } else {
                    b.push_back(v);
                }
            }
            orz[v].push_back({a, b});
        }
    }
}

void solve(int v, int pr, int x) {
    vector <int> ch;
    for (int to : g[v]) {
        if (to != pr && !roots[to]) {
            ch.push_back(to);
            solve(to, v, x);
        }
    }
    for (int me = 0; me < 2; me++) {
        int mx = 0;
        vector <event> out;
        zzz++;
        int id = 0;
        for (auto z : orz[v]) {
            for (int t = 0; t < 2; t++) {
                int a = 0;
                for (int x : z.first) {
                    zz[x] = zzz;
                    a = max(a, dp[x][t]);
                }
                int b = 0;
                for (int x : z.second) {
                    zz[x] = zzz;
                    b = max(b, dp[x][t ^ 1]);
                }
                out.push_back({id, a, b});
            }
            id++;
        }
        for (int to : ch) {
            if (not_lca[to]) {
                out.push_back({id, dp[to][me], 0});
                id++;
            } else {
                if (zz[to] != zzz) {
                    out.push_back({id, 0, dp[to][me ^ 1]});
                    out.push_back({id, dp[to][me], 0});
                    id++;
                }
            }
        }
        sort(out.begin(), out.end());
        for (int i = 0; i < id; i++) mp[i] = inf;
        int ok = 0;
        multiset <int> q;
        dp[v][me] = inf;
        for (int i = 0; i < (int) out.size(); i++) {
            if (mp[out[i].id] != inf) {
                q.erase(q.find(mp[out[i].id]));
                mp[out[i].id] = min(mp[out[i].id], out[i].b);
                q.insert(mp[out[i].id]);
            } else {
                mp[out[i].id] = out[i].b;
                q.insert(mp[out[i].id]);
            }
            if (i + 1 == (int) out.size() || out[i + 1].a != out[i].a) {
                if (q.size() == id && (q.empty() ? 0 : *q.rbegin()) + out[i].a <= x) {
                    dp[v][me] = out[i].a + 1;
                    break;
                }
            }
        }
        if (id == 0) {
            dp[v][me] = 1;
        }
    }
}

int kk[N];

void restore(int v, int pr, int me) {
    kk[v] = me;
    vector <int> ch;
    for (int to : g[v]) {
        if (to != pr && !roots[to]) {
            ch.push_back(to);
        }
    }
    int x = dp[v][me] - 1;
    int mx = 0;
    set <int> tilt;
    int id = 0;
    for (auto z : orz[v]) {
        int who = -1;
        int sa = -1, sb = -1;
        for (int t = 0; t < 2; t++) {
            int a = 0;
            for (int x : z.first) {
                tilt.insert(x);
                a = max(a, dp[x][t]);
            }
            int b = 0;
            for (int x : z.second) {
                tilt.insert(x);
                b = max(b, dp[x][t ^ 1]);
            }
            if (who == -1) {
                if (a <= x) {
                    who = t;
                    sa = a, sb = b;
                }
            } else {
                if (a <= x && b < sb) {
                    who = t;
                    sa = a, sb = b;
                }
            }
        }
        for (int x : z.first) {
            restore(x, v, who);
        }
        for (int x : z.second) {
            restore(x, v, who ^ 1);
        }
    }
    for (int to : ch) {
        if (not_lca[to]) {
            restore(to, v, me);
        } else {
            if (!tilt.count(to)) {
                if (dp[to][me] <= x) {
                    restore(to, v, me);
                } else {
                    restore(to, v, me ^ 1);
                }
            }
        }
    }
}

int mda[N];

void ofk(int v, int pr) {
    for (int to : g[v]) {
        if (to != pr) {
            ofk(to, v);
            mda[v] += mda[to];
        }
    }
}

int main() {
#ifdef iq
    freopen("a.in", "r", stdin);
#endif // iq
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, m, t;
    cin >> n >> m >> t;
    for (int i = 0; i < n; i++) {
        g[i].clear();
        dsu[i] = i;
    }
    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dfs(0, -1);
    vector <vector <pair <int, int> > > qs;
    for (int i = 0; i < m; i++) {
        int s, t;
        cin >> s >> t;
        s--, t--;
        vector <pair <int, int> > alive;
        int c = lca(s, t);
        if (s != c && t != c) {
            lc[c].push_back({np(s, c), np(t, c)});
        }
        ban_path(s, c);
        ban_path(t, c);
        mda[s]++;
        mda[t]++;
        mda[c] -= 2;
    }
    ofk(0, -1);
    preprocess(0, -1);
    for (int i = 0; i < n; i++) {
        not_lca[i] = knch[i];
    }
    for (int i = 0; i < n; i++) {
        roots[i] = !mda[i];
        vis[i] = 0;
        tg[i].clear();
    }
    ts.clear();
    int l = -1, r = n + 1;
    while (l < r - 1) {
        int m = (l + r) / 2;
        bool okay = true;
        for (int i= 0; i < n; i++) {
            if (roots[i]) {
                solve(i, dad[i], m);
                if (dp[i][0] > n) {
                    okay = false;
                }
            }
        }
        if (okay) {
            r = m;
        } else {
            l = m;
        }
    }
    cout << r + 1 << endl;
    for (int i= 0; i < n; i++) {
        if (roots[i]) {
            solve(i, dad[i], r);
        }
    }
    for (int i= 0; i < n; i++) {
        if (roots[i]) {
            restore(i, dad[i], 0);
        }
    }
    for (int i= 0; i < n; i++) {
        if (roots[i]) continue;
        if (!kk[i]) {
            tg[i].push_back(dad[i]);
        } else {
            tg[dad[i]].push_back(i);
        }
    }
    for (int i=  0; i < n; i++) {
            if (!vis[i]) {
                    zhfs(i);
            }
    }
    vector <int> c(n, 1);
    for (int v : ts) {
        for (int to : tg[v]) {
            c[v] = max(c[v], c[to] + 1);
        }
    }
    for (int i = 0; i < n; i++) {
        cout << c[i] << ' ';
    }
    cout << endl;
    return 0;
}

