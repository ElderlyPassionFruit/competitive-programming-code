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

vector<int> getColor(int n) {
    vector<int> ans = {1, 2, 3, 4};
    while (ans.size() < n * 2) {
        ans.push_back(get(1, 4));
    }
    shuffle(all(ans), rnd);
    return ans;
}

void tryBuild() {
    int n = 4;
    int x = 10;
    vector<vector<int>> a(n, vector<int>(4, -1));
    auto w = getColor(n);
    for (int i = 0; i < n; ++i) {
        a[i][0] = w[i * 2];
        a[i][2] = w[i * 2 + 1];
    } 
    w = getColor(n);
    for (int i = 0; i < n; ++i) {
        a[i][1] = w[i * 2];
        a[i][3] = w[i * 2 + 1];
    } 
    cout << n << " " << x << endl;
    for (auto i : a) {
        for (auto j : i) {
            cout << j << " ";
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