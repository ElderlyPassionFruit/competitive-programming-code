#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()
#define int ll
const int MAXK = 60;

int cnt[MAXK];

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int n;
	cin >> n;
	int a1 = -1, a2 = -1, cnt1 = 0, cnt2 = 0;
	for (int i = 0; i < n; i++) {
		ll a;
		cin >> a;
		if (a1 == -1) {
			a1 = a;
		}
		if (a != a1 && a2 == -1) {
			a2 = a;
		}
		if (a1 == a) cnt1++;
		if (a2 == a) cnt2++;
		for (int bit = 0; bit < MAXK; bit++) {
			if ((a >> bit) & 1LL) {
				cnt[bit]++;
			}
		}
	}

	int k = max(cnt1, cnt2);
	int ans = 0;
	for (int i = 0; i < MAXK; i++) {
		if (cnt[i] % k) {
			ans |= (1LL << i);
		}
	}
	cout << ans << endl;
	return 0;
}