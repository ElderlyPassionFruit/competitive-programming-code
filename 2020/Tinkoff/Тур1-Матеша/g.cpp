#pragma GCC optimize("O3")
#include <bits/stdc++.h>

using namespace std;
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 5e7 + 10;
int n;

void read() {
    cin >> n;
    if (n == 1) {
        cout << 1;
        exit(0);
    }
}

int lp[MAXN];
int euler[MAXN];
int sz = 0;

void build() {
    for (int i = 1; i <= n; i++)
        lp[i] = i;
    euler[1] = 1;
    long long sum = 0;
    int need = min(100, n);
    for (int i = 2; i <= n; i++) {
        if (i + i <= n) {
            if (lp[i] == i) {
                for (int j = i + i; j <= n; j += i) {
                    chkmin(lp[j], i);
                }
            }
            if (lp[i] == i) {
                euler[i] = i - 1;
            } else {
                int x = i / lp[i];
                if (lp[i] == lp[x]) {
                    euler[i] = euler[x] * lp[i];
                } else {
                    euler[i] = euler[x] * (lp[i] - 1);
                }
            }
            sum += euler[i];
        }
        if (i == need) {
            cout << sum << " ";
            sum = 0;
            need += 100;
            chkmin(need, n);
        }
    }
}

void run() {
    build();
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    read();
    run();
    return 0;
}
