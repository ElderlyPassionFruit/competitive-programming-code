#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int N = 2e3 + 10;
string s, t;
int n, m;

int dp[N][N];

inline void chkmax(int& x, int y) {if (x < y) x = y;}

void solve() {
    //s += 'a' - 1;
    //t += 'z' + 1;
    n = s.size(), m = t.size();

    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            dp[i][j] = 0;
            if (i > 0) chkmax(dp[i][j], dp[i - 1][j]);
            if (j > 0) chkmax(dp[i][j], dp[i][j - 1]);
            if (i > 0 && j > 0 && s[i - 1] == t[j - 1]) chkmax(dp[i][j], dp[i - 1][j - 1] + 1); 
        }
    }

    /*for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }*/

    int ans = t.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (s[i] >= t[j]) continue;
            /*if (dp[i][j] + n - i + m - j == 4) {
                cout << i << " " << j << endl;
                cout << dp[i][j] << endl;
            }*/
            chkmax(ans, 2 * dp[i][j] + n - i + m - j);
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (s[i] != t[j]) continue;
            /*if (dp[i][j] + n - i + m - j == 4) {
                cout << i << " " << j << endl;
                cout << dp[i][j] << endl;
            }*/
            chkmax(ans, 2 * dp[i + 1][j + 1] + m - j - 1);
        }
    }
    cout << ans << '\n';
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    while (cin >> s >> t) {
        solve();
    }
	return 0;
}