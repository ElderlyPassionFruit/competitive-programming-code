#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <cassert>
using ll = long long;
using ull = unsigned long long;
using ld = long double;
using namespace std;

template <typename T1, typename T2> inline void chkmin(T1& x, const T2& y) { if (y < x) x = y; }
template <typename T1, typename T2> inline void chkmax(T1& x, const T2& y) { if (x < y) x = y; }
#define int ll
const int MAXN = 5e5 + 10;
vector<int> g[MAXN];
int n;
int deg[MAXN];
int w[MAXN];

void read() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        if (a == 0) continue;
        g[a].push_back(i);
        deg[i]++;
    }
    for (int i = 1; i <= n; i++) {
        if (!deg[i]) {
            g[0].push_back(i);
        }
    }
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
    }
}

void no() {
    cout << -1 << endl;
    exit(0);
}

bool used[MAXN];
int p[MAXN];
int h[MAXN];

void dfs(int v, int par) {
    used[v] = true;
    p[v] = par;
    h[v] = h[par] + 1;
    for (auto i : g[v]) {
        if (i == par) continue;
        if (used[i]) no();
        dfs(i, v);
    }
}

void check() {
    dfs(0, 0);
    for (int i = 0; i <= n; i++) {
        if (!used[i]) {
            no();
        }
    }
}

int gcd(int a, int b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

struct num {
    int x, y;
    num() {
        x = 0, y = 0;
    }
    num(int a) {
        x = a, y = 1;
    }
    num(int a, int b) {
        x = a;
        y = b;
    }
};

bool operator<(const num& a, const num& b) {
    return a.x * b.y < a.y * b.x;
}

num operator+(const num& a, const num& b) {
    return num(a.x + b.x, a.y + b.y);
}

int dsu[MAXN], sz[MAXN], fans[MAXN], sum[MAXN];
num have[MAXN];
set<pair<num, int>> q;

void build() {
    for (int i = 1; i <= n; i++) {
        dsu[i] = i;
        sz[i] = 1;
        fans[i] = w[i];
        sum[i] = w[i];
        have[i] = num(w[i]);
        q.insert({ have[i], i });
    }
}

int get_par(int v) {
    if (dsu[v] == v) return v;
    return dsu[v] = get_par(dsu[v]);
}

void uni(int a, int b) {
    int pa = get_par(a);
    int pb = get_par(b);
    assert(pa != pb);
    assert(q.count({ have[pb], pb }));
    q.erase({ have[pb], pb });
    if (get_par(0) == pa) {
        have[pa] = have[pa] + have[pb];
    }
    else {
        assert(q.count({ have[pa], pa }));
        q.erase({ have[pa], pa });
        have[pa] = have[pa] + have[pb];
        q.insert({ have[pa], pa });
    }
    fans[pa] = fans[pa] + sum[pb] * sz[pa] + fans[pb];
    dsu[pb] = pa;
    sum[pa] += sum[pb];
    sz[pa] += sz[pb];
}

int ans;

void solve() {
    while (!q.empty()) {
        auto x = *q.begin();
        uni(p[x.second], x.second);
    }
    ans = fans[get_par(0)];
}

void run() {
    check();
    build();
    solve();
}

void write() {
    cout << ans << endl;
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    read();
    run();
    write();
    return 0;
}


/*
WA 559
input = 
7
2 0 6 0 2 7 4 
2 2 1 2 1 1 1 

ans = 
41

out = 
39
*/