#include <bits/stdc++.h>

using namespace std;
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 2e5 + 10, MAXLOG = 21;
vector<int> g[MAXN];
int n;
int tin[MAXN], timer = 0, h[MAXN];
vector<int> ed;

void dfs(int v, int p, int len) {
    h[v] = len++;
    tin[v] = timer++;
    ed.push_back(v);
    for (auto i : g[v]) {
        if (i != p) {
            dfs(i, v, len);
            ed.push_back(v);
            timer++;
        }
    }
}

int sparse[MAXN][MAXLOG];
int logs[MAXN];
int pows[MAXLOG];

void build() {
    dfs(0, 0, 0);
    for (int i = 2; i < MAXN; i++)
        logs[i] = logs[i / 2] + 1;
    pows[0] = 1;
    for (int i = 1; i < MAXLOG; i++)
        pows[i] = pows[i - 1] * 2;

    for (int i = 0; i < timer; i++) {
        sparse[i][0] = ed[i];    
    }

    for (int j = 1; j < MAXLOG; j++) {
        for (int i = 0; i + pows[j] <= timer; i++) {
            if (h[sparse[i][j - 1]] < h[sparse[i + pows[j - 1]][j - 1]]) {
                sparse[i][j] = sparse[i][j - 1];
            }
            else {
                sparse[i][j] = sparse[i + pows[j - 1]][j - 1];
            }
        }
    }
}


int lca(int v, int u) {
    if (v == u) {
        return v;
    }
    if (tin[v] > tin[u])
        swap(v, u);
    int len = tin[u] - tin[v] + 1;
    int l = logs[len];
    int p = pows[l];

    int ans = sparse[tin[v]][l];
    if (h[ans] > h[sparse[tin[u] - p + 1][l]]) {
        ans = sparse[tin[u] - p + 1][l];
    }

    return ans;
}

void solve() {
    int m;
    cin >> n >> m;
    for (int i = 1; i < n; i++) {
        int p;
        cin >> p;
        g[i].push_back(p);
        g[p].push_back(i);
    }

    build();
    long long a1, a2, x, y, z;
    cin >> a1 >> a2 >> x >> y >> z;
    long long fout = 0;
    int a0 = a1;
    
    for (int i = 0; i < m; i++) {
        int p = lca(a0, a2);
        int a3 = (x * a1 + y * a2 + z) % n;
        int a4 = (x * a2 + y * a3 + z) % n;
        a0 = (a3 + p) % n;
        a1 = a3;
        a2 = a4;     
        fout += p;
    }
    cout << fout << "\n";
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    solve();
    return 0;
}