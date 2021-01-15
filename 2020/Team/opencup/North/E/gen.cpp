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

vector<int> get(int n) {
    vector<int> a;
    for (int i = 0; i < n; ++i) {
        a.push_back(get(-N, N));
    }
    return a;
}

void tryBuild() {
    int test = 1000;
    for (int i = 0; i < test; ++i) {
        int n, m;
        n = get(1, N);
        m = get(1, N);
        cout << n << " " << m << endl;
        auto a = get(n);
        auto b = get(n);
        for (auto i : a) {
            cout << i << " ";
        }
        cout << endl;
        for (auto i : b) {
            cout << i << " ";
        }
        cout << endl;
        for (int i = 0; i < m; ++i) {
            int t = get(1, 3);
            if (t != 3) {
                cout << t << " " << get(1, n) << " " << get(-N, N) << endl;
            } else {
                cout << t << " " << get(1, n) << endl;
            }
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