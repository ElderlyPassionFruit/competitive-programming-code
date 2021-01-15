#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

const int MOD = 998244353;

int add(int a, int b) {
    a += b;
    if (a >= MOD) return a - MOD;
    return a;
}

int mul(int a, int b) {
    return (ll) a * b % MOD;
}

int n, k;
vector<vector<int>> a;

void read() {
    cin >> n >> k;
    a.resize(n, vector<int>(n, 0));
    for (auto& i : a) {
        for (auto& j : i) {
            cin >> j;
        }
    }
}

/*
set<vector<vector<int>>> used;

vector<vector<int>> swapR(int i, int j, vector<vector<int>> a) {
    swap(a[i], a[j]);
    return a;
}

vector<vector<int>> swapC(int i, int j, vector<vector<int>> a) {
    for (int x = 0; x < n; ++x) {
        swap(a[x][i], a[x][j]);
    }
    return a;
}

void dfs(vector<vector<int>> a) {
    if (used.count(a)) return;
    used.insert(a);
    for (int i = 0; i < n; ++i) {
        for (int x = 0; x < n; ++x) {
            for (int y = x + 1; y < n; ++y) {
                if (a[i][x] + a[i][y] <= k) {
                    dfs(swapC(x, y, a));
                }
                if (a[x][i] + a[y][i] <= k) {
                    dfs(swapR(x, y, a));
                }
            }
        }
    }
}

int brute() {
    dfs(a);
    return used.size();
}
*/

int ans;

void turn() {
    vector<vector<int>> ans = a;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            a[i][j] = ans[j][i];
        }
    }
}

int f(int x) {
    if (x == 1) return 1;
    return mul(f(x - 1), x);
}

bool check(int x, int y) {
    for (int i = 0; i < n; ++i) {
        if (a[i][x] + a[i][y] > k) {
            return false;
        }
    }
    return true;
}

vector<bool> used;
int comp;

void dfs(int x) {
    comp++;
    used[x] = true;
    for (int i = 0; i < n; ++i) {
        if (used[i]) continue;
        if (!check(i, x)) continue;
        dfs(i); 
    }
}

int solve() {
    used.assign(n, false);
    int ans = 1;
    for (int i = 0; i < n; ++i) {
        if (used[i]) continue;
        comp = 0;
        dfs(i);
        ans = mul(ans, f(comp));
    }
    return ans;
}

void run() {
    //ans = brute();
    ans = 1;
    ans = mul(ans, solve());
    //cout << "ans = " << ans << endl;
    turn();
    ans = mul(ans, solve());
}

void write() {
    cout << ans << endl;
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
    read();
    run();
    write();
    return 0;
}