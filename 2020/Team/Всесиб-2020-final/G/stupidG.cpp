#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

int n;
vector<int> a;
vector<int> t;

int get(int pos) {
    return a[pos] + t[pos];
}

int get() {
    int pos = 0;
    for (int i = 0; i < n; ++i) {
        if (get(i) > get(pos)) {
            pos = i;
        }
    }
    return pos;
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cout.precision(20);
    int T;
    cin >> n >> T;
    a.resize(n);
    for (auto& i : a) {
        cin >> i;
    }
    t.assign(n, 0);
    vector<int> ans(n, 0);
    for (int i = 0; i < T; ++i) {
        int pos = get();
        t[pos] = 0;
        ans[pos]++;
        for (int j = 0; j < n; ++j) {
            if (j == pos) continue;
            t[j]++;
        }
    }
    for (auto i : ans) {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}