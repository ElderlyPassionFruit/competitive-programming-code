#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    ll n;
    cin >> n;
    for (ll i = 2; i * i <= n; ++i) {
        if (n % i) continue;
        ll x = i;
        ll y = n / i;
        vector<pair<ll, ll>> ans;
        if (x != y) {
            ans.push_back({1LL, x});
            ans.push_back({1LL, y});
        } else {
            ans.push_back({2LL, x});
        }
        if (x + y != n) {
            ans.push_back({n - x - y, 1});
        }
        cout << ans.size() << endl;
        for (auto [x, y] : ans) {
            cout << y << " " << x << endl;
        }
        return 0;
    }
    cout << "-1\n";
	return 0;
}