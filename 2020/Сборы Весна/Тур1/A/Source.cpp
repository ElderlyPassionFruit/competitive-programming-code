#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <queue>

using namespace std;

const int N = 25;
vector<int> g[N], mp[N], vis;
int C[N], cntall[N];

int sz[N], mxsz[N], used[N];

int usednw[N], par[N], usedcol[N];

void dfs_sz(int v, int p) {
    sz[v] = 1, mxsz[v] = 0;
    for (int to : g[v]) {
        if (used[to] || to == p) continue;
        dfs_sz(to, v);
        sz[v] += sz[to], mxsz[v] = max(mxsz[v], sz[to]);
    }
}

queue<int> ndcol;

int Cnt = 0, nwcnt = 0;

void dfs_solve(int v, int p, int nd) {
    if (nd == C[v]) 
        ++nwcnt;
    mp[C[v]].push_back(v);
    vis.push_back(v);
    for (int to : g[v]) {
        if (to == p || used[to]) continue;
        par[to] = v;
        dfs_solve(to, v, nd);
    }
}

void get(int v) {
    while (par[v] != -1) {
        if (usednw[v]) return;
        usednw[v] = 1;
        if (usedcol[C[v]] == 0) {
            while (mp[C[v]].size()) {
                ndcol.push(mp[C[v]].back());
                mp[C[v]].pop_back();
            }
            usedcol[C[v]] = 1;
            ++Cnt;
        }
        v = par[v];
    }
}

int ans = N;

void Clear() {
    while (vis.size()) {
        int u = vis.back();
        while (mp[C[u]].size()) {
            mp[C[u]].pop_back();
        }
        usednw[u] = 0;
        usedcol[C[u]] = 0;
        par[u] = -1;
        vis.pop_back();
    }
    nwcnt = 0, Cnt = 0;
}

void dfs_c(int v, int p, int all) {
    if ((all - sz[v]) * 2 <= all && mxsz[v] * 2 <= all) {

        dfs_solve(v, -1, C[v]);
        for (int u : mp[C[v]])
            ndcol.push(u);
        usedcol[C[v]] = 1;
        while (ndcol.size()) {
            int u = ndcol.front();
            ndcol.pop();
            get(u);
        }
        if (nwcnt == cntall[C[v]])
            ans = min(ans, Cnt);

        Clear();

        used[v] = 1; 
        for (int to : g[v]) {
            if (used[to]) continue;
            dfs_sz(to, -1);
            dfs_c(to, -1, sz[to]);
        }
    } else {
        for (int to : g[v]) {
            if (to == p || used[to] || sz[to] != mxsz[v]) continue;
            dfs_c(to, v, all);
        }
    }
}

void solve() {
    for (int i = 0; i < N; ++i) {
        par[i] = -1;
        used[i] = 0, usednw[i] = 0, usedcol[i] = 0;
    }

    dfs_sz(1, -1);
    dfs_c(1, -1, sz[1]);
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, k;
    cin >> n >> k;
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int i = 1; i <= n; ++i) {
        cin >> C[i];
        cntall[C[i]]++;
    }

    solve();

    cout << ans << endl;
}