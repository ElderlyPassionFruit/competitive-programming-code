#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

struct Edge{
    int u, v, cost;
};

bool operator<(const Edge& a, const Edge& b) {
    return a.cost < b.cost;
}

const int N = 3e5 + 10;
int n, m;
Edge edges[N];

int par[N], sz[N];

void init() {
    iota(par, par + n, 0);
    fill(sz, sz + n, 1);
}

int getPar(int v) {
    if (v == par[v]) return v;
    return par[v] = getPar(par[v]);
}

ll ans = 0;

void uni(int a, int b, int x) {
    //cout << "a = " << a << " b = " << b << " x = " << x << endl;
    a = getPar(a);
    b = getPar(b);
    if (a == b) {
        return;
    }
    ans += (ll)sz[a] * sz[b] * x;
    sz[a] += sz[b];
    par[b] = a;
}

void no() {
    cout << -1 << "\n";
    exit(0);
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].cost;
        --edges[i].u;
        --edges[i].v;
    }
    init();
    sort(edges, edges + m);
    reverse(edges, edges + m);
    for (int l = 0; l < m; ++l) {
        int r = l;
        while (r < m && edges[l].cost == edges[r].cost) {
            ++r;
        }
        for (int i = l; i < r; ++i) {
            if (getPar(edges[i].u) == getPar(edges[i].v)) {
                no();
            }
        }
        for (int i = l; i < r; ++i) {
            uni(edges[i].u, edges[i].v, edges[i].cost);
        }
        l = r - 1;
    }
    for (int i = 1; i < n; ++i) {
        if (getPar(i) != getPar(0)) {
            uni(i, 0, 1);
        }
    }
    cout << ans << "\n";
	return 0;
}