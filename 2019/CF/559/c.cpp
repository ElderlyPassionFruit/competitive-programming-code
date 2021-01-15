#include <bits/stdc++.h>

using namespace std;
#define int long long

void solve() {
	int n;
	cin >> n;
	vector <int> next(n);
	for (auto &i : next)
		cin >> i;

	vector <int> ans;

	for (auto i : ans)
		cout << i << " ";
	cout << "\n";
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	for (int test = 0; test < t; test++) {
		solve();
	}
	return 0;
}