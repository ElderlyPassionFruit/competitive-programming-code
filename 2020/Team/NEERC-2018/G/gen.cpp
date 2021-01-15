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

int get(int l, int r) {
    return rnd() % (r - l + 1) + l;
}

const int INF = 1e18 + 228;

const int N = 100;
const int C = 100;

void tryBuild() {
    int n = get(2, N);
    int r = get(1, n - 1);
    int k = get(1, (n - r) * (n - r + 1) / 2);
    cout << n << " " << r << " " << k << endl;
    vector<int> a(n), b(n), c(n);
    for (int i = 0; i < n; ++i) {
        a[i] = get(1, C - 2);
        b[i] = get(a[i] + 1, C - 1);
        c[i] = get(b[i] + 1, C);
    }
    for (auto i : a) {
        cout << i << " ";
    }
    cout << endl;
    for (auto i : b) {
        cout << i << " ";
    }
    cout << endl;
    for (auto i : c) {
        cout << i << " ";
    }
    cout << endl;
    exit(0);
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
    while (true) {
        tryBuild();
    }
    return 0;
}