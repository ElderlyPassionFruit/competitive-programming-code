#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

int n;
vector<int> a;

bool check0(vector<int> a) {
    int now = 0;
    while (now < n) {
        int nxt = now + a[now] + 1;
        if (nxt >= n) return false;
        if (a[nxt] != a[now]) return false;
        now = nxt + 1;
    }
    return now == n;
}

bool check1(vector<int> a) {
    for (int i = 0; i < n; ++i) {
        for (int x = 0; x < n; ++x) {
            auto b = a;
            b[i] = x;
            if (check0(b)) {
                return true;
            }
        }
    }
    return false;
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cout.setf(ios::fixed), cout.precision(20);
    cin >> n;
    a.resize(n);
    for (auto& i : a) {
        cin >> i;
    }
    if (check0(a)) {
        cout << "fix 0\n";
        exit(0);
    }
    if (check1(a)) {
        cout << "fix 1\n";
        exit(0);
    }
    cout << "fix 2" << endl;
    cout << 0 << " " << n - 2 << endl;
    cout << n - 1 << " " << n - 2 << endl;
    return 0;
}