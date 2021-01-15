#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

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
        while (!par(s, t)) {
            alive.push_back({s, 0});
            f[s].push_back({i, 0});
            s = dad[s];
        }
        while (!par(t, s)) {
            alive.push_back({t, 1});
            f[t].push_back({i, 1});
            t = dad[t];
        }
        qs.push_back(alive);
    }
    for (int i = 1; i < n; i++) {
        if (!f[i].empty()) {
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
            if (bns[i]) {
                tg[dad[i]].push_back(i);
            } else {
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
        for (int its = 0; its < (1 << (int) rev.size()); its++) {
            ch = true;
            for (int i = 0; i < (int) rev.size(); i++) {
                rev[i] = (its >> i) & 1;
            }
            me = cost(rev);
            /*
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
            */
            if (cost(rev) < cost(best)) {
                best = rev;
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
