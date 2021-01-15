#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

int n, m;
set<int> now;
vector<int> ans;

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		now.insert(i);
	}
	ans.resize(n, -1);
	for (int i = 0; i < m; i++) {
		int l, r, x;
		cin >> l >> r >> x;
		l--;
		r--;
		x--;
		while (true) {
			auto it = now.lower_bound(l);
			if (it == now.end()) break;
			if (*it == x) it++;
			if (it == now.end()) break;
			if (*it > r) break;
			ans[*it] = x;
			now.erase(it);
		}
	}
	for (auto i : ans) {
		cout << i + 1 << " ";
	}
	cout << endl;
	return 0;
}