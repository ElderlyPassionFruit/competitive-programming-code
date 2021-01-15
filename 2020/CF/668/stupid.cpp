#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

int n, q;
vector<int> a;

void read() {
    cin >> n >> q;
    a.resize(n);
    for (auto &i : a) {
        cin >> i;
        i--;
    }
}

int solve(int x, int y) {
    vector<int> now = a;
    for (int i = 0; i < x; i++) {
        now[i] = n;
    }
    for (int i = 0; i < y; i++) {
        now[n - 1 - i] = n;
    }
    int ans = 0;
    while (!now.empty()) {
        bool ok = false;
        for (int i = (int)now.size() - 1; i >= 0; i--) {
            if (now[i] == i) {
                ok = true;
                ans++;
                now.erase(now.begin() + i);
                break;
            }
        }
        if (!ok) break;
    }
    return ans;
}

void run() {
    while (q--) {
        int x, y;
        cin >> x >> y;
        cout << solve(x, y) << "\n";
    }
}

void write() {

}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
    read();
    run();
    write();
    return 0;
}