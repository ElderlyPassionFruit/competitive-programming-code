#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

string s;
int n;

void read() {
    cin >> s >> n;
}

string ans;

void run() {
    int pos = min_element(all(s)) - s.begin();
    char nxt = 'z';
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] != s[pos]) continue;
        if (i > 0) chkmin(nxt, s[i - 1]);
        if (i + 1 < s.size()) chkmin(nxt, s[i + 1]);  
    }
    ans = "";
    for (int i = 0; i < n; ++i) {
        if (i & 1) {
            ans += nxt;
        } else {
            ans += s[pos];
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