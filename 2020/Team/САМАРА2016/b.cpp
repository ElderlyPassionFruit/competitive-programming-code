#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int n;
	cin >> n;
	vector<int> ans;
	for (int i = 0; i < n; i++) {
		int a;
		cin >> a;
		a--;
		if (a == i){
			ans.push_back(i + 1);
		}
	}
	cout << (ans.size() + 1) / 2 << "\n";
	for (int i = 0; i + 1 < ans.size(); i+=2) {
		cout << ans[i] << " " << ans[i + 1] << "\n";
	}
	if ((ll)ans.size() % 2) {
		if (ans.back() != n) {
			cout << ans.back() << " " << n << endl;
		}
		else {
			cout << ans.back() << " " << 1 << endl;
		}
	}
	return 0;
}