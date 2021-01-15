#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

mt19937 rnd(time(0));

int get(int l, int r) {
    return rnd() % (r - l + 1) + l;
}

int n;
vector<int> a;

void read() {
    n = 20;
    for (int i = 0; i < n; ++i) {
        a.push_back(get(0, 127));
    }
    sort(all(a));
    a.resize(unique(all(a)) - a.begin());
}

void run() {
    n = a.size();
    cout << "a = " << endl;
    for (auto i : a) {
        cout << i << " ";
    }
    cout << endl;
    cout << "best = " << endl;
    for (auto i : a) {
        int val = a[0];
        for (auto j : a) {
            if (i != j && (val ^ i) > (j ^ i)) {
                val = j;
            }
        }
        cout << val << " ";
    }
    cout << endl;
}

void write() {

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