#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	vector<int> a;
	for (int i = 0; i <= 1000; i++) {
		int x = sqrt(4 * i + 1);
		if (x * x == 4 * i + 1) {
			cout << i << " ";
			a.push_back(i);
		}
	}
	cout << endl;
	for (int i = 1; i < a.size(); i++)
		cout << a[i] - a[i - 1] << " ";
	cout << endl;
	return 0;
}