#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

int n, k;
vector<vector<int>> g;
vector<int> ban;

void read() {
    cin >> n;
    g.resize(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    cin >> k;
    ban.resize(k);
    for (auto& i : ban) {
        cin >> i;
        --i;
    }
}

vector<int> cost;

void initCost() {
    cost.assign(n, -1);
    queue<int> q;
    for (auto v : ban) {
        q.push(v);
        cost[v] = 0;
    }
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (auto i : g[v]) {
            if (cost[i] != -1) continue;
            cost[i] = cost[v] + 1;
            q.push(i); 
        }
    }
}

vector<int> ans;

int dfs(int v, int p, int dist) {
    if (cost[v] < dist) return 0;
    if (cost[v] == dist) return cost[v];
    int ans = cost[v];
    for (auto i : g[v]) {
        if (i == p) continue;
        chkmax(ans, dfs(i, v, dist + 1));
    }
    return ans;
}

int calc(int v) {
    return dfs(v, -1, 0);
}

void run() {
    ans.assign(n, 0);
    initCost();
    for (int i = 0; i < n; ++i) {
        ans[i] = calc(i);
    }
}

void write() {
    for (auto i : ans) {
        cout << i << " ";
    }
    cout << endl;
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
    read();
    run();
    write();
    return 0;
}