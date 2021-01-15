#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

pair<vector<int>, vector<int>> solve(vector<int> a, int A, int B, bool& ok) {
    if (A < 0 || B < 0) {
        ok = false;
        return {};
    }
    int n = a.size();
    vector<vector<short int>> dp(n + 1, vector<short int> (A + 1, -1));
    dp[0][0] = 0;
    for (int i = 0; i < n; i++) {
        for (int w = 0; w <= A; w++) {
            if (dp[i][w] == -1) continue;
            dp[i + 1][w] = 0;
            if (w + a[i] <= A) {
                dp[i + 1][w + a[i]] = 1;
            }
        }
    }
    int myA = -1;
    int sum = 0;
    for (auto i : a) {
        sum += i;
    }
    for (int w = 0; w <= A; w++) {
        if (dp[n][w] == -1) continue;
        if (sum - w > B) continue;
        myA = w;
        break;
    }
    if (myA == -1) {
        ok = false;
        return {};
    }
    ok = true;
    pair<vector<int>, vector<int>> ans;
    for (int i = n; i > 0; i--) {
        assert(dp[i][myA] != -1);
        if (dp[i][myA] == 0) {
            ans.second.push_back(i + 1);
        } else {
            ans.first.push_back(i + 1);
            myA -= a[i - 1];
        }
    }
    assert(myA == 0);
    return ans;
}

void outAns(vector<int> a1, vector<int> a2, int t) {
    cout << t << "\n";
    sort(all(a1));
    sort(all(a2));
    cout << a1.size();
    for (auto i : a1) {
        cout << " " << i;
    }
    cout << "\n";
    cout << a2.size();
    for (auto i : a2) {
        cout << " " << i;
    }
    cout << "\n";
    exit(0);
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    int n, A, B;
    cin >> n >> A >> B;
    vector<int> a(n);
    for (auto &i : a) {
        cin >> i;
    }
    int x = a[0];
    a.erase(a.begin());
    bool ok = true;
    auto fans = solve(a, A - x, B, ok);
    if (ok) {
        fans.first.push_back(1);
        outAns(fans.first, fans.second, 1);
    }
    ok = true;
    fans = solve(a, A, B - x, ok);
    if (ok) {
        fans.second.push_back(1);
        outAns(fans.first, fans.second, 2);
    }
    cout << -1 << "\n";
	return 0;
}