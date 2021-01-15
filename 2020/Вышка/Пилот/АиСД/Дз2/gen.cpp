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
    int len = get(1, N);
    for (int i = 0; i < len; ++i) {
        cout << static_cast<char>(get(0, 1) + 'a');
    } 
    cout << endl;
    int q = get(1, N);
    //int q = 1;
    cout << q << endl;
    for (int i = 0; i < q; ++i) {
        int l, r;
        l = get(0, len - 1);
        r = get(l, len - 1);
        cout << l << " " << r << " ";
        l = get(0, len - 1);
        r = get(l, len - 1);
        cout << l << " " << r << endl;
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