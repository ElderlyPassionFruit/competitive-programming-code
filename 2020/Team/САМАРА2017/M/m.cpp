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
	vector<pair<int, int> > a;
	cin >> n;
	a.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i].first;
		a[i].second = i;
	}
	sort(all(a));
	vector<pair<int, int> > ans;

	vector<int> zero;
	for (auto &i : a) {
		if (i.first == 0) {
			zero.push_back(i.second);
			continue;
		}
		if (i.first > zero.size()) {
			cout << "NO";
			return 0;
		}
		while (i.first--) {
			ans.push_back({i.second, zero.back()});
			zero.pop_back();
		}
		zero.push_back(i.second);
	}
	
	cout << "YES" << "\n";
	for (auto &i : ans)
		cout << i.first  + 1 << " " << i.second + 1 << "\n";
	return 0;
}