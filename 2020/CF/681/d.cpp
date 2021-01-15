#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

#define int ll

const int N = 3010;
int n, k;
vector<int> a[N];

void read() {
    cin >> n >> k;
    for (int i = 0; i < n; ++i) {
        int sz;
        cin >> sz;
        a[i].resize(sz);
        for (auto& x : a[i]) {
            cin >> x;
        }
    }
}

ll dp[N];

void init() {
    fill(dp, dp + N, 0);
}

void relax(int cnt, ll sum) {
    for (int w = k; w >= cnt; --w) {
        chkmax(dp[w], dp[w - cnt] + sum);
    }
}

ll ans;

void relaxAns(int cnt, ll sum) {
    if (cnt > k) return;
    chkmax(ans, dp[k - cnt] + sum);
}

int ptr[N];

vector<int> pref[N];

void run() {
    sort(a, a + n, [&] (const vector<int>& i, const vector<int>& j) {
        return i.back() > j.back();
    });
    for (int i = 0; i < n; ++i) {
        pref[i] = a[i];
        for (int j = 1; j < a[i].size(); ++j) {
            pref[i][j] += pref[i][j - 1];
        }
    }
    for (int i = 0; i < n; ++i) {
        ptr[i] = a[i].size();
    }
    init();
    ans = 0;
    for (int i = 0; i < n; ++i) {
        while (ptr[i] > 0) {
            ptr[i]--;
            relaxAns(ptr[i] + 1, pref[i][ptr[i]]);
        }
        relax(a[i].size(), pref[i].back());
        /*
        for (int j = i + 1; j < n; ++j) {
            while (ptr[j] > 0) {
                if (a[j][ptr[j] - 1] <= a[i].back() && (ptr[j] == a[j].size() || a[j][ptr[j]] <= a[i].back())) {
                    break;
                }
                ptr[j]--;
                relaxAns(ptr[j] + 1, pref[j][ptr[j]]);
            }
        }*/
        for (int j = i + 1; j < n; ++j) {
            for (int cnt = 1; cnt <= k && cnt <= a[j].size(); ++cnt) {
                relaxAns(cnt, pref[j][cnt - 1]);
            }
        }
    }
    /*for (int i = 0; i < n; ++i) {
        ll sum = 0;
        for (int cnt = 0; cnt <= k && cnt <= a[i].size(); ++cnt) {
            if (dp[k - cnt] != INF) {
                chkmax(ans, dp[k - cnt] + sum);
            }
            if (cnt < a[i].size()) {
                sum += a[i][cnt];
            }
        }
        relax(a[i].size(), sum);
    }*/
    chkmax(ans, dp[k]);
}

void write() {
    cout << ans << endl;
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
    read();
    run();
    write();
    return 0;
}