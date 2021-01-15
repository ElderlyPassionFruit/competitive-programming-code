#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()
#define int ll
const int MAXN = 1e5 + 10, MAXBIT = 30;
int n, m, k;
int a[MAXN];

pair<ll, int> cnt[MAXBIT];

pair<ll, int> calc(int bit) {
	for (int i = 0; i < bit; i++) cnt[i] = {0LL, i};
	ll ans = 0;
	for (int i = 0; i < n; i++) {
		if ((a[i] >> bit) & 1) {
			ans += a[i];
		} else {
			ans += (1 << bit);
			ans += a[i];
			for (int j = 0; j < bit; j++) {
				bool flag = (a[i] >> j) & 1;
				if (flag) cnt[j].first -= (1 << j);
				else cnt[j].first += (1 << j);
			}
		}
	}
	int x = (1 << bit);
	/*cout << ans << " " << x << endl;
	cout << "cnt = " << endl;
	for (int i = 0; i < bit; i++) {
		cout << cnt[i].first << " " << cnt[i].second << endl;
	}*/
	sort(cnt, cnt + bit);
	reverse(cnt, cnt + bit);
	for (int i = 0; i < min(k - 1, bit); i++) {
		if (cnt[i].first <= 0) break;
		ans += cnt[i].first;
		x += (1 << cnt[i].second);
	}
	return {ans, x};
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n >> m >> k;
	if (k == 0) {
		cout << 0 << endl;
		exit(0);
	}
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	//calc(0);
	//return 0;
	ll ans = 0;
	for (int i = 0; i < n; i++) {
		ans += a[i];
	}
	int x = 0;
	for (int i = m - 1; i >= 0; i--) {
		pair<ll, int> fans = calc(i);
		//cout << i << " " << fans.first << " " << fans.second << endl;
		if (fans.first < ans) continue;
		ans = fans.first;
		x = fans.second;
	}
	ll sum = 0;
	for (int i = 0; i < n; i++) {
		sum += a[i];
	}
	if (sum == ans) x = 0;
	cout << x << endl;
	return 0;
}