#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

#define int ll

struct Edge{
    int to, cap, cost;
};

const int N = 1e3 + 10;
int n;
vector<Edge> g[N];
ll ans;
ll sum;

int myCost[N];
int myVal[N];
int p[N];

void dfs(int v, int par) {
    p[v] = par;
    for (auto [to, cap, cost] : g[v]) {
        if (par == to) continue;
        myCost[to] = myCost[v] + cost;
        myVal[to] = cap;
        dfs(to, v);
    }
}

vector<int> order;

void build() {
    dfs(0, 0);
    ans = 0;
    sum = 0;
    for (int i = 1; i < n; ++i) {
        if (g[i].size() != 1) continue;
        if (p[i] != g[i][0].to) continue;
        order.push_back(i);
    }
    sort(all(order), [&] (int a, int b) {
        return myCost[a] < myCost[b];
    });
}

ll getPath(int v) {
    ll ans = myVal[v];
    while (v != 0) {
        ans = min(ans, myVal[v]);
        v = p[v];
    }
    return ans;
}

void upd(int v, ll x) {
    while (v != 0) {
        myVal[v] -= x;
        v = p[v];
    }
}

void relax(int v) {
    ll have = getPath(v);
    if (myCost[v] <= 0 || have * myCost[v] <= sum) {
        ans += have;
        sum -= have * myCost[v];
        upd(v, have);
    } else {
        cout << ans + (ld)sum / myCost[v] << endl;
        exit(0);
    }
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cout.setf(ios::fixed), cout.precision(20);
    cin >> n;
    for (int i = 0; i < n - 1; ++i) {
        int u, v, cap, cost;
        cin >> u >> v >> cap >> cost;
        --u;
        --v;
        g[u].push_back({v, cap, cost});
        g[v].push_back({u, cap, cost});
    }

    build();
    for (auto v : order) {
        relax(v);
    }
    cout << ans << endl;
    return 0;
}