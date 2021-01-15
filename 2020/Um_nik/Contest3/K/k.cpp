#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int MAXN = 51;
const int MAXSUM = 1e6 + 10;

int n, d;
bitset<MAXSUM> dp;

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n >> d;
	dp[0] = 1;
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		dp |= dp << x;
	}
	int now = 0;
	int ans = 0;
	while (true) {
		bool ok = false;
		for (int i = now + d; i > now; i--) {
			if (dp[i]) {
				ans++;
				now = i;
				ok = true;
				break;
			}
		}
		if (!ok) {
			cout << now << " " << ans << endl;
			return 0;
		}
	}
	return 0;
}