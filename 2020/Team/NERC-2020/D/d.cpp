#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int N = 3e5 + 10;
int n;
string a[N];

int calc(int i, int j) {
    int cnt = 0;
    for (int x = 0; x < a[i].size(); ++x) {
        cnt += a[i][x] == a[j][x];
    }
    return cnt;
}

bool check(int i, int j) {
    return abs(i - j) <= calc(i, j);
}

bool dp[N];

void solve(int n) {
    fill(dp, dp + n, false);
    for (int i = n - 1; i >= 0; --i) {
        for (int d = 1; d <= 8 && i + d <= n - 1; ++d) {
            if (check(i, i + d)) {
                if (!dp[i + d]) {
                    dp[i] = 1;
                }
            }
        }
    }
    /*
    cout << "dp = " << endl;
    for (int i = 0; i < n; ++i) {
        cout << dp[i] << " ";
    }
    cout << endl;*/
    if (dp[0]) {
        cout << 1;
    } else {
        cout << 2;
    }
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; ++i) {
        solve(i);
    }
	return 0;
}