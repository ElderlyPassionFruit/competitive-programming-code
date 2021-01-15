#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int N = 5e2 + 10;
int n, m;
int dist[N][N];
vector<int> g[N];

inline void chkmin(int& x, int y) {
    if (y < x) x = y;
}

inline void chkmax(int& x, int y) {
    if (x < y) x = y;
}

void build() {
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                chkmin(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    } 
    /*cout << "dist = " << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << dist[i][j] << " ";
        }
        cout << endl;
    }*/
    for (int i = 0; i < n; ++i) {
        sort(all(g[i]));
        g[i].resize(unique(all(g[i])) - g[i].begin());
    }
}

int now[N];
int topNow;
vector<int> gNow[N];

int findV() {
    int ansV = -1;
    int ansCnt = N;
    for (int i = 0; i < topNow; ++i) {
        int v = now[i];
        int fans = 0;
        for (auto u : gNow[v]) {
            int cnt = 0;
            for (int x = 0; x < topNow; ++x) {
                if (dist[v][x] > dist[u][x]) {
                    ++cnt;
                }
            }
            chkmax(fans, cnt);
        }
        if (fans >= ansCnt) continue;
        ansV = v;
        ansCnt = fans; 
    }
    assert(topNow != 0);
    assert(ansV != -1);
    return ansV;
}

int newNow[N];
int topNew;
vector<int> newG[N];
bool used[N];

void rebuild(int v, int to) {
    fill(used, used + n, false);
    topNew = 0;
    for (int i = 0; i < topNow; ++i) {
        int x = now[i];
        if (dist[v][x] < dist[to][x]) continue;
        newNow[topNew++] = x;
        used[x] = true;
    }
    topNow = 0;
    for (int i = 0; i < topNew; ++i) {
        now[topNow++] = newNow[i];
    }
    for (int i = 0; i < n; ++i) {
        newG[i].clear();
    }
    for (int i = 0; i < topNow; ++i) {
        int v = now[i];
        for (auto to : gNow[v]) {
            if (!used[to]) continue;
            newG[v].push_back(to);
        }
    }
    for (int i = 0; i < n; ++i) {
        gNow[i] = newG[i];
    }
}

int query(int v) {
    assert(v >= 0 && v < n);
    cout << v + 1 << endl;
    string ans;
    cin >> ans;
    if (ans == "FOUND") return -1;
    int fans;
    cin >> fans;
    return fans - 1;
}

void solve() {
    iota(now, now + n, 0);
    topNow = n;
    for (int i = 0; i < n; ++i) {
        gNow[i] = g[i];
    }
    for (int it = 0; it < 10; ++it) {
        int v = findV();
        int have = query(v);
        if (have == -1) {
            return;
        }
        rebuild(v, have);
    }
    assert(false);
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            dist[i][j] = N;
        }
        dist[i][i] = 0;
    }
    for (int i = 0; i < m; ++i) {
        int k;
        cin >> k;
        int v;
        cin >> v;
        --v;
        for (int i = 0; i < k - 1; ++i) {
            int u;
            cin >> u;
            --u;
            g[v].push_back(u);
            g[u].push_back(v);
            //cout << u << " " << v << endl;
            chkmin(dist[v][u], 1);
            chkmin(dist[u][v], 1);
            v = u;
        }
    }
    build();
    for (int i = 0; i < n; ++i) {
        solve();
    }
	return 0;
}