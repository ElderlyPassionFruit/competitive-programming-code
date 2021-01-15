#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

int k;
vector<vector<int>> a;

void Swap() {
    a.push_back(a[0]);
    a.erase(a.begin());
}

vector<vector<int>> make() {
    vector<vector<int>> ans;
    for (int i = 0; i < k; ++i) {
        vector<int> fans;
        for (int j = 0; j < (1 << k); ++j) {
            fans.push_back(a[i][(j + (1 << i)) % (1 << k)]);
        }
        ans.push_back(fans);
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cout.precision(20);
    cin >> k;
    
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < (1 << k); ++j) {
            for (int x = 0; x < k; ++x) {
                cout << 0;
            }
            cout << "\n";
        }
        cout << "\n";
    }

    for (int i = 1; i < (1 << k); i *= 2) {
        vector<int> ans(1 << k, 1);
        for (int x = 0; x < (1 << k); x += 2 * i) {
            for (int j = 0; j < i; ++j) {
                ans[x + j] = 0;
            }
        }
        a.push_back(ans);
    }

    for (int it = 0; it < k; ++it) {
        auto ans = make();
        /*for (auto i : ans) {
            for (auto j : i) {
                cout << j << " ";
            }
            cout << "\n";
        }*/
        for (int i = 0; i < (1 << k); ++i) {
            for (int j = 0; j < k; ++j) {
                cout << ans[j][i];
            }
            cout << "\n";
        }
        if (it == k - 1) continue;
        cout << "\n";

        Swap();
    }


    return 0;
}