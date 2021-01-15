#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct Edge{
    int to, ind;
};

int n;
vector<vector<Edge>> g;

void read() {
    cin >> n;
    g.resize(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        g[u].push_back({v, i + 1});
        g[v].push_back({u, i + 1});
    }
}

int dfs(int v, int p, vector<int>& lables) {
    int ans = 0;
    for (auto i : g[v]) {
        if (i.to == p) continue;
        int cost = 1;
        if (lables[v] == i.ind) {
            cost = 0;
        }
        chkmax(ans, dfs(i.to, v, lables) + cost);
    }
    return ans;
}

int calc(vector<int>& lables) {
    /*cout << "lables = " << endl;
    for (auto i : lables) {
        cout << i << " ";
    }
    cout << endl;*/
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        chkmax(ans, dfs(i, -1, lables));
    }
    /*if (ans == 1) {
        cout << "lables = " << endl;
        for (auto i : lables) {
            cout << i << " ";
        }
        cout << endl;
        exit(0);
    }*/
    return ans;
}

void rec(vector<int> lables, int pos, int& ans) {
    if (pos == n) {
        chkmin(ans, calc(lables));
        return;
    }
    for (auto i : g[pos]) {
        lables.push_back(i.ind);
        rec(lables, pos + 1, ans);
        lables.pop_back();
    }
}

int solveAns() {
    int ans = n - 1;
    vector<int> lables = {};
    rec(lables, 0, ans);
    return ans;
}

int ans;

void run() {
    ans = solveAns();
}

void write() {
    cout << ans << endl;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    read();
    run();
    write();
    return 0;
}