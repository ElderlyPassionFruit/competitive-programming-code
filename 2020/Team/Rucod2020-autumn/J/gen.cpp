#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

int get(int l, int r) {
    return rnd() % (r - l + 1) + l;
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cout.setf(ios::fixed), cout.precision(20);
    int n = get(2, 10);
    int m = get(0, 10);
    int k = get(1, 5);
    cout << n << " " << m << " " << k << endl;
    vector<int> order(n);
    iota(all(order), 0);
    shuffle(all(order), rnd);
    for (int i = 0; i < m; ++i) {
        int u = get(1, n - 1);
        int v = get(u + 1, n);
        cout << order[u - 1] + 1 << " " << order[v - 1] + 1 << endl;
    }
    return 0;
}