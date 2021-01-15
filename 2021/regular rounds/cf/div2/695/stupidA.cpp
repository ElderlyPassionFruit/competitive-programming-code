#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

string gen(int n, int i, int pos) {
    string ans(n, i + '0');
    for (int x = 0; x < n; ++x) {
        int add = abs(x - pos);
        int val = (i + add) % 10;
        ans[x] = val + '0';
    }
    return ans;
}

void solve() {
    int n;
    cin >> n;
    string ans(n, '0');
    for (int i = 0; i <= 9; ++i) {
        for (int pos = 0; pos < n; ++pos) {
            chkmax(ans, gen(n, i, pos));
        }
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