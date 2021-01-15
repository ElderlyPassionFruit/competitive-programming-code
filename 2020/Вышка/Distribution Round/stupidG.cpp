#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

string s;

void read() {
    cin >> s;
}

int calc(string a) {
    if (a.empty()) return 0;
    int ans = 0;
    for (int i = 0; i + a.size() <= s.size(); ++i) {
        ans += s.substr(i, a.size()) == a;
    }
    return ans;
}

string ans;

void relax(string a) {
    if (calc(a) < calc(ans)) return;
    if (calc(a) == calc(ans) && a.size() < ans.size()) return;
    if (calc(a) == calc(ans) && a.size() == ans.size() && a > ans) return;
    ans = a;
}

void run() {
    for (int i = 0; i < s.size(); ++i) {
        for (int len = 1; i + len - 1 < s.size(); ++len) {
            relax(s.substr(i, len));
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