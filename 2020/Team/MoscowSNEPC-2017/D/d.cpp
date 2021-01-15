#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);

    int n;
    cin >> n;
    ull cur = 1;
    ull res = 0;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        if (x < 128) {
            res += cur * x;
            cur = 1;
            if (res % 2 == 0) {
                cout << res / 2 << '\n';
            } else {
                res /= 2;
                cout << '-' << res + 1 << '\n';
            }
            res = 0;
        } else {
            res += cur * (x - 128);
            cur <<= 7;
        }
    }
	return 0;
}