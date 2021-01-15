#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

#define int ll

vector<int> days = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool checkYear(int x) {
    if (x % 4 == 0 && x % 100 != 0) return true;
    if (x % 400 == 0) return true;
    return false;
}

int get(int n) {
    return n * (n + 1) / 2;
}

int getDays(int x) {
    if (x > 12) {
        return get(11);
    } else {
        int ans = 0;
        for (int m = 1; m < x; ++m) {
            int d = m - 1;
            ans += d;
        }
        return ans;
    }
}

int k;

void read() {
    cin >> k;
}

void run() {
    for (int y = 3; ; y++) {
        if (getDays(y) < k) {
            k -= getDays(y);
            continue;
        }
        for (int m = 1; m <= 12; ++m) {
            for (int d = 1; d < m; ++d) {
                --k;
                if (k == 0) {
                    cout << y << "/" << m << "/" << d << endl;
                    exit(0);
                }
            }
        }
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