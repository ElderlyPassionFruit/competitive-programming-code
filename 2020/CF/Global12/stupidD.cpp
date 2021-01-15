#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

bool check(int k, vector<int> a) {
    vector<int> b;
    for (int i = 0; i + k - 1 < a.size(); ++i) {
        b.push_back(*min_element(a.begin() + i, a.begin() + i + k));
    }
    int sz = b.size();
    sort(all(b));
    b.resize(unique(all(b)) - b.begin());
    return b.size() == sz && b[0] == 1 && b[b.size() - 1] == b.size();
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& i : a) {
        cin >> i;
    }
    for (int k = 1; k <= n; ++k) {
        cout << check(k, a);
    }
    cout << endl;
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