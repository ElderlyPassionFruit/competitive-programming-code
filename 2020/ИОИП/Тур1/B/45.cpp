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
    for (auto &i : a)
        cin >> i;
}
 
void build() {
    vector<int> have;
    for (auto i : a)
        have.push_back(i);
    sort(all(have));
    have.resize(unique(all(have)) - have.begin());
    for (auto &i : a)
        i = lower_bound(all(have), i) - have.begin();  
}
 
int ans;
 
void run() {
    build();
    vector<int> dp(n, 0);
    map<int, int> last;
    for (int i = 0; i < n; i++) {
        int add = 0;
        if (last.count(a[i])) {
            chkmax(add, dp[last[a[i]]]);
        }
        if (last.count(a[i] - 1)) {
            chkmax(add, dp[last[a[i] - 1]]);
        }
        add++;
        last[a[i]] = i;
        dp[i] = add;
    }
    ans = n;
    for (int i = 0; i < n; i++) {
        chkmin(ans, n - dp[i]);
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