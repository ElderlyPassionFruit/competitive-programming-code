#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

int n, m;
vector<int> a, b;

void relax(int x, vector<int>& b) {
    sort(all(b));
    reverse(all(b));
    for (int i = 0; i < x; ++i) {
        b[i]--;
    }
}

int getAns(vector<int> a, vector<int> b) {
    sort(all(a));
    reverse(all(a));
    for (auto i : a) {
        if (i > b.size()) return false;
        relax(i, b);
    }
    return *min_element(all(b)) >= 0;
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cout.setf(ios::fixed), cout.precision(20);
    cin >> n >> m;
    a.resize(n);
    for (auto& i : a) cin >> i;
    b.resize(m);
    for (auto& i : b) cin >> i;
    int q;
    cin >> q;
    while (q--) {
        int t, pos;
        cin >> t >> pos;
        --pos;
        if (t == 1) {
            a[pos]++;
        } else if (t == 2) {
            a[pos]--;
        } else if (t == 3) {
            b[pos]++;
        } else if (t == 4) {
            b[pos]--;
        }
        cout << getAns(a, b) << endl;
    }
    return 0;
}