#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int MAXN = 1e6 + 10;

int n;
int pref[MAXN][5];
int a[MAXN];

int getCost(int l, int r, int need) {
	int ans = 0;
	for (int i = 0; i <= 4; i++) {
		if (i == need) continue;
		int have = pref[r][i] - pref[l - 1][i];
		ans += abs(i - need) * have;
	}
	return ans;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n;
	int sum = 0;
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		sum += x;
		a[i + 1] = x;
	}
	sort(a + 1, a + n + 1);
	reverse(a + 1, a + n + 1);
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= 4; j++) {
			pref[i][j] = pref[i - 1][j];
		}
		pref[i][a[i]]++;
	}
	int ans = 4 * n;

	for (int x = 0; x <= sum / 4; x++) {
		if (x * 4 > sum) continue;
		int y = (sum - 4 * x) / 3;
		if (x * 4 + y * 3 != sum) continue;
		if (x + y > n) continue;
		int fans = 0;
		if (x > 0) fans += getCost(1, x, 4);
		if (y > 0) fans += getCost(x + 1, x + y, 3);
		if (x + y != n) fans += getCost(x + y + 1, n, 0);
		//cout << x << " " << y << " " << fans << endl; 
		assert(fans % 2 == 0);	
		ans = min(ans, fans / 2);
	}
	if (ans == 4 * n) ans = -1;
	cout << ans << endl;
 	return 0;
}