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

const int N = 8;

set<string> have;

void genString() {
    int len = get(1, 4);
    string s = "";
    for (int i = 0; i < len; ++i) {
        s += get(0, 3) + 'a';
        //cout << static_cast<char>(get(0, 1) + 'a');
    }
    have.insert(s);
    //cout << endl;
}

void tryBuild() {
    //int t = get(1, N);
    int t = 100;
    cout << t << endl;
    for (int it = 0; it < t; ++it) {
        int n = get(1, N);
        cout << n << endl;
        for (int i = 0; i < n; ++i) {
            cout << get(1, n) << " ";
        }
        cout << endl;
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