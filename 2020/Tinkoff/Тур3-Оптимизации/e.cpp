#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int INF = 1e10;

int n, k;
const int MAXN = 2e5 + 10, MAXBIT = 30;
int a[MAXN];
void read() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
}

pair <int, int> dp[MAXN];
int last[MAXBIT];
int pos[MAXBIT];

pair <int, int> get(int x) {
    for (int i = 0; i < MAXBIT; i++) {
        last[i] = 0;
        pos[i] = 0;
    }
    for (int i = 1; i <= n; i++) {
        dp[i] = make_pair(dp[i - 1].first + a[i] + x, dp[i - 1].second + 1);
        for (int j = 0; j < MAXBIT; j++) {
            chkmax(dp[i], make_pair(dp[pos[j]].first + (last[j] | a[i]) + x, dp[pos[j]].second + 1));
        }
        for (int j = 0; j < MAXBIT; j++) {
            if ((a[i] >> j) & 1) {
                last[j] = a[i];
                pos[j] = i - 1;
            } else {
                last[j] |= a[i];
            }
        }
    }
    return dp[n];
}

bool check(int x) {
    return get(x).second <= k;
}

int ans;

void run() {
    int l, r;
    l = -INF, r = INF;
    while (l < r - 1) {
        int mid = (l + r) / 2;
        if (check(mid)) {
            l = mid;
        } else {
            r = mid;
        }
    }
    auto fans = get(r);
    ans = fans.first - r * k;
}

void write() {
    cout << ans << endl;
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
