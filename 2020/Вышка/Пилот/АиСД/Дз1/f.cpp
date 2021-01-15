#include <bits/stdc++.h>

using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(a) a.begin(), a.end()

using namespace std;

template<typename T1, typename T2> inline void chkmin(T1& x, const T2& y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1& x, const T2& y) {if (x < y) x = y;}

const int N = 2e5 + 10;
int n;
char c[N];
int t[N];

void read() {
    cin >> n;
    n *= 2;
    for (int i = 0; i < n; ++i) {
        cin >> c[i] >> t[i];
    }
}

vector<ld> ans;

void run() {
    int cnt = 0;

    for (int i = n - 1; i >= 0; --i) {
        if (c[i] == '+') {
            ld fans = 0;
            int tNow = 0;
            ld p = 1;
            int cntNow = cnt;
            for (int j = i + 1; j < n; ++j) {
                tNow += t[j] - t[j - 1];
                if (c[j] == '-') {
                    fans += p * tNow / cntNow;
                    p -= p / cntNow;
                } else {
                    fans += p * (ans.back() + tNow);
                    break;
                }
                if (c[j] == '+') {
                    ++cntNow;
                } else {
                    --cntNow;
                }
            }
            ans.push_back(fans);
        }
        if (c[i] == '+') {
            --cnt;
        } else {
            ++cnt;
        }
    }
}

void write() {
    reverse(all(ans));
    for (auto i : ans) {
        cout << i << '\n';
    }
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.setf(ios::fixed), cout.precision(20);
    read();
    run();
    write();
    return 0;
}