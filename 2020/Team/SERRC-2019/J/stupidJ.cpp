#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int MAXN = 52;
const ll mod = 1e9 + 7;

ll dp[MAXN][MAXN];

ll calc(int L, int R, const vector<int> &a){
    if (L > R){
        return 1;
    }
    if (dp[L][R] != -1){
        return dp[L][R];
    }
    int mn = 1e7;
    for (int i = L; i <= R; i++){
        mn = min(mn, a[i]);
    }
    dp[L][R] = 0;
    for (int i = L; i <= R; i++){
        if (a[i] == mn){
            ll val = calc(L, i - 1, a) * calc(i + 1, R, a);
            val %= mod;
            dp[L][R] += val;
            dp[L][R] %= mod;
        }
    }
    return dp[L][R];
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cout.setf(ios::fixed), cout.precision(20);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            dp[i][j] = -1;
        }
    }
    cout << calc(0, n - 1, a) << endl;
    return 0;
}