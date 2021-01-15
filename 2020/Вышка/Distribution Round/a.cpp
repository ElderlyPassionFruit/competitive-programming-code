#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

string a, b;

void read() {
    cin >> a >> b;
}

void run() {
    map<char, int> cnt;
    for (auto i : a) {
        cnt[i]++;
    }
    for (auto i : b) {
        if (i >= 'a' && i <= 'z') {
            cnt[i]--;
        }
    }
    for (auto i : cnt) {
        if (i.second < 0) {
            cout << "NO\n";
            exit(0);
        }
    }
}

void write() {
    cout << "YES\n";
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
    read();
    run();
    write();
    return 0;
}