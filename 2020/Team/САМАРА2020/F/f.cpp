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
	if (n == 1) {
		cout << 1 << "\n" << 1 << endl;
		exit(0);
	}
	if (n == 2) {
		cout << 2 << "\n" << 1 << " " << 2 << endl;
		exit(0);
	}
	vector<int> ans = {1, 3};
	int add = 2;
	while (ans.back() != n) {
		int nxt = ans.back() + add;
		nxt = min(nxt, n);
		ans.push_back(nxt);
	//	add++;
	}
	cout << ans.size() << endl;
	for (auto i : ans)
		cout << i << " ";
	cout << endl;
	return 0;
}