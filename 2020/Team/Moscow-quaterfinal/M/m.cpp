#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n;
vector<int> a;

void read() {
    cin >> n;
    a.resize(n);
    for (auto& i : a) {
        cin >> i;
    }
}

bool check(int l, int r) {
    map<int, int> cnt;
    for (int i = l; i <= r; ++i) {
        cnt[a[i]]++;
    }
    map<int, int> nxtCnt;
    for (auto i : cnt) {
        nxtCnt[i.second]++;
    }
    if ((--nxtCnt.end())->second > 1) {
        return true;
    }
    return false;
}

int ans;

void run() {
    ans = 0;
    for (int l = 0; l < n; ++l) {
        for (int r = l; r < n; ++r) {
            if (check(l, r)) {
                chkmax(ans, r - l + 1);
            }
        }
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