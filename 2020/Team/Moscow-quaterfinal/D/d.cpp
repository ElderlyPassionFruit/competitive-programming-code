#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

/*
const int N = 100;
bool p[N];

void initPrimes() {
    fill(p, p + N, true);
    p[0] = p[1] = false;
    for (int i = 2; i < N; ++i) {
        if (!p[i]) continue;
        for (int j = i + i; j < N; j += i) {
            p[j] = false;
        }
    }
}

bool prime(int x) {
    return p[x];
    if (x <= 1) return false;
    for (int i = 2; i * i <= x; ++i) {
        if (x % i == 0) {
            return false;
        }
    }
    return true;
}

bool check(int x) {
    if (!prime(x)) return false;
    string s = to_string(x);
    for (int l = 0; l < s.size(); ++l) {
        for (int len = 1; l + len - 1 < s.size(); ++len) {
            if (!prime(stoi(s.substr(l, len)))) {
                return false;
            }
        }
    }
    return true;
}*/

vector<int> have = {2,3,5,7,23,37,53,73,373};
ll l, r;

void read() {
    cin >> l >> r;
    /*initPrimes();
    for (int x = 1; x < N; ++x) {
        if (check(x)) {
            cout << x << ",";
        }
    }*/
}

int ans;

void run() {
    ans = 0;
    for (auto i : have) {
        if (l <= i && i <= r) {
            ++ans;
        }
    }
}

void write() {
    cout << ans << endl;
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