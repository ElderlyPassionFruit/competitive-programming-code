#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

#define int ll

int n, r, k;
vector<int> a, b, c;

int get(int x, int y) {
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        bool X = i >= x && i <= x + r - 1;
        bool Y = i >= y && i <= y + r - 1;
        if (!X && !Y) {
            ans += a[i];
        } else if (X && Y) {
            ans += c[i];
        } else {
            ans += b[i];
        }
    } 
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cout.setf(ios::fixed), cout.precision(20);
    cin >> n >> r >> k;
    a.resize(n);
    b.resize(n);
    c.resize(n);
    for (auto& i : a) {
        cin >> i;
    }
    for (auto& i : b) {
        cin >> i;
    }
    for (auto& i : c) {
        cin >> i;
    }
    vector<int> fans;
    for (int x = 0; x < n; ++x) {
        for (int y = x + 1; y + r - 1 < n; ++y) {
            fans.push_back(get(x, y));
        }
    }
    sort(all(fans));
    /*cerr << "fans = " << endl;
    for (auto i : fans) {
        cerr << i << " ";
    }
    cerr << endl;*/
    cout << fans[k - 1] << endl;
    return 0;
}