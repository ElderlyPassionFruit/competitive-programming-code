#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

char getInv(char x) {
    if (x == 'L') return 'W';
    return 'L';
}

string make(string s, int mask, int n) {
    for (int i = 0; i < n; ++i) {
        if ((mask >> i) & 1) {
            s[i] = getInv(s[i]);
        }
    }
    return s;
}

int calc(string s) {
    int ans = 0;
    char last = 'L';
    for (auto i : s) {
        if (i == 'L') {
            last = i;
        } else {
            if (last == 'L') {
                ++ans;
            } else {
                ++ans;
                ++ans;
            }
            last = 'W';
        }
    }
    return ans;
}

void solve() {
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    int ans = 0;
    for (int mask = 0; mask < (1 << n); ++mask) {
        if (__builtin_popcount(mask) > k) continue;
        chkmax(ans, calc(make(s, mask, n)));
    }
    cout << ans << endl;
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}