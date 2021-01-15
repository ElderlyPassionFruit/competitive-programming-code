#include <bits/stdc++.h>
#define int long long
#define double long double
#pragma GCC optimize("O3,Ofast,no-stack-protector,unroll-loops,fast-math")
#pragma GCC target("avx,avx2,sse")
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        sort(a.begin(), a.end());
        reverse(a.begin(), a.end());
        vector<int> b(k);
        for (int i = 0; i < k; i++) {
            cin >> b[i];
        }
        sort(b.begin(), b.end());
        vector<vector<int>> keks(k);
        int pos = 0;
        for (int i = 0; i < k; i++) {
            keks[i].push_back(a[pos++]);
        }
        for (int i = 0; i < k; i++) {
            while (keks[i].size() < b[i]) {
                keks[i].push_back(a[pos++]);
            }
        }
        int tot = 0;
        for (vector<int> kek : keks) {
            sort(kek.begin(), kek.end());
            tot += kek[0] + kek[kek.size() - 1];
        }
        cout << tot << '\n';
    }

    fflush(stdout);
    return 0;
}
