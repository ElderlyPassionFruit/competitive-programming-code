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
	int cnt = 0;
	while (n % 2 == 0) {
		n /= 2;
		cnt++;
	}
	if (n == 1) {
		cout << "Yes\n";
	}
	else {
		cout << "No\n";
	}
	return 0;
}