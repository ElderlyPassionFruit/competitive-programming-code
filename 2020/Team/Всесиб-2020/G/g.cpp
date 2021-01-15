#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int N = 210;
int n;
int g[N][N];
bool used[N];

void dfs(int v) {
    used[v] = true;
    for (int i = 0; i < n; ++i) {
        if (!g[v][i]) continue;
        if (used[i]) continue;
        dfs(i);
    }
}

void solve() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> g[i][j];
        }
    }
    fill(used, used + n, false);
    int ans = n;
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            --ans;
            dfs(i);
        }
    }
    cout << ans << "\n";
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
	return 0;
}