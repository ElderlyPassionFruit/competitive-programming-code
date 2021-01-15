#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

#define int ll

void solve() {
	int n;
	cin >> n;
	n++;
	int it = 0;
	while (n != 1) {
		if (it == 0) {
			n = (n + 8) / 9;
		}
		else {
			n = (n + 1) / 2;
		}
		it ^= 1;
	}
	if (it == 1)
		cout << "YES\n";
	else
		cout << "NO\n";
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int t;
	cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}