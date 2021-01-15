#include <bits/stdc++.h>
 
using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()
 
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
const int MAXN = 2e5 + 10;
#define int ll
int n, m;
vector<int> g[MAXN];
map<int, vector<int>> gr[MAXN];
 
 
int c[MAXN];
void read() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> c[i];  
    }
    for (int i = 0; i < m; i++) {
        int a, x, y;
        cin >> a >> x >> y;
        a--;
        x--;
        y--;
        gr[a][x].push_back(y);
        gr[a][y].push_back(x);
        g[x].push_back(a);
        g[y].push_back(a);
    }
}
 
int ans;
bool used[MAXN];
 
void run() {
    queue<int> q;
    for (int i = 0; i < n; i++)
        q.push(i), used[i] = true;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        used[v] = false;
        for (auto i : g[v]) {
            for (auto x : gr[i][v]) {
                if (c[i] <= c[v] + c[x]) continue;
                c[i] = c[v] + c[x];
                if (!used[i]) q.push(i);
                used[i] = true;
            }
        }
    }
    ans = c[0];
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