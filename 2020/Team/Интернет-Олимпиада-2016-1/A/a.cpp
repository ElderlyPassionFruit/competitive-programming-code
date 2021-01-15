#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    freopen("cinemaholics.in", "r", stdin);
    freopen("cinemaholics.out", "w", stdout);
    int t1, e1, f1, t2, e2, f2;
    cin >> t1 >> e1 >> f1 >> t2 >> e2 >> f2;
    int ans1 = t1 * 3 + e1 * 20 + f1 * 120;
    int ans2 = t2 * 3 + e2 * 20 + f2 * 120;
    if (ans1 > ans2) {
        cout << "Max\n";
    } else if (ans1 < ans2) {
        cout << "Mel\n";
    } else {
        cout << "Draw\n";
    }
	return 0;
}