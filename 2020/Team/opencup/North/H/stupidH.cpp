#include <iostream>
#include <vector>
#include <algorithm>
#define ll long long

using namespace std;

int n, m;

void solve() {
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vector<int> all;
    for (int i = 1; i <= m; ++i) {
        vector<int> all2;
        all2 = all;
        all2.push_back(i);
        for (auto elem : all) {
            all2.push_back(elem);
        }
        all = all2;
    }
    ll S = 0;
    int mn = n;
    int ln = all.size();
    for (int i = 0; i < ln; ++i) {
        if (i + n > ln)
            break;
        int now = 0;
        for (int j = 0; j < n; ++j) {
            if (a[j] != all[i + j]) {
                now++;
            }
        }
        //cerr << now << "!\n";
        S += now;
        mn = min(mn, now);
    }
    cout << mn << " " << S << "\n";

}

int main() {
    while (cin >> n >> m) {
        solve();
    }
}
//*/