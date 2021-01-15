#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

void no() {
    cout << "No\n";
    exit(0);
}

const int N = 210;
int n;
int a[N], b[N];

void read() {
    cin >> n;
    set<int> setik;
    for (int i = 0; i < n; ++i) {
        cin >> a[i] >> b[i];
        if (a[i] != -1 && setik.count(a[i])) no();
        if (b[i] != -1 && setik.count(b[i])) no();
        setik.insert(a[i]);
        setik.insert(b[i]);
    }
}

bool used[N];

bool check(int l, int r) {
    //l = 2 * l + 1;
    //r = 2 * r;
    //cout << "l = " << l << " r = " << r << endl;
    if (r <= l) return false;
    if ((r - l + 1) % 2) return false;
    fill(used, used + N, false);
    int c = (r - l + 1) / 2;
    //cout << "c = " << c << endl;
    for (int i = 0; i < n; ++i) {
        int x = a[i], y = b[i];
        //cout << "x = " << x << " y = " << y << endl;
        if (x == -1 && y == -1) continue;
        if (x != -1 && y != -1 && x >= y) return false;
        bool must = (x >= l && x <= r) || (y >= l && y <= r);
        if (x == -1) {
            x = y - c;
        } else if (y == -1) {
            y = x + c;
        }
        if (x > r || y < l) continue;
        if ((x < l || y > r) && must) return false;
        if ((x < l || y > r)) continue;
        if (y - x != c) return false;
        if (used[x] || used[y]) return false;
        //cout << "x = " << x << "y = " << y << endl;
        used[x] = true;
        used[y] = true;
    }
    return true;
}

bool dp[N];

void calcDp() {
    for (int i = 1; i <= 2 * n; i += 2) {
        for (int j = i + 1; j <= 2 * n; j += 2) {
            cout << check(i, j) << " ";
        }
        cout << "\n";
    }
    //cout << check(1, 4) << endl;
    //exit(0); 
    /*cout << check(1, 3) << endl;
    exit(0);
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            cout << check(i, j) << " ";
        }
        cout << endl;
    }*/
    //exit(0);
    dp[0] = 1;
    for (int i = 1; i <= 2 * n; ++i) {
        for (int j = 0; j < i; ++j) {
            dp[i] |= dp[j] && check(j + 1, i);
        }
    }
}

void run() {
    calcDp();
}

void write() {
    if (!dp[2 * n]) {
        no(); 
    }
    cout << "Yes\n";
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
    read();
    run();
    write();
    return 0;
}
