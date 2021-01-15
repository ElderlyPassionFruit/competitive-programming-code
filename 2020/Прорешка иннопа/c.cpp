#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

int n, m, q;
int a, b;

void read() {
    cin >> n >> m >> q;
    swap(n, m);
    cin >> a >> b;
    --a;
    --b;
    swap(a, b);
}

vector<int> dx = {1, }

void solve() {
    int x, y;
    char t;
    cin >> x >> y;
    cin >> t;
    --x;
    --y;
    swap(x, y);
}

void run() {
    while (q--) {
        solve();
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