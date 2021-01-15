#include <bits/stdc++.h>

using namespace std;

const int inf = 1e9;

int main() {
#ifdef iq
    freopen("a.in", "r", stdin);
#endif // iq
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector <int> dp(n + 1, inf);
    dp[0] = 0;
    map <int, int> when;
    int x = 0;
    when[0] = -1;
    map <int, int> best;
    best[0] = 1;
    for (int i = 0; i < n; i++) {
        x += (s[i] == '(' ? 1 : -1);
        int cost = inf;
        if (best.count(x)) {
            cost = min(cost, best[x] + i);
        }
        if (when.count(x) && (!when.count(x - 1) || when[x] > when[x - 1])) {
            cost = min(cost, dp[when[x] + 1]);
        }
        when[x] = i;
        dp[i + 1] = cost;
        if (!best.count(x)) best[x] = dp[i + 1] - i;
        else best[x] = min(best[x], dp[i + 1] - i);
    }
    if (dp[n] == inf) dp[n] = -1;
    cout << dp[n] << endl;
}
