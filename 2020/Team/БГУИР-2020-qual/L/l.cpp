#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

vector<bool> used;
vector<int> ans;

void gen(ll x, int n) {
	ans.clear();
	for (int i = n; i >= 1; i--) {
		if (used[i] || x < i) continue;
		ans.push_back(i);
		x -= i;
		used[i] = true;
	}
	cout << ans.size() << endl;
	for (auto i : ans)
		cout << i << " ";
	cout << endl;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int n;
	cin >> n;
	if ((ll) (n + 1) * n / 2 % 3 != 0 || n <= 3) {
		cout << "Impossible";
		return 0;
	}
	cout << "Possible" << endl;
	ll x = (ll) (n + 1) * n / 6;
	used.assign(n + 1, false);
	gen(x, n);
	gen(x, n);
	gen(x, n);
	return 0;
}