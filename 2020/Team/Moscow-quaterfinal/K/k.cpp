#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct Edge{
    int to, ind;
    Edge() {}
    Edge(int _to, int _ind) {
        to = _to, ind = _ind;
    }
};

const int N = 2e5 + 10;
int n;
vector<Edge> g[N];

void read() {
    cin >> n;
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        g[u].push_back({v, i + 1});
        g[v].push_back({u, i + 1});
    }
}

int par[N];
int h[N];

void dfs(int v, int p) {
    par[v] = p;
    for (auto i : g[v]) {
        if (i.to == p) continue;
        h[i.to] = h[v] + 1;
        dfs(i.to, v); 
    }
}

int ans;
int lables[N];
int root;

void dfsLables(int v, int p) {
    for (auto i : g[v]) {
        if (i.to == p) continue;
        lables[i.to] = i.ind;
        dfsLables(i.to, v);
    }
}

int getMxH(int v, int p) {
    int ans = 0;
    for (auto i : g[v]) {
        if (i.to == p) continue;
        int cost = 1;
        if (lables[v] == i.ind) {
            cost = 0;
        }
        chkmax(ans, getMxH(i.to, v) + cost);
    }
    return ans;
}

void buildLables() {
    dfs(0, -1);
    int mx = max_element(h, h + n) - h;
    fill(h, h + n, 0);
    dfs(mx, -1);
    mx = max_element(h, h + n) - h;
    int len = h[mx] / 2;
    while (len--) {
        mx = par[mx];
    }
    fill(lables, lables + n, -1);
    root = mx;
    int nowH = -1;
    int nowL = -1;
    for (auto i : g[root]) {
        int have = getMxH(i.to, root);
        if (have <= nowH) continue;
        nowH = have;
        nowL = i.ind;
    }
    lables[root] = nowL;
    dfsLables(root, -1);
}

void calcAns() {
    ans = getMxH(root, -1);
}

void run() {
    buildLables();
    calcAns();
}

void write() {
    cout << ans << '\n';
    /*for (int i = 0; i < n; ++i) {
        cout << lables[i] << ' ';
    }
    cout << '\n';*/
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