#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

bool check(vector<int> p, vector<int> a) {
    for (int i = 0; i + 1 < p.size(); ++i) {
        if (a[p[i]] == a[p[i + 1]]) {
            return false;
        }
    }
    return true;
}

int calc(vector<int> p) {
    int ans = 0;
    for (int i = 0; i + 1 < p.size(); ++i) {
        if (abs(p[i] - p[i + 1]) > 1) {
            ++ans;
        }
    }
    return ans;
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& i : a) {
        cin >> i;
    }
    int ans = n;
    vector<int> p(n);
    iota(all(p), 0);
    do {
        if (check(p, a)) {
            chkmin(ans, calc(p));
        }
    } while (next_permutation(all(p)));
    if (ans == n) {
        ans = -1;
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