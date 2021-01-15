#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()
#define int ll
int n, b;
const int MAXN = 2e5 + 10;
int a[MAXN];

int get(int x) {
	int ans = 0;
	while (x) {
		ans++;
		x /= 2;
	}
	return ans;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n >> b;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	sort(a, a + n);
	int ans = 0;
	for (int i = 0; i < n; i++) {
		if (get(a[i]) * (i + 1) <= b) {
			ans = i + 1;
		}
	}
	cout << ans << endl;
	return 0;
}