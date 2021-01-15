#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()
#define int ll

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cout.setf(ios::fixed), cout.precision(20);
    int sum, n, m;
    cin >> sum >> n >> m;
    map<int, int> must;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        must[a] = b;
    }
    vector<vector<bool>> dp(sum + 1, vector<bool> (sum + 1, false));
    for (int val = 0; val <= sum; val++) {
        dp[val][0] = 1;
    }
    /*cout << "dp = " << endl;
    for (auto i : dp) {
        for (auto j : i) {
            cout << j << " ";
        }
        cout << endl;
    }*/
    for (int i = 1; i <= n; i++) {
        vector<vector<bool>> ndp(sum + 1, vector<bool> (sum + 1, false));
        for (int val = 0; val <= sum; val++) {
            if (must.count(i) && must[i] != val) continue;
            for (int mySum = val; mySum <= sum; mySum++) {
                //cout << "i = " << i << " val = " << val << " mySum = " << mySum << endl;
                for (int dx = -1; dx <= 1; dx++) {
                    int prevVal = val + dx;
                    if (prevVal < 0 || prevVal > sum) continue;
                    int prevSum = mySum - val;
                    if (prevSum == 0)
                  //  cout << "prevVal = " << prevVal << " prevSum = " << prevSum << endl;
                    if (prevSum < 0 || prevSum > sum) continue;
                    if (!dp[prevVal][prevSum]) continue;
                    ndp[val][mySum] = 1;
                }
            }
        }
        dp = ndp;
       /* cout << "dp = " << endl;
        for (auto i : dp) {
            for (auto j : i) {
                cout << j << " ";
            }
            cout << endl;
        }
        cout << endl;*/
    }
    bool ans = false;
    for (int val = 0; val <= sum; val++) {
        ans |= dp[val][sum];
    }
    if (ans) {
        cout << "Yes";
    } else {
        cout << "No";
    }
    return 0;
}