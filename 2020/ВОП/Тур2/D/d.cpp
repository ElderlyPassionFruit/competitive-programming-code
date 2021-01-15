#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,avx,avx2,mmx,abm")
#include <bits/stdc++.h>
 
using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(), (x).end()
template <typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

struct edge{
    int to, dist, s;
    edge() {}
    edge(int _to, int _dist, int _s) {
        to = _to, dist = _dist, s = _s;
    }
};
const int MAXN = 3001 + 10;
 
ll fans[MAXN][MAXN];
bool have[MAXN];
vector<edge> g[MAXN];
int n, m, k;
 
void read() {
    cin >> n >> m >> k;
    //scanf("%d%d%d",&n,&m,&k);
    for (int i = 0; i < n; i++) {
        g[i].clear();
        have[i] = false;
    }
    for (int i = 0; i < m; i++) {
        int u, v, dist, s;
        cin >> u >> v >> dist >> s;
        //scanf("%d%d%d%d",&u,&v,&dist,&s);
        u--;
        v--;
        g[u].push_back({v, dist, s});
        g[v].push_back({u, dist, s});
    }
}
 
const ll INF = 1e18 + 228;
ll dist[MAXN];
queue<int> q;
 
int topQ;

ll solve(int s, int t) {
	if (have[s]) return fans[s][t];
    q.push(s);
    fill(dist, dist + n, INF);
    dist[s] = 0;
    while (!q.empty()) {
        int v = q.front();
        q.pop(); 
        for (auto [to, d, s] : g[v]) {
            ll nxt = 0;
            if (s >= dist[v]) {
                nxt = s + d;
            } else {
                nxt = (dist[v] - s + k - 1) / k * k + s + d;
            }
            if (nxt >= dist[to]) continue;
            dist[to] = nxt;
            q.push(to);
        }
    }
    have[s] = true;
    for (int i = 0; i < n; i++) {
    	fans[s][i] = dist[i];
    }

    return dist[t];
}
 
void run() {
    int q;
    cin >> q;
    //scanf("%d", &q);
    ll ans = 0;
    while (q--) {
        int x, y;
        cin >> x >> y;
        //scanf("%d%d", &x, &y);
        x = (x + ans - 1) % n;
        y = (y + ans - 1) % n;
        ans = solve(x, y);
        cout << ans << "\n";
    }
}
 
void write() {
 
}
 
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.setf(ios::fixed), cout.precision(20);
    int t;
    cin >> t;
    //scanf("%d",&t);
    while (t--) {
        read();
        run();
        write();
    }
    return 0;
}