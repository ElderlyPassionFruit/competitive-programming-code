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

const int N = 2;

void tryBuild() {
    int n = get(1, N);
    int cnt = get(1, n);
    vector<int> a(cnt, 1);
    a.resize(n, 0);
    shuffle(all(a), rnd);
    ++n;
    a.push_back(1);
    vector<pair<int, int>> ans;
    for (int i = 0; i < n; ++i) {
        int r = i;
        while (a[r] != 1) ++r;
        for (int c = i; c <= r; ++c) {
            ans.emplace_back(i * 2 + c - i, i * 2 + (c - i) + (r - i) + 1);
        }
        i = r;
    }
    shuffle(all(ans), rnd);
    cout << n << endl;
    for (auto i : ans) {
        int x = i.first + 1;
        int y = i.second + 1;
        if (get(1, 4) == 1) x = -1;
        if (get(1, 4) == 1) y = -1;
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