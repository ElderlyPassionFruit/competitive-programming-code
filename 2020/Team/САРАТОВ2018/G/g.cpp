#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	string s;
	cin >> s;
	map <char, int> cnt;
	for (int i = 0; i < 26; i++) {
		cin >> cnt[i + 'a'];
	}
	int l = 0, r = 0;
	int ans = 0;
	while (l < s.size()) {
		while (r < s.size() && cnt[s[r]] > 0) {
			cnt[s[r]]--;
			r++;
		}
		ans = max(ans, r - l);
		if (r > l)
			cnt[s[l]]++;
		l++;
		r = max(r, l);
	}
	cout << ans << endl;
	return 0;
}	