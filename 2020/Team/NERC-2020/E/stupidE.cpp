#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

#define int ll
/*
int gcd(int a, int b, int& x, int& y) {
    if (a == 0) {
        x = 0, y = 1;
        return b;
    }
    int x1, y1;
    int d = gcd(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}

void solve() {
    int B, D;
    cin >> B >> D;
    int a, c;
    int g = gcd(D, B, a, c);
    if (B * B % g) {
        cout << "0\n";
        return;
    } 
    int x = B / g;
    int y = D / g;
    cout << "a = " << a << " c = " << c << endl; 
    while (a >= 0) {
        a -= x;
        c += y;
    }
    while (a <= 0) {
        a += x;
        c -= y;
    }
    if (c <= 0) {
        cout << "0\n";
        return;
    }
    int ans = c / y + 1;
    if (c % y == 0) {
        ans--;
    }
    cout << ans << "\n";
}*/

void solve() {
    int b, d;
    cin >> b >> d;
    int ans = 0;
    for (int a = 1; a <= 1000; ++a) {
        for (int c = 1; c <= 1000; ++c) {
            if (a * d + b * c == b * b) {
                ++ans;
            } 
        }
    }
    cout << ans << endl;
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cout.precision(20);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}