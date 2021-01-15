#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

#define int ll

int get_lg(ll n, int b) {
	int ans = 0;
	while (n >= b) {
		n /= b;
		ans++;
	}
	return ans;
}

void solve() {
	int p, q, a, b;
	ll n;
	cin >> p >> q >> a >> b >> n;
	if (n % p || a * p > n) {
		cout << "No\n";
		return;
	} 
	n /= p;
	int lg = get_lg(n, q);
	lg = min(lg, b);
	ll Q = 1;
	for (int i = 0; i < lg; i++)
		Q *= q;

	ll sum = 0;
	for (int i = lg; i >= 0; i--) {
		sum += n / Q;
		n %= Q;
		Q /= q;
	}

	if (sum <= a && (a - sum) % (q - 1) == 0) {
		cout << "Yes\n";
	}
	else {
		cout << "No\n";
	}
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t--)
		solve();
	return 0;
}