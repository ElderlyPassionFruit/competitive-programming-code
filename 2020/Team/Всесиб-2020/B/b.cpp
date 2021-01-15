#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const ll INF = 1e9;

void solve(){
    ll p, q, a, b;
    cin >> p >> q >> a >> b;
    ll L = -1;
    ll R = INF;
    while (R - L > 1){
        ll M = (L + R) / 2;
        ll x = q * (100 - p) * (b + M);
        ll y = b * (100 - q) * p * (1 + a * M);
        if (x <= y)
            R = M;
        else
            L = M;
    }
    if (R == INF){
        cout << "-1\n";
    } else{
        cout << R << "\n";
    }
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    int t;
    cin >> t;
    for (int ij = 0; ij < t; ++ij){
        solve();
    }
	return 0;
}