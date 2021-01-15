#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int MAXN = 2e5 + 10;
#define int ll
int dp[MAXN][2][2];
vector<int> g[MAXN];
int n;
int w[MAXN];
ll ans;
ll cnt;

void dfs(int v, int p) {
    for (auto i : g[v]) {
        if (i != p) {
            dfs(i, v);
        }
    }

    for (auto i : g[v]) {
        if (i != p) {
            dp[v][0][0] += dp[i][1][0]; 
            dp[v][0][1] += dp[i][1][1];
            
            dp[v][1][0] += dp[i][0][0]; 
            dp[v][1][1] += dp[i][0][1]; 
        }
    }

    /*cout << "v = " << v << endl;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            cout << dp[v][i][j] << " ";
        } 
    }
    cout << endl;
    cout << endl;*/

    for (auto i : g[v]) {
        if (i != p) {
            dp[v][0][0] -= dp[i][1][0]; 
            dp[v][0][1] -= dp[i][1][1];
            dp[v][1][0] -= dp[i][0][0]; 
            dp[v][1][1] -= dp[i][0][1]; 
            
            for (int f1i = 0; f1i < 2; f1i++) {
                for (int f2i = 0; f2i < 2; f2i++) {
                    for (int f1v = 0; f1v < 2; f1v++) {
                        for (int f2v = 0; f2v < 2; f2v++) {
                            if ((f1i + f1v + 1) % 2 != (f2i + f2v) % 2) {
                                //cout << "puh" << endl;
                                ans += (ll)dp[v][f1v][f2v] * dp[i][f1i][f2i]; 
                            }
                        }
                    }
                }
            }

            dp[v][0][0] += dp[i][1][0]; 
            dp[v][0][1] += dp[i][1][1];
            dp[v][1][0] += dp[i][0][0]; 
            dp[v][1][1] += dp[i][0][1];    
        }
    }

    cnt += dp[v][0][w[v] ^ 1];
    cnt += dp[v][1][w[v]];

    dp[v][0][w[v]]++;
} 

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cout.precision(20);
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    for (int i = 0; i < n; i++) {
        cin >> w[i];
        w[i] = __builtin_popcount(w[i]);
        w[i] %= 2;
    }
    /*cout << "w = " << endl;
    for (int i = 0; i < n; i++)
        cout << w[i] << " ";
    cout << endl;*/

    ans = cnt = 0;
    dfs(0, 0);
    //cout << ans << " " << cnt << endl;
    cout << ans / 2 + cnt << endl;
    return 0;
}