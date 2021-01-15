#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

int calc(int x, int d) {
	int ans = 0;
	while (x % d == 0) {
		ans++;
		x /= d;
	}
	return ans;
}

void wr(int x, int d) {
	while (x) {
		cout << x % d << " ";
		x /= d;
	}
	cout << endl;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int x;
	cin >> x;
	wr(x, 2);
	cout << calc(x, 2) << endl;
	for (int i = 2; ; i++) {
		if (calc(x, i) == 2) {
			cout << i << endl;
		} 
	}
	return 0;
}