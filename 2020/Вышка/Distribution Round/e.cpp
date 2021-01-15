#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

#define int ll
int n;
vector<int> a;

void read() {
    cin >> n;
    a.resize(n);
    for (auto& i : a) {
        cin >> i;
    }
}

int ans;

void run() {
    sort(all(a));
    int sum = 0;
    for (auto i : a) {
        sum += i;
    }
    if (sum - a.back() <= a.back()) {
        ans = sum - a.back();
    } else {
        ans = sum / 2;
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