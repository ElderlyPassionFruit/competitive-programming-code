#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int MAXN = 1e6 + 10;
int n, k;
int a[MAXN];

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		a[x] = x;
	}
	for (int i = MAXN - 2; i > 0; i--) {
		if (!a[i]) a[i] = a[i + 1];
	}
	for (int ans = MAXN - 1; ans >= 1; ans--) {
		if (a[1] < ans) continue;
		bool ok = true;		
		if (ans > k + 1) {
			for (int i = ans; i + k + 1 < MAXN; i += ans) {
				ok &= (!a[i + k + 1]) || (a[i + k + 1] >= i + ans); 
			}	
		}
		if (ok) {
			cout << ans << endl;
			return 0;
		}
	}
	assert(false);
	return 0;
}