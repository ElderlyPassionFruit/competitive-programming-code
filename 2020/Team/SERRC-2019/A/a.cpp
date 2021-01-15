#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

struct Pt{
    int x, y;
    Pt() {}
    Pt(int _x, int _y) {
        x = _x, y = _y;
    }
};

Pt operator-(const Pt& a, const Pt& b) {
    return Pt(a.x - b.x, a.y - b.y);
}

int dist(const Pt& a) {
    int ans = max((int)sqrt(a.x * a.x + a.y * a.y) - 2, 0);
    while (ans * ans < a.x * a.x + a.y * a.y) {
        ++ans;
    }
    return ans;
}

int dist(const Pt& a, const Pt& b) {
    return dist(a - b);
}

struct Edge{
    int to, len, cost;
};

const int N = 1e3 + 10, B = 110;
Pt p[N];
int t, n, b;
int c[N];
vector<Edge> g[N];
vector<pair<int, int>> edges[N];


void read() {
    cin >> p[0].x >> p[0].y >> p[1].x >> p[1].y;
    cin >> b;
    cin >> c[0];
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        cin >> c[i];
    }
    cin >> n;
    n += 2;
    for (int i = 2; i < n; ++i) {
        cin >> p[i].x >> p[i].y;
        int sz;
        cin >> sz;
        for (int j = 0; j < sz; ++j) {
            int v, type;
            cin >> v >> type;
            v += 2;
            edges[i].push_back({v, type});
            edges[v].push_back({i, type});
        }
    }
}

void buildG() {
    for (int i = 1; i < n; ++i) {
        int len = dist(p[0], p[i]);
        g[0].push_back({i, len, len * c[0]});
    }
    for (int i = 2; i < n; ++i) {
        int len = dist(p[i], p[1]);
        g[i].push_back({1, len, len * c[0]});
    }
    for (int i = 0; i < n; ++i) {
        for (auto [v, type] : edges[i]) {
            int len = dist(p[i], p[v]);
            g[i].push_back({v, len, len * c[type]});
            g[v].push_back({i, len, len * c[type]});
        }
    }
    /*for (int i = 0; i < n; ++i) {
        cout << "v = " << i << endl;
        for (auto [to, len, cost] : g[i]) {
            cout << "to = " << to << " len = " << len << " cost = " << cost << endl;
        }
    }
    cout << endl;*/
}

const int INF = 1e9 + 228;
int dp[N][B];
queue<pair<int, int>> q;

void relax(int v, int len, int w) {
    if (len > b) return;
    if (dp[v][len] <= w) return;
    dp[v][len] = w;
    q.push({v, len});
}

void bfs() {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < B; ++j) {
            dp[i][j] = INF;
        }
    }
    relax(0, 0, 0);
    while (!q.empty()) {
        auto [v, myLen] = q.front();
        q.pop();
        for (auto [to, len, cost] : g[v]) {
            relax(to, len + myLen, dp[v][myLen] + cost);
        }
    }
}

void makeAns() {
/*
    cout << "dp = " << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= b; ++j) {
            cout << (dp[i][j] == INF ? -1 : dp[i][j]) << " ";
        }
        cout << endl;
    }*/

    int ans = INF;
    for (int i = 0; i < B; ++i) {
        ans = min(ans, dp[1][i]);
    }
    if (ans == INF) {
        ans = -1;
    }
    cout << ans << endl;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    read();
    buildG();
    bfs();
    makeAns();
    return 0;
}