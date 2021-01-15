#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int MAXN = 1e6 + 10;
int a[MAXN], b[MAXN];
int ans[MAXN];
int n;

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n;
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		a[x] = i;
	}
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		b[x] = i;
	}
	for (int i = 0; i < n; i++) {
		ans[i] = n;
	}
	
	for (int i = 1; i <= n; i++) {
		for (int j = 1; i * j < n; j++) {
			int pos = (a[i] - b[j] + n) % n;
			ans[pos] = min(ans[pos], i * j); 
		}
	}

	for (int i = 0; i < n; i++) {
		cout << ans[i] << "\n";
	}
	return 0;
}