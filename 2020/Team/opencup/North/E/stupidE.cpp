#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

int n, m;
vector<int> a, b;

int getAns(int pos) {
    int ans = 0;
    for (int i = 0; i <= pos; ++i) {
        ans = max(ans + b[i], a[i]);
    }
    return ans;
}

void solve() {
    a.resize(n);
    b.resize(n);
    for (auto& i : a) {
        cin >> i;
    }
    for (auto& i : b) {
        cin >> i;
    }
    while (m--) {
        int t;
        cin >> t;
        if (t == 1) {
            int pos, val;
            cin >> pos >> val;
            --pos;
            a[pos] = val;
        } else if (t == 2) {
            int pos, val;
            cin >> pos >> val;
            --pos;
            b[pos] = val;
        } else if (t == 3) {
            int pos;
            cin >> pos;
            --pos;
            cout << getAns(pos) << "\n";
        } else {
            assert(false);
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cout.setf(ios::fixed), cout.precision(20);
    while (cin >> n >> m) {
        solve();
    }
    return 0;
}