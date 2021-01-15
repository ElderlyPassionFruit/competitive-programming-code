#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int n, p;
	cin >> n >> p;
	int k = 0;
	for (int i = 0; i <= n; i++) {
		if (i * 100 <= n * p)
			k = i;
	}
	cout << "[";
	for (int i = 0; i < k; i++)
		cout << "*";
	for (int i = 0; i < n - k; i++)
		cout << ".";
	cout << "]";
	cout << endl;
	return 0;
}