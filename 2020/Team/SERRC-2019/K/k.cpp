#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int N = 1e5 + 10;
int n, m, v;
vector<int> g[N];
bool ans[N];
bool need[N];
bool used[N];

void dfs(int v, bool ok) {
    if (ok && need[v]) {
        ans[v] = true;
    }
    ok = true;
    used[v] = true;
    for (auto i : g[v]) {
        if (used[i]) continue;
        dfs(i, ok);
    }
}

void solve() {
    for (auto i : g[v]) {
        need[i] = true;
    }
    fill(used, used + n, false);
    used[v] = true;
    for (auto i : g[v]) {
        dfs(i, false);
    }
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    cin >> n >> m >> v;
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        g[v].push_back(u);
    }
    
    solve();
    reverse(all(g[v]));
    solve();
    for (auto i : g[v]) {
        ans[i] ^= 1;
    }
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        if (ans[i]) {
            ++cnt;
        }
    }
    cout << cnt << "\n";
    for (int i = 0; i < n; ++i) {
        if (ans[i]) {
            cout << i << "\n";
        }
    }
	return 0;
}