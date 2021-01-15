#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

#define int ll

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

int get(int n) {
    return (ull)rnd() % n;
}

const int Q = 1000;
int cnt = 0;

int query(int x) {
    ++cnt;
    assert(cnt <= Q);
    cout << "? " << x + 1 << endl;
    int ans;
    cin >> ans;
    return ans;
}

void outAns(int x) {
    cout << "! " << x + 1 << endl;
    exit(0); 
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
    int n, k;
    cin >> n >> k;
    int sleep = sqrt(n) + 10;
    for (int i = 0; i < sleep; ++i) {
        query(0);
    }
    int step = sqrt(n) + 1;
    int now = 0;
    while (query(now) <= k) {
        now += step;
        now %= n;
    }
    while (query(now) != k) {
        now--;
        if (now == 0) now = n - 1;
    } 
    outAns(now);
    return 0;
}