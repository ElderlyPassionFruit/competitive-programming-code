#include <bits/stdc++.h>

using namespace std;
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n, k;
vector<int> a;

void read() {
    cin >> n >> k;
    a.resize(n);
    for (auto &i : a)
        cin >> i;
}

void run() {
    vector<vector<long long> > dp(n, vector<long long> (k, 0));
    vector<vector<int> > help(n, vector<int> (n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (j > 0)
            help[i][j] = help[i][j - 1];
            help[i][j] |= a[j];
        }
    }
    for (int i = 0; i < n; i++) {
        dp[i][0] = help[0][i];
        for (int j = 1; j < k; j++) {
            for (int pos = 0; pos < i; pos++) {
                chkmax(dp[i][j], dp[pos][j - 1] + help[pos + 1][i]);
            }
        }
    }
    cout << dp[n - 1][k - 1] << endl;
}

void write() {
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    read();
    run();
    write();
    return 0;
}
