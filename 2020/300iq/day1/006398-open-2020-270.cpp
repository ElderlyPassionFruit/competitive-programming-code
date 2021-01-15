#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MEM = 5e8;

char c[MEM];

int ptr = 0;

void *operator new(size_t n) {
    ptr += n;
    return (void*)(c+ptr-n);
}

void operator delete(void *) {
}

const int N = 5e5 + 7;

vector <int> g[N];
int tin[N], tout[N];
int dad[N];

int tt = 0;

void dfs(int v, int pr) {
    tin[v] = tt++;
    dad[v] = pr;
    for (int to : g[v]) {
        if (to != pr) {
            dfs(to, v);
        }
    }
    tout[v] = tt++;
}

bool par(int a, int b) {
    return tin[a] <= tin[b] && tout[a] >= tout[b];
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
        for (auto z : lc[v]) {
            zz[z.first] = zz[z.second] = zzz;
            out.push_back({id, dp[z.first][me], dp[z.second][me ^ 1]});
            out.push_back({id, dp[z.second][me], dp[z.first][me ^ 1]});
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
    vector <event> out;
    set <int> tilt;
    int id = 0;
    for (auto z : lc[v]) {
        tilt.insert(z.first);
        tilt.insert(z.second);
        if (dp[z.first][me ^ 1] > dp[z.second][me ^ 1]) swap(z.first, z.second);
        if (dp[z.second][me] > x) {
            restore(z.first, v, me);
            restore(z.second, v, me ^ 1);
        } else {
            restore(z.first, v, me ^ 1);
            restore(z.second, v, me);
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
        int x = -1, y = -1;
        while (!par(s, t)) {
            x = s;
            alive.push_back({s, 0});
            f[s].push_back({i, 0});
            if (!par(dad[s], t)) {
                not_lca[s] = 1;
            }
            s = dad[s];
        }
        while (!par(t, s)) {
            y = t;
            alive.push_back({t, 1});
            f[t].push_back({i, 1});
            if (!par(dad[t], s)) {
                not_lca[t] = 1;
            }
            t = dad[t];
        }
        if (x != -1 && y != -1) {
            lc[s].push_back({x, y});
        }
        qs.push_back(alive);
    }
    bool bad = false;
    for (int i = 1; i < n; i++) {
        if (!f[i].empty()) {
            if (f[i].size() > 1) bad = true;
            int a = f[i][0].first;
            for (auto c : f[i]) {
                add_edge(c.first, a);
            }
        }
    }
    vector <int> ans(n, -1);
    vector <vector <int> > ord;
    for (int i = 0; i < m; i++) {
        if (!u[i]) {
            qr_ord.clear();
            dfs_comp(i);
            vector <int> guys;
            for (int i : qr_ord) {
                bool bad_natural = false;
                bool bad_rev = false;
                for (auto c : qs[i]) {
                    guys.push_back(c.first);
                    if (ans[c.first] != -1 && ans[c.first] != c.second) {
                        bad_natural = true;
                    }
                    if (ans[c.first] != -1 && ans[c.first] == c.second) {
                        bad_rev = true;
                    }
                }
                if (bad_natural && bad_rev) {
                    cout << -1 << endl;
                    return 0;
                }
                if (!bad_natural) {
                    for (auto c : qs[i]) ans[c.first] = c.second;
                } else {
                    for (auto c : qs[i]) ans[c.first] = (c.second ^ 1);
                }
            }
            sort(guys.begin(), guys.end());
            guys.resize(unique(guys.begin(), guys.end()) - guys.begin());
            ord.push_back(guys);
        }
    }
    vector <int> rev(ord.size());
    vector <int> last;
    auto cost = [&] (vector <int> rev) {
        vector <int> bns = ans;
        for (int i = 0; i < (int) ord.size(); i++) {
            if (rev[i]) {
                for (auto c : ord[i]) {
                    bns[c] ^= 1;
                }
            }
        }
        for (int i = 0; i < n; i++) tg[i].clear();
        for (int i = 1; i < n; i++) {
            if (bns[i] == 1) {
                tg[dad[i]].push_back(i);
            } else if (bns[i] == 0) {
                tg[i].push_back(dad[i]);
            }
        }
        ts.clear();
        for (int i = 0; i < n; i++) vis[i] =0 ;
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
        last = c;
        return *max_element(c.begin(), c.end());
    };
    int me = cost(rev);
    auto best = rev;
    bool ch = true;
    if (t != 0) {
        if (bad && n <= 100 && m <= 100) {
            for (int its = 0; its < 10000; its++) {
                ch = true;
                for (int i = 0; i < (int) rev.size(); i++) {
                    rev[i] = rnd() % 2;
                }
                me = cost(rev);
                while (ch) {
                    ch = false;
                    for (int i = 0; i < (int) rev.size(); i++) {
                        rev[i] ^= 1;
                        int go = cost (rev);
                        if (go < me) {
                            me = go;
                            ch = true;
                        } else {
                            rev[i] ^= 1;
                        }
                    }
                }
                if (cost(rev) < cost(best)) {
                    best = rev;
                }
            }
        } else {
            bool star = false;
            int root = -1;
            for (int i = 0; i < n; i++) {
                if (g[i].size() == n - 1) {
                    star = true;
                    root = i;
                }
            }
            if (bad && star) {
                for (int i = 0; i < (int) ord.size(); i++) {
                    auto c = ord[i];
                    if (c.size() == 2) {
                        continue;
                    } else {
                        int x = c[0];
                        if (ans[x]) {
                            best[i] = 1;
                        } else {
                            best[i] = 0;
                        }
                    }
                }
            } else {
                for (int i = 0; i < n; i++) {
                    roots[i] = (ans[i] == -1);
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
        }
    }
    rev = best;
    me = cost(rev);
    cout << me << endl;
    cost(rev);
    for (int i = 0; i < n; i++) cout << last[i] << ' ';
    cout << endl;
}

