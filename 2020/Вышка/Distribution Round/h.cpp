#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

const int N = 2e5 + 10;
int n;
vector<int> g[N];

void read() {
    for (int i = 0; i < n; ++i) {
        g[i].clear();
    }
    for (int i = 0; i < n; ++i) {
        int v;
        cin >> v;
        --v;
        g[i].push_back(v);
        g[v].push_back(i);
    }
}

vector<int> cycle;
bool used[N];
int par[N];

void buildCycle(int u, int v) {
    while (u != v) {
        cycle.push_back(v);
        v = par[v];
    }
    cycle.push_back(v);
}

void dfsCycle(int v, int p) {
    used[v] = true;
    par[v] = p;
    for (auto i : g[v]) {
        if (i == p) continue;
        if (!cycle.empty()) return;
        if (used[i]) {
            buildCycle(i, v);
        } else {
            dfsCycle(i, v);
        }
    }
}

vector<int> order[N];

void dfsTin(int v, int p, int root) {
    par[v] = p;
    for (auto i : g[v]) {
        if (i == p) continue;
        if (used[i]) continue;
        dfsTin(i, v, root);
    }
    order[root].push_back(v);
}

void buildOrder(int v) {
    dfsTin(v, -1, v);
}

void findCycle() {
    cycle.clear();
    fill(used, used + n, false);
    dfsCycle(0, 0);
    fill(used, used + n, false);
    for (auto i : cycle) {
        used[i] = true;
    }
    for (int i = 0; i < n; ++i) {
        order[i].clear();
    }
    for (auto i : cycle) {
        buildOrder(i);
        /*cout << "i = " << i << endl;
        cout << "order[i] = " << endl;
        for (auto x : order[i]) {
            cout << x << " ";
        }
        cout << endl;*/
    }
}

int sz[N];
bool ok[N];

void dfsCheck(int root, int k) {
    for (auto v : order[root]) {
        ok[v] = true;
        int sum = 1 % k;
        sz[v] = 1 % k;
        for (auto i : g[v]) {
            if (i == par[v]) continue;
            if (used[i]) continue;
            sz[v] += sz[i];
            sum += sz[i];
            if (sz[v] >= k) sz[v] -= k;
            if (sum >= k) sum -= k;
            ok[v] &= ok[i];
            if (!ok[v]) break;
        }
        if (sz[v] == 0 && sum == k) {
            continue;
        }
        if (sz[v] == sum) {
            continue;
        }
        ok[v] = false;
    }
}

int a[2 * N];
int dp[2 * N];
int pref[2 * N];

int getSum(int l, int r) {
    if (r < l) return 0;
    return pref[r] - (l > 0 ? pref[l - 1] : 0);
}

bool calcDp(int k) {
    fill(dp, dp + 2 * (int)cycle.size() + 10, 0);
    int sum = 0;
    for (int i = 0; i < (int)cycle.size(); ++i) {
        a[i] = a[i + cycle.size()] = sz[cycle[i]];
        sum += a[i];
    }

    for (int i = 0; i < 2 * (int)cycle.size(); ++i) {
        pref[i] = a[i];
        if (i > 0) {
            pref[i] += pref[i - 1];
        }
    }

    int r = 2 * (int)cycle.size() - 1;
    if (dp[r + 1] == sum) return true;
    for (int l = 2 * (int)cycle.size() - 1; l >= 0; --l) {
        if (getSum(l, r) < k) continue;
        while (getSum(l, r) > k) --r;
        if (getSum(l, r) == k) {
            dp[l] = k + dp[r + 1];
            if (dp[l] == sum) return true;
        }
    }
    return false;
}

bool check(int k) {
    for (auto v : cycle) {
        dfsCheck(v, k);
        if (!ok[v]) {
            return false;
        }
    }
    return calcDp(k);
}

int ans;

void run() {
    findCycle();
    ans = 0;
    for (int k = 1; k <= n; ++k) {
        if (n % k) continue;
        ans += check(k);
    }
}

void write() {
    cout << ans << "\n";
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
    while (cin >> n) {
        read();
        run();
        write();
    }
    return 0;
}