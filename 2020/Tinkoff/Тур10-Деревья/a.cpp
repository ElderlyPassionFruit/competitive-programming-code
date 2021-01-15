#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 2e5 + 10;
vector<int> g[MAXN];
int n;

void read() {
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
}

int par[MAXN], sz[MAXN], centr = 0;
bool used[MAXN];
void dfs(int v, int p, int size) {
    sz[v] = 1;
    int mx = 0;
    for (auto i : g[v]) {
        if (i != p && !used[i]) {
            dfs(i, v, size);
            sz[v] += sz[i];
            chkmax(mx, sz[i]);
        }
    }
    chkmax(mx, size - sz[v]);
    if (mx <= size / 2) {
        centr = v;
    }
}

void solve(int v, int p, int size) {
    dfs(v, -1, size);
    v = centr;
    used[v] = true;
    par[v] = p;
    for (auto i : g[v]) {
        if (!used[i]) {
            int fsz = sz[i];
            if (fsz > sz[v])
                fsz = size - sz[v];
            solve(i, v, fsz);
        }
    }
}

void run() {
    solve(0, -1, n);
}

void write() {
    for (int i = 0; i < n; i++)
        cout << par[i] + 1 << " ";
    cout << endl;
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
