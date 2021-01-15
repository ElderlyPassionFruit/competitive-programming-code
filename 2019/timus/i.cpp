#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int MAXN = 5e3 + 10;
int a[MAXN][MAXN];
int n, m;

int dp1[MAXN][MAXN];

int solve(vector<int> & a) {
    vector<pair<int, int>> st;
    int ans = 0;
    for (int i = 0; i < (int)a.size(); i++) {
        while (!st.empty() && st.back().first >= a[i]) {
            st.pop_back();
        }
        int x = -1;
        if (!st.empty())
            x = st.back().second;
        ans = max(ans, a[i] * (i - x));
        st.push_back({a[i], i});
    }
    return ans;
}

signed main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = m - 1; j >= 0; j--) {
            if (a[i][j]) continue;
            dp1[i][j] = dp1[i][j + 1] + 1;
        }
    }

    int ans = 0;

    for (int j = 0; j < m; j++) {
        vector<int> have;
        for (int i = 0; i < n; i++) {
            have.push_back(dp1[i][j]);
        }
        ans = max(ans, solve(have));
    }

    cout << ans << endl;
    return 0;
}