#include <bits/stdc++.h>
 
using namespace std;
#define int long long
 
const int MAXN = 20;
vector <pair<int, int> > g[MAXN];
bool used[MAXN][MAXN];
int dist[MAXN];
int n;
 
void read() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> dist[i];
    }
    for (int i = 1; i < n; i++) {
        int u, v, len;
        cin >> u >> v >> len;
        u--;
        v--;
        g[u].push_back({v, len});
        g[v].push_back({u, len});
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            used[i][j] = false;
    }
}
int cnt = 0;
void dfs(int v, int p, int len, int len2, int old) {
    cnt++;
    if (cnt > 1000) {
        cout << 1 << endl;
        exit(0);
    }
    used[old][v] = true;
    if (dist[v] - len2 > len + len2)
        p = -1;
    len = max(len, dist[v]);
    for (auto i : g[v]) {
        if (i.first != p && i.second <= len) {
            dfs(i.first, v, len - i.second, i.second, old);
        }
    }
}
 
bool check(vector <int> & a) {
    vector <bool> u(n, false);
    for (int i = 0; i < n; i++) {
        if (a[i] == 1) {
            for (int j = 0; j < n; j++) {
                if (used[i][j]) u[j] = true;
            }
        }
    }
    int cnt = 0;
    for (int i = 0; i < n; i++) 
        if (u[i] == true)
            cnt++;
    return (cnt == n);
}
 
void run() {
    for (int i = 0; i < n; i++) {
        cnt = 0;
        dfs(i, i, dist[i], 1e9, i);
    }
    for (int i = 1; i <= n; i++) {
        vector <int> help(n);
        for (int j = 0; j < i; j++)
            help[j] = 1;
        reverse(help.begin(), help.end());
        do {
            if (check(help)) {
                cout << i << endl;
                return;
            }
        } while(next_permutation(help.begin(), help.end()));
 
    }
    cout << n << endl;
}
 
void write() {
 
}
 
signed main() {
    freopen("alarm.in", "r", stdin);
    freopen("alarm.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    read();
    run();
    write();
    return 0;
}