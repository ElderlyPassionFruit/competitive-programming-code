#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	ll n, m;
	string a, b;
	cin >> n >> m >> a >> b;
	ll g = __gcd((int)a.size(), (int)b.size());
	ll l = (ll)(int)a.size() / g * (int)b.size();
	vector<vector<int>> cnt(g, vector<int> (26, 0));
	for (int i = 0; i < (int)a.size(); i++) {
		cnt[i % g][a[i] - 'a']++;
	}
	ll ans = l;
	for (int i = 0; i < (int)b.size(); i++) {
		ans -= cnt[i % g][b[i] - 'a'];
	}
	cout << ans * (n * (int)a.size() / l) << endl;
	return 0;	
}