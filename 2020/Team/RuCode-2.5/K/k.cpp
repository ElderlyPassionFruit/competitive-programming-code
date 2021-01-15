#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

bool check(int y) {
    return y % 400 == 0 || (y % 4 == 0 && y % 100 != 0);
}

int getDays(int y) {
    if (check(y)) return 366;
    return 365;
}

void solve() {
    int y, c, a;
    cin >> y >> c >> a;
    //int daysA = haveA[y];
    int daysC = getDays(y);
    int ansMin = a + c - 2 * min(a, c);
    int ansMax = 0;
    for (int ban = 0; ban <= min(a, c); ++ban) {
        if (a + c - 2 * ban <= daysC - ban) {
            ansMax = a + c - 2 * ban;
            break;
        }
    }
    cout << ansMin << " " << ansMax << "\n";
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
	return 0;
}