#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

const int N = 20;

int a[N][N];

bool check(int x, int y) {
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            if (a[i][j] == a[i][y] && a[x][j] == a[x][y]) return true;
            if (a[i][j] == a[x][j] && a[i][y] == a[x][y]) return true;
        }
    }
    return false;
}

bool rec(int n, int m, int x, int y) {
    if (x == n) return true;
    int nx = x, ny = y;
    if (ny + 1 < m) ++ny;
    else ++nx, ny = 0;

    for (int i = 0; i < 3; ++i) {
        a[x][y] = i;
        if (check(x, y)) continue;
        if (rec(n, m, nx, ny)) return true;
    }
    return false;
}  

bool solve(int n, int m) {
    return rec(n, m, 0, 0);
}

ll pows[N * N];

int get(int m, int x, int y) {
    return x * m + y + 1;
} 

ll recAns(int n, int m, int x, int y) {
    if (x == n) return 0;
    int nx = x, ny = y;
    if (ny + 1 < m) ++ny;
    else ++nx, ny = 0;
    ll ans = 0;
    for (int i = 0; i < 3; ++i) {
        a[x][y] = i;
        if (check(x, y)) {
            ans += pows[n * m - get(m, x, y)];
        } else {
            ans += recAns(n, m, nx, ny);
        }
    }
    return ans;
}

ll getAns(int n, int m) {
    return recAns(n, m, 0, 0);
}

const int MOD = 1e9 + 7;

void read() {
    pows[0] = 1;
    for (int i = 1; i < N * N; ++i) {
        pows[i] = pows[i - 1] * 3;
    }
    for (int n = 1; n <= 20; ++n) {
        for (int m = 1; m <= n; ++m) {
            if (n == 1 || m == 1) continue;
            if (solve(n, m)) {
                cout << "else if (n == " << n << " && m == " << m << ")" << " cout << " << getAns(n, m) % MOD << " << endl;" << endl;
            }
        }
    }
}

void run() {

}

void write() {

}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
    read();
    run();
    write();
    return 0;
}