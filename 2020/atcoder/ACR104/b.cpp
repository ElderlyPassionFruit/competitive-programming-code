#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

const int N = 5e3 + 10;
int n;
string s;

void read() {
    cin >> n >> s;
}

int pref[N][4];

int get(char x) {
    if (x == 'A') return 0;
    if (x == 'T') return 1;
    if (x == 'C') return 2;
    if (x == 'G') return 3;
    assert(false);
    return -1;
}

void init() {
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < 4; ++j) {
            pref[i][j] = pref[i - 1][j];
        }
        pref[i][get(s[i - 1])]++; 
    }
}

int get(int l, int r, int t) {
    return pref[r][t] - pref[l -1 ][t];
}

bool check(int l, int r) {
    return get(l, r, 0) == get(l, r, 1) && get(l, r, 2) == get(l, r, 3);
}

int ans;

void run() {
    init();
    ans = 0;
    for (int l = 1; l <= n; ++l) {
        for (int r = l + 1; r <= n; ++r) {
            ans += check(l, r);
        }
    }
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