#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

const int N = 1e5 + 10;
string s;
int n;

void read() {
    cin >> s;
    n = s.size();
}

mt19937 rnd(time(0));
const int MOD[2] = {998244353, (int)1e9 + 7};
const int base[2] = {(int)rnd() % 228 + 1337, (int)rnd() % 228 + 1337};

int add(int a, int b, int it) {
    a += b;
    if (a >= MOD[it]) return a - MOD[it];
    return a;
}

int sub(int a, int b, int it) {
    a -= b;
    if (a < 0) return a + MOD[it];
    return a;
}

int mul(int a, int b, int it) {
    return (ll) a * b % MOD[it];
}

int h[2][N];
int pows[2][N];

void build() {
    for (int it = 0; it < 2; ++it) {
        pows[it][0] = 1;
        h[it][0] = 0;
        for (int i = 1; i <= n; ++i) {
            pows[it][i] = mul(pows[it][i - 1], base[it], it);
            h[it][i] = add(mul(h[it][i - 1], base[it], it), s[i - 1], it);
        }
    }
}

bool check(int l1, int l2, int len) {
    int r1 = l1 + len - 1;
    int r2 = l2 + len - 1;
    for (int it = 0; it < 2; ++it) {
        int h1 = sub(h[it][r1], mul(h[it][l1 - 1], pows[it][r1 - l1 + 1], it), it);
        int h2 = sub(h[it][r2], mul(h[it][l2 - 1], pows[it][r2 - l2 + 1], it), it);
        if (h1 != h2) {
            return false;
        }
    }
    return true;
}

void solve() {
    int l1, r1, l2, r2;
    cin >> l1 >> r1 >> l2 >> r2;
    ++l1;
    ++r1;
    ++l2;
    ++r2;
    int len = min(r1 - l1 + 1, r2 - l2 + 1);
    int l = 0, r = len + 1;
    while (l < r - 1) {
        int mid = (l + r) / 2;
        if (check(l1, l2, mid)) {
            l = mid;
        } else {
            r = mid;
        }
    }
    //int l = 0;
    //while (l1 + l <= r1 && l2 + l <= r2 && s[l1 + l - 1] == s[l2 + l - 1]) {
    //    ++l;
    //} 
    //cout << "l = " << l << endl;
    int len1 = r1 - l1 + 1;
    int len2 = r2 - l2 + 1;
    int ans = 0;
    if (l == len1 && len1 < len2) {
        ans = -1;
    } else if (l == len2 && len2 < len1) {
        ans = 1;
    } else if (l < min(len1, len2)) {
        if (s[l1 + l - 1] > s[l2 + l - 1]) {
            ans = 1;
        } else {
            ans = -1;
        }
    }
    cout << ans << '\n';
    /*if (l == len && r1 - l1 + 1 == r2 - l2 + 1) {
        cout << 0 << '\n';
    } else {
        //cout << r2 - l2 + 1 << " " << s[l2 + l - 1] << " " << s[l1 + l - 1] << endl;
        if ((l != r2 - l2 + 1) && (l == r1 - l1 + 1 || s[l1 + l - 1] > s[l2 + l - 1])) {
            cout << 1 << '\n';
        } else {
            cout << -1 << '\n';
        }
    }*/
}

void run() {
    build();
    int q;
    cin >> q;
    while (q--) {
        solve();
    }
}

void write() {

}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
    read();
    run();
    write();
    return 0;
}