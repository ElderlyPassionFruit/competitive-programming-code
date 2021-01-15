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

const int N = 50;

string get(int x) {
    if (x >= 10) return to_string(x);
    return "0" + to_string(x);
}

void oudTime() {
    cout << get(get(0, 23)) << ":" << get(get(0, 59)) << ":" << get(get(0, 59));
}

void tryBuild() {
    vector<char> have = {'L', 'R', 'U', 'D'};
    int n = get(1, N);
    cout << n << endl;
    for (int i = 0; i < n; ++i) {
        cout << have[get(0, 3)];
    }
    cout << endl;
    int q = get(1, 10000);
    cout << q << endl;
    for (int i = 0; i < q; ++i) {
        int x = get(-5, 5);
        int y = get(-5, 5);
        while (x == 0 && y == 0) {
            x = get(-5, 5);
            y = get(-5, 5);
        }
        cout << x << " " << y << endl;
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