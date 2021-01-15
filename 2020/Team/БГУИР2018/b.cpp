#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

int query(int x) {
	cout << "? " << x << endl;
	int ans;
	cin >> ans;
	return ans;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int cnt = query(0);
	int have = 0;
	int a = 0;
	for (int i = 0; i < 29; i++) {
		int x = query(1 << i);
		if (x != cnt + 1) {
			a += (1 << i);
			have++;
		}
	}
	if (have != cnt) {
		a += (1 << 29);
	}
	cout << a << endl;
	return 0;
}