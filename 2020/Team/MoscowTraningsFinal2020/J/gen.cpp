#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

mt19937 rnd(time(0));

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int n = 10000;
	cout << n << endl;
	for (int i = 0; i < n; i++) {
		cout << rnd() % (int)1e9 + 1 << " ";
	}
	cout << endl;
	return 0;
}