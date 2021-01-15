#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

const vector<int> dx = {0, 0, -1, 1};
const vector<int> dy = {1, -1, 0, 0};
const vector<char> have = {'U', 'D', 'L', 'R'};

int getDir(char x) {
    if (x == 'U') return 0;
    if (x == 'D') return 1;
    if (x == 'L') return 2;
    if (x == 'R') return 3;
    assert(false);
    return -1;
}

void solve() {
    int x, y;
    string s;
    cin >> x >> y;
    cin >> s;
    int fx = 0, fy = 0;
    vector<int> cnt(4, 0);
    for (auto i : s) {
        int dir = getDir(i);
        fx += dx[dir];
        fy += dy[dir];
        cnt[dir]++;
    }
    if (fx == x && fy == y) {
        cout << "Impossible\n";
        return;
    }
    if (x == 0 && y == 0) {
        cout << "Impossible\n";
        return;    
    }
    string ans = "";
    vector<int> order = {0, 1, 2, 3};
    // if (x == 0) {
    //     order.push_back(2);
    //     order.push_back(3);
    //     if (y > 0) {
    //         order.push_back(1);
    //         order.push_back(0);
    //     } else {
    //         order.push_back(0);
    //         order.push_back(1);
    //     }
    // } else if (y == 0) {
    //     order.push_back(0);
    //     order.push_back(1);
    //     if (x > 0) {
    //         order.push_back(2);
    //         order.push_back(3);
    //     } else {
    //         order.push_back(3);
    //         order.push_back(2);
    //     }
    // } else {
    //     if (x > 0) {
    //         order.push_back(2);
    //         order.push_back(3);
    //     } else {
    //         order.push_back(3);
    //         order.push_back(2);
    //     }
    //     if (y > 0) {
    //         order.push_back(1);
    //         order.push_back(0);
    //     } else {
    //         order.push_back(0);
    //         order.push_back(1);
    //     }
    // }
    do {
        ans = "";
        for (auto i : order) {
            for (int x = 0; x < cnt[i]; ++x) {
                ans += have[i];
            }
        }
        bool ok = true;
        fx = 0, fy = 0;
        for (auto i : ans) {
            int dir = getDir(i);
            fx += dx[dir];
            fy += dy[dir];
            ok &= (fx != x || fy != y);
            // if (fx == x && fy == y) {
            //     cout << "fail" << endl;
            // }
            // assert(!(fx == x && fy == y));
        }
        if (ok) {
            cout << ans << '\n';
            return;
        }
    } while (next_permutation(all(order)));
    cout << "Impossible\n";
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}