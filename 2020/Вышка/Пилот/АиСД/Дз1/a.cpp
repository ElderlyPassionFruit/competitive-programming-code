#include <bits/stdc++.h>

using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(a) a.begin(), a.end()

using namespace std;

template<typename T1, typename T2> inline void chkmin(T1& x, const T2& y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1& x, const T2& y) {if (x < y) x = y;}

const int N = 1e3 + 10;
int n, m, k;
int a[N][N];

void read() {
    cin >> n >> m >> k;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> a[i][j];
        }
    }
}

vector<int> have;

void build() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            have.push_back(a[i][j]);
        }
    }
    sort(all(have));
    have.resize(unique(all(have)) - have.begin());
}

int dpUp[N][N];
int dpL[N][N], dpR[N][N];

int get(int pos) {
    int x = have[pos];
    //int x = 521;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (x > a[i][j]) {
                dpUp[i][j] = 0;
            } else {
                dpUp[i][j] = (i > 0 ? dpUp[i - 1][j] : 0) + 1;
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        vector<pair<int, int>> st;
        int pos = -1;
        for (int j = 0; j < m; ++j) {
            if (a[i][j] < x) {
                dpL[i][j] = 0;
                st.clear();
                pos = j;
            } else {
                while (!st.empty() && st.back().first >= dpUp[i][j]) st.pop_back();
                if (st.empty()) {
                    dpL[i][j] = j - pos;
                } else {
                    dpL[i][j] = j - st.back().second;
                }
                st.push_back({dpUp[i][j], j});
            }
        }
        st.clear();
        pos = m;
        for (int j = m - 1; j >= 0; --j) {
            if (a[i][j] < x) {
                dpR[i][j] = 0;
                st.clear();
                pos = j;
            } else {
                while (!st.empty() && st.back().first >= dpUp[i][j]) st.pop_back();
                if (st.empty()) {
                    dpR[i][j] = pos - j;
                } else {
                    dpR[i][j] = st.back().second - j;
                }
                st.push_back({dpUp[i][j], j});
            }
        }
    }

    /*cout << "dpUp = " << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << dpUp[i][j] << " ";
        }
        cout << endl;
    }
    cout << "dpL = " << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << dpL[i][j] << " ";
        }
        cout << endl;
    }
    cout << "dpR = " << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << dpR[i][j] << " ";
        }
        cout << endl;
    }*/

    int ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            chkmax(ans, dpUp[i][j] * (dpL[i][j] + dpR[i][j] - 1));
        }
    }
    //pos += 5;
    return ans;
}

int ans;

void run() {
    build();
    //cout << get(1) << endl;
    //exit(0);
    int l = 0, r = have.size();
    while (l < r - 1) {
        int mid = (l + r) / 2;
        if (get(mid) >= k) {
            l = mid;
        } else {
            r = mid;
        }
    }
    ans = l;
}

void write() {
    //cout << "ans = " << ans << endl;
    //exit(0);
    cout << have[ans] << " " << get(ans) << '\n';
}

signed main() {
    freopen("burrow.in", "r", stdin);
    freopen("burrow.out", "w", stdout);
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.setf(ios::fixed), cout.precision(20);
    read();
    run();
    write();
    return 0;
}