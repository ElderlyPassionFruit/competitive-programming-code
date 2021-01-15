#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()
#define int ll

int c_n_k(int n, int k) {
	int ans = 1;
	for (int i = 1; i <= n; i++)
		ans = ans * i;
	for (int i = 1; i <= n - k; i++)
		ans /= i;
	for (int i = 1; i <= k; i++)
		ans /= i;
	return ans;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	for (int n = 1; n <= 10; n++) {
		for (int k = 1; k <= 10; k++) {
			cout << c_n_k(n, k) << " ";
		}
		cout << endl;
	}
	return 0;
}