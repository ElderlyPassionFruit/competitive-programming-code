#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cout.setf(ios::fixed), cout.precision(20);
    vector<pair<int, int>> a;
    for (int i = 0; i <= 200; ++i) {
        for (int j = 0; j <= 200; ++j) {
            a.push_back({i, j});
        }
    }
    cout << a.size() << endl;
    for (auto i : a) {
        cout << i.first << " " << i.second << endl;
    }
    return 0;
}