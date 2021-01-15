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

void tryBuild() {
    int n = 500;
    int tailLen = 250;
    //int tailLen;
    //cin >> tailLen;
    vector<pair<int, int>> edges;
    for (int i = 1; i <= n - tailLen; ++i) {
        for (int j = i + 1; j <= n - tailLen; ++j) {
            edges.push_back({i, j});
        }
    }
    for (int i = n - tailLen + 1; i <= n; ++i) {
        edges.push_back({i - 1, i});
    }
    /*for (int i = 1; i <= n - 1; i += groupSize) {
        if (i > 1) edges.push_back({i, i - 1});
        for (int j = 0; j < groupSize; ++j) {
            for (int k = j + 1; k < groupSize; ++k) {
                edges.push_back({i + j, i + k});
            }
        }
    }
    edges.push_back({n - 1, n});
    */
    cout << n << " " << edges.size() << endl;
    for (auto i : edges) {
        cout << i.first << " " << i.second << endl;
    }
    cout << 1 << " " << n << endl;
    exit(0);
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
    while (true) {
        tryBuild();
    }
    return 0;
} 