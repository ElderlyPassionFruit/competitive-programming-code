#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

char getOther(char x) {
	if (x == 'L') return 'R';
	return 'L';
}

int n;
string s;

bool check(string s) {
	vector<int> cnt(n);
	for (int i = 0; i < n; i++) {
		int prev = (i - 1 + n) % n;
		int nxt = (i + 1) % n;
		int cnt = 0;
		cnt += s[prev] == 'R';
		cnt += s[nxt] == 'L';
		if (cnt != 1) continue;
		if (s[prev] == 'R' && s[i] == 'L') continue;
		if (s[nxt] == 'L' && s[i] == 'R') continue;
		return false;
	}
	return true;
}

bool check(int mask) {
	string now = s;
	for (int i = 0; i < n; i++) {
		if ((mask >> i) & 1) {
			now[i] = getOther(now[i]);
		}
	}
	return check(now);
}

void solve() {
	cin >> n;
	cin >> s;
	int ans = n;
	for (int mask = 0; mask < (1 << n); mask++) {
		if (check(mask)) {
			chkmin(ans, __builtin_popcount(mask));
		}
	}
	cout << ans << endl;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
	int t;
	cin >> t;
	while(t--) {
		solve();
	}
	return 0;
}