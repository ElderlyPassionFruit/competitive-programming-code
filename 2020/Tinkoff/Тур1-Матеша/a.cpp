#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int a, b, c;

void read() {
    cin >> a >> b >> c;
}

tuple <int, int, int> gcd(int a, int b) {
    if (b == 0) {
        return {1, 0, a};
    } else {
        int x, y, g;
        tie(x, y, g) = gcd(b, a % b);
        return {y, x - (a / b) * y, g};
    }
}

int x, y, g;

void run() {
    tie(x, y, g) = gcd(a, b);
    if (c % g) {
        cout << "Impossible" << endl;
        exit(0);
    }
    x *= c / g;
    y *= c / g;
    int dx = b / g;
    int dy = a / g;
    if (x >= dx) {
        int k = x / dx;
        x -= k * dx;
        y += k * dy;
    }
    if (x < 0) {
        int k = (abs(x) + dx - 1) / dx;
        x += k * dx;
        y -= k * dy;
    }
}

void write() {
    cout << x << " " << y << endl;
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
