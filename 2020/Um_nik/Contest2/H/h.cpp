#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

int a;
string s;
int n;
const int MAXVAL = 4000 * 9 + 228;

int cnt[MAXVAL];

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> a;
	cin >> s;
	n = s.size();
	for (int l = 0; l < n; l++) {
		int val = 0;
		for (int r = l; r < n; r++) {
			val += s[r] - '0';
			cnt[val]++;
		}
	}
	ll ans = 0;
	for (int l = 0; l < n; l++) {
		int val = 0;
		for (int r = l; r < n; r++) {
			val += s[r] - '0';
			if (a == 0) {
				if (val == 0) {
					ans += n * (n + 1) / 2;
				} else {
					ans += cnt[0];
				}
			} else if (val != 0 && a % val == 0 && a / val < MAXVAL) {
				ans += cnt[a / val];
			}
		}
	}
	cout << ans << endl;
	return 0;
}