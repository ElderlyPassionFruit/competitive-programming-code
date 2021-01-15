#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int N = 1e5 + 10, LOG = 20;
int n, m;
vector<int> g[N];
vector<int> mark[N];
pair<int, int> path[N];
bool used[N];

int dp[N][LOG], tin[N], tout[N], timer = 0;
int h[N];

void dfs(int v, int p) {
    tin[v] = timer++;
    dp[v][0] = p;
    for (int i = 1; i < LOG; ++i) {
        dp[v][i] = dp[dp[v][i - 1]][i - 1];
    }
    for (auto i : g[v]) {
        if (i == p) continue;
        h[i] = h[v] + 1;
        dfs(i, v);
    }
    tout[v] = timer++;
}

bool isUpper(int v, int u) {
    return tin[v] <= tin[u] && tout[v] >= tout[u];
} 

int lca(int v, int u) {
    if (isUpper(v, u)) return v;
    if (isUpper(u, v)) return u;
    for (int i = LOG - 1; i >= 0; --i) {
        if (!isUpper(dp[v][i], u)) {
            v = dp[v][i];
        }
    }
    return dp[v][0];
}

int dist(int v, int u) {
    return h[v] + h[u] - 2 * h[lca(v, u)];
}

vector<int> getPath(int v, int u) {
    int l = lca(v, u);
    vector<int> a, b;
    while (v != l) {
        a.push_back(v);
        v = dp[v][0];
    }
    while (u != l) {
        b.push_back(u);
        u = dp[u][0];
    }
    a.push_back(l);
    reverse(all(b));
    for (auto i : b) {
        a.push_back(i);
    }
    return a;
}

void no() {
    cout << "No";
    exit(0);
}

bool check(int a, int b, int x) {
    //cerr << "a = " << a << " b = " << b << " x = " << x << endl;
    //cerr << dist(a, b) << " " << dist(a, x) << " " << dist(b, x) << endl;  
    //cerr << "dist(a, b) = " << dist(a, b) << " " << dist(a, x) << " " << dist(b, x) << endl;
    return dist(a, b) == dist(a, x) + dist(b, x);
}

bool check(int a, int b, int c, int d) {
    //cerr << "a = " << a << " b = " << b << " c = " << c << " d = " << d << endl;
    //cerr << dist(a, b) << " " << dist(c, d) << " " << check(a, b, c) << " " << check(a, b, d) << endl;
    return dist(a, b) >= dist(c, d) && check(a, b, c) && check(a, b, d);
}

void relax(int ind) {
    int u = path[ind].first;
    int v = path[ind].second;
    auto myPath = getPath(u, v);
    set<int> have;
    vector<int> st;

    /*cerr << "myPath = " << endl;
    for (auto i : myPath) {
        cerr << i << " ";
    }
    cerr << endl;*/

    //int id = 0;
    for (auto i : myPath) {
        //cerr << "i = " << i << endl;
        vector<int> add;
        vector<int> del;
        for (auto x : mark[i]) {
            assert(!used[x]);
            if (have.count(x)) {
                del.push_back(x);
            } else {
                add.push_back(x);
                have.insert(x);
            }
        }
        /*cerr << "add = " << endl;
        for (auto x : add) {
            cerr << x << " ";
        }
        cerr << endl;*/
        reverse(all(del));
        for (auto x : add) {
            if (st.empty()) {
                st.push_back(x);
            } else {
                int a = path[st.back()].first;
                int b = path[st.back()].second;
                int c = path[x].first;
                int d = path[x].second;
                //cerr << a << " " << b << " " << c << " " << d << endl;
                if (!check(a, b, c, d)) {
                    //cerr << "puhh" << endl;
                    no();
                }
                st.push_back(x);
            }
        }
        for (auto x : del) {
            if (st.empty()) no();
            if (st.back() != x) no();
            st.pop_back();
        }
    }
    //cerr << "puhh" << endl;
    if (!st.empty()) no();
    for (auto i : myPath) {
        for (auto x : mark[i]) {
            used[x] = true;
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cerr.tie(0);
    cerr.setf(ios::fixed), cerr.precision(20);
    cin >> n >> m;
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int i = 0; i < m; ++i) {
        cin >> path[i].first >> path[i].second;
        path[i].first--;
        path[i].second--;
    }
    dfs(0, 0);
    sort(path, path + m, [&](pair<int, int> a, pair<int, int> b) {
        return dist(a.first, a.second) > dist(b.first, b.second);
    });
    /*cerr << "path = " << endl;
    for (int i = 0; i < m; ++i) {
        cerr << path[i].first << " " << path[i].second << endl;
    }*/
    fill(used, used + m, false);
    for (int i = 0; i < m; ++i) {
        mark[path[i].first].push_back(i);
        mark[path[i].second].push_back(i);
    }
    /*cerr << "marks = " << endl;
    for (int i = 0; i < n; ++i) {
        for (auto x : mark[i]) {
            cerr << x << " ";
        }
        cerr << endl;
    }*/
    for (int i = 0; i < m; ++i) {
        if (!used[i]) {
            relax(i);
        }
    }

    cout << "Yes";
    return 0;
}