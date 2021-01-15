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


const int N = 20;

string get(int x) {
    if (x >= 10) return to_string(x);
    return "0" + to_string(x);
}

void oudTime() {
    cout << get(get(0, 23)) << ":" << get(get(0, 59)) << ":" << get(get(0, 59));
}

void tryBuild() {
    int n = get(1, N), m = get(1, N);
    vector<int> a(n);
    cout << n << " " << m << endl;
    for (int i = 0; i < n; ++i) {
        a[i] = get(0, N);
    }
    for (auto i : a) {
        cout << i << " ";
    }
    cout << endl;
    vector<int> b(m);
    for (int i = 0; i < m; ++i) {
        b[i] = get(0, N);
    }
    for (auto i : b) {
        cout << i << " ";
    }
    cout << endl;
    int q = get(1, N);
    cout << q << endl;
    while (q--) {
        int t = get(0, 1) * 2 + 1;
        if (t == 1) {
            cout << t << " " << get(1, n) << endl;
        } else if (t == 3) {
            cout << t << " " << get(1, m) << endl;
        }
    }
    exit(0);
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
    while (true) {
        tryBuild();
    }
    return 0;
}