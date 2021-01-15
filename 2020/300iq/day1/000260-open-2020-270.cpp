#include <bits/stdc++.h>

using namespace std;

const int inf = 1e9;

const int N = 2e6 + 7;

int when[N];
int best[N];

int main() {
#ifdef iq
    freopen("a.in", "r", stdin);
#endif // iq
    ios::sync_with_stdio(0);
    cin.tie(0);
    for (int i= 0; i < N; i++) best[i] = inf, when[i] = -inf;
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector <int> dp(n + 1, inf);
    dp[0] = 0;
    int x = n;
    when[x] = -1;
    best[x] = 1;
    for (int i = 0; i < n; i++) {
        x += (s[i] == '(' ? 1 : -1);
        int cost = inf;
        cost = min(cost, best[x] + i);
        if (when[x] != -inf && (when[x - 1] == -inf || when[x] > when[x - 1])) {
            cost = min(cost, dp[when[x] + 1]);
        }
        when[x] = i;
        dp[i + 1] = cost;
        best[x] = min(best[x], dp[i + 1] - i);
    }
    if (dp[n] == inf) dp[n] = -1;
    cout << dp[n] << endl;
}
