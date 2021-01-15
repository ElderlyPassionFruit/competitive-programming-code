#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

int n, m;
vector<int> a, b;

ld get(int mask) {
	int sumA = 0, sumB = 0;
	for (int i = 0; i < n; i++) {
		if (((mask >> i) & 1) == 0) continue;
		sumA += a[i];
		sumB += b[i];
	}
	if (sumA < m) return 0;
	return (ld) sumB / sumA;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n >> m;
	a.resize(n);
	b.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i] >> b[i];
	}
	ld ans = 0;
	for (int mask = 0; mask < (1 << n); mask++) {
		ans = max(ans, get(mask));
	}
	cout.precision(20);
	cout << ans << endl;
	return 0;
}