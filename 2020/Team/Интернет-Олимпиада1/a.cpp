#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x)( x).begin(),(x).end()

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	string s, t;
	cin >> s >> t;
	int n = s.size();
	map <char, int> cnt;
	for (auto i : t) {
		cnt[i]++;
	}
	ll ans = 0;
	int l = 0, r = 0;
	while (l < n) {
		while (r < n && cnt[s[r]] > 0) {
			cnt[s[r]]--;
			r++;
		}
		ans += r - l;
		cnt[s[l]]++;
		l++;
	}
	cout << ans << endl;
	return 0;
}