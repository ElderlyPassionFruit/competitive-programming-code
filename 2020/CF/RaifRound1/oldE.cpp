#include <bits/stdc++.h>

using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(a) a.begin(), a.end()

using namespace std;

template<typename T1, typename T2> inline void chkmin(T1& x, const T2& y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1& x, const T2& y) {if (x < y) x = y;}

int n, k;
vector<int> a;

void read() {
    cin >> n >> k;
    a.resize(n);
    for (auto& i : a) {
        cin >> i;
    }
}

bool check(int x) {
    int cnt = 0;
    for (auto i : a) {
        cnt += (i + x - 1) / x;
    }
    return cnt <= k;
}

ll ans;

void makeAns(int x) {
    
} 

void run() {
    int l = 0, r = *max_element(all(a));
    while (l < r - 1) {
        int mid = (l + r) / 2;
        if (check(mid)) {
            r = mid;
        } else {
            l = mid;
        }
    }
    makeAns(r);
}

void write() {
    cout << ans << endl;
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.setf(ios::fixed), cout.precision(20);
    read();
    run();
    write();
    return 0;
}