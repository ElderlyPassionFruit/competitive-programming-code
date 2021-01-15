#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()
#define int ll

ll binpow(ll a, ll b, ll mod) {
    ll res = 1;
    while (b) {
        if (b & 1)
        {
            res = (res * a) % mod;
        }
        b >>= 1;
        a = (a * a) % mod;
    }
    return res;
}


ll solve(ll a, ll n)
{
	if (n <= 35) return binpow(a, 1LL << n, 1LL << (n + 2));
	return a % 2;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int n, a;
	cin >> n >> a;
	cout << solve(a, n) << "\n";
	return 0;
	for (int a = 1; a <= 30; a++) {
		for (int n = 1; n <= 30; n++) {
			cout << solve(a, n) << " ";
		}
		cout << endl;
	}
	return 0;
}