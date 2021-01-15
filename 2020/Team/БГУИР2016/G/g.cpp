#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()
#define int ll
signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int n;
	cin >> n;
	int cur_p = 1;
	int cur_num = 0;
	int cur_p2 = 2;
	for (int i = 0; i < n; i++) {
		if ((cur_num + cur_p) % cur_p2 == 0) {
			cur_num += cur_p;
		} else {
			cur_num += cur_p * 2;
		}
		cur_p2 *= 2;
		cur_p *= 10;
	}
	cout << cur_num << endl;
	return 0;
}