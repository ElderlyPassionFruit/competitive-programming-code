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
vector<int> a;

void read() {
    cin >> n;
    a.resize(n);
    for (auto& i : a){
        cin >> i;
    }
    g.resize(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
}

set<int> dfs(int v, int p, bool& ok) {
    set<int> ans;
    for (auto i : g[v]) {
        if (i == p) continue;
        auto x = dfs(i, v, ok);
        for (auto have : x) {
            ans.insert(have);
        }
    }
    if (ans.count(a[v])) {
        ok = false;
    } else {
        ans.insert(a[v]);
    }
    return ans;
}

int ans;

void run() {
    ans = 0;
    for (int i = 0; i < n; ++i) {
        bool ok = true;
        dfs(i, -1, ok);
        if (ok) {
            ++ans;
        }
    }
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