#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int N = 2e5 + 10, A = 110;
int n;
int a[N];
vector<int> pos[A];
int cnt[A];

void read() {
    cin >> n;
    fill(cnt, cnt + A, 0);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        pos[a[i]].push_back(i);
        cnt[a[i]]++;
    }
}

int bal[2 * N];

int get(int mx, int val) {
    if (cnt[val] == 0) return 0;
    fill(bal, bal + 2 * N, 2 * N);
    bal[N] = -1;
    int now = 0;
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        if (a[i] == mx) {
            ++now;
        } else if (a[i] == val) {
            --now;
        }
        chkmax(ans, i - bal[now + N]);
        chkmin(bal[now + N], i);
    }
    return ans;
}

int ans;

void run() {
    int mx = max_element(cnt, cnt + A) - cnt;
    ans = 0;
    for (int i = 0; i < A; ++i) {
        if (i == mx) continue;
        chkmax(ans, get(mx, i));
    }
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