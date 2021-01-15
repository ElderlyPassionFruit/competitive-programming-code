#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

const int N = 1e5 + 10;
int n, m;

int par[N];

int getPar(int v) {
    if (v == par[v]) return v;
    return par[v] = getPar(par[v]);
}

bool uni(int a, int b) {
    a = getPar(a);
    b = getPar(b);
    if (a == b) return false;
    par[a] = b;
    return true;
}

int p[N];
int cost[N];

void init(int n) {
    iota(par, par + n, 0);
    fill(p, p + n, -1);
}

ll ans = 0;

void hangByRoot(int v) {
    int nxt = p[v];
    int lastCost = cost[v];
    p[v] = -1;

    while (nxt != -1) {
        swap(lastCost, cost[nxt]);
        int myNxt = p[nxt];
        p[nxt] = v;
        v = nxt;
        nxt = myNxt;
    }
}

int getMinCost(int v) {
    int ans = v;
    while (p[v] != -1) {
        if (cost[ans] < cost[v]) {
            ans = v;
        }
        v = p[v];
    }
    return ans;
}

void addEdge(int u, int v, int len) {
    if (u == v) return;
    if (uni(u, v)) {
        ans += len;
        hangByRoot(u);
        p[u] = v;
        cost[u] = len;
    } else {
        hangByRoot(u);
        int forCut = getMinCost(v);
        if (cost[forCut] <= len) return;
        ans -= cost[forCut];
        p[forCut] = -1;
        hangByRoot(v);
        ans += len;
        p[v] = u;
        cost[v] = len;
    }
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
    cin >> n >> m;
    init(n);

    while (m--) {
        int u, v, len;
        cin >> u >> v >> len;
        --u;
        --v;
        addEdge(u, v, len);
        cout << ans << '\n';
        cout.flush();
    }
    return 0;
}