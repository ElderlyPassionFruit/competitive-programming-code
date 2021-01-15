#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

int n;
vector<vector<int>> g;
vector<int> sz;
vector<int> mx;

void dfsSz(int v, int p) {
    sz[v] = 1;
    mx[v] = 0;
    for (auto i : g[v]) {
        if (i == p) continue;
        dfsSz(i, v);
        chkmax(mx[v], sz[i]);
        sz[v] += sz[i];
    }
    chkmax(mx[v], n - sz[v]);
}

vector<int> getCentroids() {
    sz.assign(n, 0);
    mx.assign(n, 0);
    dfsSz(0, 0);
    vector<int> ans;
    for (int i = 0; i < n; i++) {
        if (ans.empty()) {
            ans.push_back(i);
        } else if (mx[i] < mx[ans.back()]) {
            ans = {i};
        } else if (mx[i] > mx[ans.back()]) {
            continue;
        } else {
            ans.push_back(i);
        }
    }
    return ans;
}

void dfsV(int v, int p, int ban, int& ans) {
    if (g[v].size() == 1) {
        ans = v;
        return;
    }
    for (auto i : g[v]) {
        if (i == p || i == ban) continue;
        dfsV(i, v, ban, ans);
    }
}

int findV(int v, int ban) {
    int ans = -1;
    dfsV(v, -1, ban, ans);
    assert(ans != -1);
    return ans;
}

void solve() {
    cin >> n;
    g.assign(n, {});
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v; 
        u--;
        v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    auto have = getCentroids();
    /*cout << "have = " << endl;
    for (auto i : have) {
        cout << i << " ";
    }
    cout << endl;
    cout << endl;*/
    assert(have.size() >= 1 && have.size() <= 2);
    if (have.size() == 1) {
        for (int i = 0; i < n; i++) {
            assert(!g[i].empty());
            cout << g[i][0] + 1 << " " << i + 1 << "\n";
            cout << g[i][0] + 1 << " " << i + 1 << "\n";
            return;
        }
    }
    int v = findV(have[1], have[0]);
    assert(g[v].size() == 1);
    cout << g[v][0] + 1 << " " << v + 1 << "\n";
    cout << have[0] + 1 << " " << v + 1 << "\n";
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}