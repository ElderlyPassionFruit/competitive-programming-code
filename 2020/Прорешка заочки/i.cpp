#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

struct Edge{
    int to, cost;
};

const int N = 1e5 + 10;
const int C = 1e6 + 10;
int n;
vector<Edge> g[N];

void read() {
    cin >> n;
    for (int i = 0; i < n - 1; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        --u;
        --v;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
}

vector<int> d[C];

void build() {
    for (int i = 1; i < C; ++i) {
        for (int j = i; j < C; j += i) {
            d[j].push_back(i);
        }
    }
}

ll ans;

int sz[N];
bool used[N];
int centr;

void dfs(int v, int p, int size) {
    sz[v] = 1;
    int mx = 0;
    for (auto [to, cost] : g[v]) {
        if (to == p) continue;
        if (used[to]) continue;
        dfs(to, v, size);
        sz[v] += sz[to];
        chkmax(mx, sz[to]);
    }
    chkmax(mx, size - sz[v]);
    if (mx * 2 <= size) {
        centr = v;
    }
}

int fans[C];

void dfsAns(int v, int p, int myGcd) {
    for (auto x : d[myGcd]) {
        //cerr << "x = " << x << " fans[x] = " << fans[x] << endl;
        int cnt = fans[x];
        for (auto y : d[myGcd]) {
            // if ()
        }
        ans += (ll)fans[x] * x;
    }
    //ans += myGcd;

    for (auto [to, cost] : g[v]) {
        if (to == p) continue;
        if (used[to]) continue;
        dfsAns(to, v, __gcd(myGcd, cost));
    }
}

void dfsUpd(int v, int p, int myGcd, int flag) {
    // cerr << "v = " << v << " p = " << p << " myGcd = " << myGcd << " flag = " << flag << endl;
    // fans[myGcd] += flag;
    for (auto x : d[myGcd]) {
        fans[x] += flag;
    }
    for (auto [to, cost] : g[v]) {
        if (to == p) continue;
        if (used[to]) continue;
        dfsUpd(to, v, __gcd(myGcd, cost), flag);
    }
}

void solve(int v, int size) {
    dfs(v, -1, size);
    assert(centr != -1);
    // cerr << "v = " << v << " centr = " << centr << endl;
    v = centr;
    used[v] = true;
    for (auto [to, cost] : g[v]) {
        if (used[to]) continue;
        dfsUpd(to, v, cost, 1);
    }
    for (auto [to, cost] : g[v]) {
        if (used[to]) continue;
        dfsUpd(to, v, cost, -1);
        dfsAns(to, v, cost);
        dfsUpd(to, v, cost, 1);
    }
    dfsUpd(v, -1, 0, -1);
    for (auto [to, cost] : g[v]) {
        if (used[to]) continue;
        int fsz = sz[to];
        if (fsz > sz[v]) {
            fsz = size - sz[v];
        }
        solve(to, fsz);
    }
}

void run() {
    build();
    // cerr << "build: Ok" << endl;
    solve(0, n);
}

void write() {
    cout << ans << endl;
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
    read();
    run();
    write();
    return 0;
}