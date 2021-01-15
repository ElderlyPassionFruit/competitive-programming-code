#include <bits/stdc++.h>

using namespace std;
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const long long INF = 1e18 + 7;
const int MAXN = 2e3 + 10;
long long dp[MAXN][MAXN], sum[MAXN][MAXN];
int mid[MAXN][MAXN];
int n;
int arr[MAXN];

void read() {
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
}

void build() {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j <= n; j++) {
            sum[i][j] = sum[i][j - 1] + arr[j - 1];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j <= n; j++) {
            dp[i][j] = INF;
        }
    }
}

void calc() {
    for (int r = 1; r <= n; r++) {
        for (int l = r - 1; l >= 0; l--) {
            if (l == r - 1) {
                dp[l][r] = arr[l];
                mid[l][r] = l;
                continue;
            }
            for (int m = mid[l][r - 1]; m <= mid[l + 1][r]; m++) {
                chkmin(dp[l][r], dp[l][m] + dp[m][r] + sum[l][r]);
                if (dp[l][r] == dp[l][m] + dp[m][r] + sum[l][r])
                    mid[l][r] = m;
            }
        }
    }
}

vector<string> ans;

void make_ans(int l, int r, string now) {
    if (l >= r)
        return;
    if (l == r - 1) {
        ans.push_back(now);
        return;
    }
    make_ans(l, mid[l][r], now + "0");
    make_ans(mid[l][r], r, now + "1");
}

void run() {
    build();
    calc();
    make_ans(0, n, "");
    sort(ans.begin(), ans.end());
}

void write() {
    for (auto i : ans)
        cout << i << "\n";
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
