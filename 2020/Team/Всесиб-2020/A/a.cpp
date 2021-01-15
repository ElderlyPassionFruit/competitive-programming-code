#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

void solve() {
    int n, m, x, y, r;
    cin >> n >> m >> x >> y >> r;
    x--;
    y--;
    int a = x;
    int b = n - x - 1;
    int c = y;
    int d = m - y - 1;
    
    if ((a <= r && b <= r) || (a <= r && c <= r) || (b <= r && d <= r) || (c <= r && d <= r)) {
        cout << "Tuzik\n";
    }
    else{
        cout << "Barsik\n";
    }
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