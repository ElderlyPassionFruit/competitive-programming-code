#include <bits/stdc++.h>

using namespace std;
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct state{
    int mask, a, b;
};

void no() {
    cout << "NO\n";
    exit(0);
}

void yes() {
    cout << "YES\n";
    exit(0);
}

int n, m, a, b;
void read() {
    cin >> n >> m >> a >> b;
    if (n > m)
        swap(n, m);
    if (n * m != (a + b) * 3) {
        no();   
    }
}

bool operator<(const state & a, const state & b) {
    return tie(a.mask, a.a, a.b) < tie(b.mask, b.a, b.b);
}

bool operator==(const state & a, const state & b) {
    return tie(a.mask, a.a, a.b) == tie(b.mask, b.a, b.b);
}

void make(vector<state> & a) {
    sort(a.begin(), a.end());
    a.resize(unique(a.begin(), a.end()), a.end());
    //a.erase(unique(a.begin(), a.end()), a.end());
}

void make(vector<state> & ans, const state & mask, int x, int da, int db) {
    if (mask.mask & x)
        return;
    ans.push_back({(mask.mask | x) >> 1, mask.a + da, mask.b + db});
}

void calc(vector<state> & ans, const state & mask, int pos) {
    if (pos + 2 < n) {
        make(ans, mask, (1 << 1) | (1 << 2), 1, 0);
    }
    make(ans, mask, (1 << n) | (1 << (2 * n)), 1, 0);
    if (pos + 1 < n) {
        make(ans, mask, (1 << 1) | (1 << n), 0, 1);
        make(ans, mask, (1 << 1) | (1 << (n + 1)), 0, 1);
        make(ans, mask, (1 << n) | (1 << (n + 1)), 0, 1);
    }
    if (pos - 1 >= 0) {
        make(ans, mask, (1 << n) | (1 << (n - 1)), 0, 1);
    }
}

void solve(vector<state> & mask) {
    vector<state> ans;
    for (int i = 0; i < n; i++) {
        for (auto j : mask) {
            if (j.mask & 1) {
                ans.push_back({j.mask >> 1, j.a, j.b});
                continue;
            }
            calc(ans, j, i);
        }
        make(ans);
        mask = ans;
        ans.clear();
    }
}

vector<state > mask;
bool flag = false;

void run() {
    mask.push_back({0, 0, 0});
    for (int i = 0; i < m; i++) {
        solve(mask);
    }
}

void write() {
    state fans = {0, a, b};
    for (auto i : mask)
        flag |= (i == fans);
    if (flag)
        yes();
    else
        no();
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