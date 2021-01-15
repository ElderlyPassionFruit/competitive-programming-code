#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    freopen("powerstower.in", "r", stdin);
    freopen("powerstower.out", "w", stdout);
    int n;
    cin >> n;
    if (n == 1) {
        int x;
        cin >> x;
        cout << x % 3 << endl;
    } else {
        int x, y;
        cin >> x >> y;
        x %= 3;
        if (x != 2) {
            cout << x << endl;
        } else {
            y %= 2;
            if (y) {
                cout << 2 << endl;
            } else {
                cout << 1 << endl;
            }
        }
    }
	return 0;
}