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
vector<int> g[N];

void read() {
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
}

bool used[N];

void dfs(int v) {
    used[v] = true;
    for (auto i : g[v]) {
        if (used[i]) continue;
        dfs(i);
    }
}

int ans;

void run() {
    ans = -1;
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            dfs(i);
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