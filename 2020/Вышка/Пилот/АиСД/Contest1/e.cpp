#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

const ull a = 134775813;
const unsigned int c = 1;
const ull x = 100000000;

unsigned int nxt(unsigned int &s) {
    s = a * s + c;
    return (x * s) >> 32; 
}

mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());

const int N = 2e5 + 10;
int n;
int pos[N], val[N];

int getInd(unsigned int x) {
    return lower_bound(pos, pos + n, x) - pos;
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
    cin >> n;
    n *= 2;
    vector<unsigned int> a(n);
    for (auto& i : a) {
        cin >> i;
    }
    for (int i = 0; i < n; ++i) {
        pos[i] = a[i];
    }
    sort(pos, pos + n);
    for (int i = 0; i < n; ++i) {
        val[getInd(a[i])] = i;
    }
    while((double)clock() / CLOCKS_PER_SEC < 2.9) {
        unsigned int s = rnd();
        unsigned int x;
        while (true) {
            x = nxt(s);
            int ind = getInd(x);
            if (ind == n || pos[ind] != x || val[ind] + 300 > n) {
                s = rnd();
                continue;
            }
            break;
        } 
        int ind = getInd(x);
        int now = val[ind];
        while (now + 1 < n) {
            x = nxt(s);
            int ind = getInd(x);
            if (ind == n || pos[ind] != x) break;
            if (val[ind] != now + 1) break;
            ++now;
        }
        if (now == n - 1) {
            cout << "RAW\n";
            exit(0);
        }
    }
    cout << "SHUFFLED\n";
    return 0;
}