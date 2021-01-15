#include <bits/stdc++.h>

using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(a) a.begin(), a.end()

using namespace std;

template<typename T1, typename T2> inline void chkmin(T1& x, const T2& y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1& x, const T2& y) {if (x < y) x = y;}

int a, b;

void read() {
    cin >> a >> b;
}

pair<int, int> get(int a, int x) {
    return {(a - 1) * x + 1, a * x};
}

pair<int, int> merge(pair<int, int> a, pair<int, int> b) {
    return {max(a.first, b.first), min(a.second, b.second)};
}

vector<int> ans;

void run() {
    auto have = merge(get(a, 50), get(b, 70));
    //cout << have.first << " " << have.second << endl;
    if (have.first > have.second) return;
    int L = (have.first + 60 - 1) / 60;
    int R = (have.second + 60 - 1) / 60;
    for (int i = L; i <= R; ++i) {
        ans.push_back(i);
    }
}

void write() {
    if (ans.empty()) {
        cout << "-1\n";
    } else {
        for (auto i : ans) {
            cout << i << ' ';
        }
        cout << '\n';
    }
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.setf(ios::fixed), cout.precision(20);
    read();
    run();
    write();
    return 0;
}