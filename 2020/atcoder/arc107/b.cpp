#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

#define int ll

int n, k;

void read() {
    cin >> n >> k;
}

int get(int sum) {
    if (sum < 2) return 0;
    if (sum > 2 * n) return 0;
    int minA = max(1LL, sum - n);
    int maxA = min(n, sum - minA);
    return maxA - minA + 1;
}

int ans = 0;

void run() {
    for (int sumAB = 2; sumAB <= 2 * n; ++sumAB) {
        ans += get(sumAB) * get(sumAB - k);
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