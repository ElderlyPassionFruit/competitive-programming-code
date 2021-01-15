#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()


#define int ll

bool calc(int x) {
	int ans = 1;
	for (int i = 2; i * i <= x; i++) {
		if (x % i == 0) {
			int cnt = 0;
			while (x % i == 0) {
				x /= i;
				cnt++;
			}
			cnt++;
			ans *= cnt;
			if (ans >= 100) return true;
		}
	}
	if (x > 1) {
		ans *= 2;
	}
	return ans >= 100;
}

const int INF = 1e12;
const int MY = 1e10;
signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int x;
	cin >> x;
	if (x >= INF) {
		cout << (x + MY) / MY * MY;
		return 0;
	}
	for (int i = x; i <= x * 101 / 100; i++) {
		if (calc(i)) {
			cout << i;
			return 0;
		}
	}
	cout << -1;
	return 0;
}