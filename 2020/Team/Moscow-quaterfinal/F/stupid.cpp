#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n;
vector<int> a;
vector<int> b;

void read() {
    cin >> n;
    a.resize(n);
    for (auto& i : a) {
        cin >> i;
    }
    b.resize(n);
    for (auto& i : b) {
        cin >> i;
    }
}

set<vector<int>> used;

void solve(vector<int> a) {
    if (used.count(a)) {
        return;
    }
    used.insert(a);
    if (a == b) {
        cout << "Yes\n";
        exit(0);
    }
    for (int i = 0; i < n; ++i) {
        int prev = (i - 1 + n) % n;
        int nxt = (i + 1) % n;
        if (a[i] - 2 >= max(a[prev], a[nxt])) {
            auto myA = a;
            myA[i] -= 2;
            myA[prev]++;
            myA[nxt]++;
            solve(myA);
        }
    }
}

void run() {
    solve(a);
}

void write() {
    cout << "No\n";
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    read();
    run();
    write();
    return 0;
}