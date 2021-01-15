#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int n, r;
	cin >> n >> r;
	set<int> have;
	vector<pair<int, int>> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i].first;
		a[i].second = i;
	}
	sort(all(a));
	int mx = -2e9 - 10;
	vector<int> ans(n);
	
	for (int i = 0; i < n; i++) {
		int x = min(max(mx + 1, a[i].first - r), a[i].first + r);
		ans[a[i].second] = x;
		mx = max(mx, x);
	}
	vector<int> fans = ans;
	sort(all(fans));
	fans.resize(unique(all(fans)) - fans.begin());
	cout << fans.size() << "\n";
	for (auto i : ans)
		cout << i << " ";
	cout << endl;
	return 0;
}