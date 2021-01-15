#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	ll a, n;
	cin >> n >> a;
	while (n != 1) {
		cout << (1 - a % 2) << " ";
		if (a % 2 == 0) {
			n -= (n + 1) / 2;
		} else {
			n -= n / 2;
		}
		a = (a + 1) / 2;
		//cout << endl;
		//cout << n << " " << a << endl;
	}
	return 0;
}