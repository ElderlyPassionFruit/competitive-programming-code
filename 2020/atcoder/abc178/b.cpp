#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

#define int ll

int a, b, c, d;

void read() {
    cin >> a >> b >> c >> d;
}

vector<int> get(int l, int r) {
    vector<int> ans;
    ans.push_back(l);
    ans.push_back(r);
    if (l <= 0 && r >= 0) {
        ans.push_back(0);
    }
    if (l <= 1 && r >= 1) {
        ans.push_back(1);
    }
    if (l <= -1 && r >= -1) {
        ans.push_back(-1);
    }
    return ans;
}

int ans;

void run() {
    auto L = get(a, b);
    auto R = get(c, d);
    ans = L[0] * R[0];
    for (auto i : L) {
        for (auto j : R) {
            chkmax(ans, i * j);
        }
    }
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