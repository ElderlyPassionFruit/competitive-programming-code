#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()
#define int long long

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int t;
	cin >> t;
	while (t--) {
		int a, n;
		cin >> a >> n;
		int k = (a / n);
		int min_ans = LLONG_MAX;
		for (int i = k - 5; i < k + 5; i++) {
			int kk = i * a;
			min_ans = min(min_ans, a ^ max(0LL, n * i));
		}
		cout << min_ans << endl;
	}
	return 0;
}