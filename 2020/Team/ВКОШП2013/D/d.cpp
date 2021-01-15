#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x)( x).begin(),(x).end()
#define int ll

int n, k;
vector<int> a;

bool check(int x) {
	int painted = 0;
	for (auto i : a) {
		if (i < x) return false;
		if (painted + x >= i)
			painted += x;
		else
			painted = i;
	}
	return painted <= k;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	freopen("fence.in", "r", stdin);
	freopen("fence.out", "w", stdout);
	cin >> n >> k;
	a.resize(n);
	for (auto &i : a)
		cin >> i;
	sort(all(a));
	int l = 0, r = k + 1;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (check(mid))
			l = mid;
		else
			r = mid;
	}
	cout << l << endl;
	return 0;
}z