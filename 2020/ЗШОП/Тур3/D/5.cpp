#include <bits/stdc++.h>
 
using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()
 
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
 
#define int ll
 
const ll INF = 1e17;

struct edge{
    int u, v, cost, d;
    edge() {}
};
 
vector<edge> ed;
int n, m;
 
void read() {
    cin >> n >> m;
    ed.resize(m);
    for (auto &i : ed) {
        cin >> i.u >> i.v >> i.cost >> i.d;
        i.u--;
        i.v--;
    }
}
 
ll calc(int s, int t) {
    vector<vector<pair<int, int> > > g(n);
    for (auto i : ed) {
        g[i.u].push_back({i.v, i.cost});
    }
    vector<ll> d(n, INF);
    d[s] = 0;
    set<pair<int, int> > q;
    q.insert({0, s});
    while (!q.empty()) {
        int v = q.begin()->second;
        q.erase(q.begin());
        for (auto i : g[v]) {
            if (d[i.first] <= d[v] + i.second) continue;
            q.erase({d[i.first], i.first});
            d[i.first] = d[v] + i.second;
            q.insert({d[i.first], i.first});
        }
    }
    return d[t];
}
 
ll calc() {
    return calc(0, n - 1) + calc(n - 1, 0); 
}
 
ll cost(int ind) {
    ll ans = 0;
    if (ind != -1) {
        swap(ed[ind].u, ed[ind].v);
        ans += ed[ind].d;
    }
    ans += calc();
    if (ind != -1) {
        swap(ed[ind].u, ed[ind].v);
    }
    return ans;
}
 
ll ans = INF;
 
void run() {
	if (m <= 1000) {
	    for (int i = -1; i < m; i++)
	        chkmin(ans, cost(i));
	}
	else {
		chkmin(ans, calc());
	}
}
 
void write() {
    if (ans == INF) ans = -1;
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