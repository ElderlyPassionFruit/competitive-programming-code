#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

#define int ll

int calc(int n, int a, int b) {
    int ans = 0;
    int now = a;
    while (now + b < n) {
        now += min(now, (n - now) / 2);
        ans++;
    }
    ans++;
    return ans;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    int n, k;
    cin >> n >> k;
    if (k >= n) {
        cout << 1 << endl;
        exit(0);
    }
    int ans = 1e9;
    for (int a = 1; a < k; a++) {
        ans = min(ans, calc(n, a, k - a));
    }
    cout << ans << endl;
	return 0;
}