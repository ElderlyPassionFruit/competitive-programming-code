#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

vector<pair <int, char> > get(string s) {
	int n = s.size();
	char last = s[0];
	int pos = 0;
	vector<pair <int, char> > ans;
	for (int i = 1; i < n; i++) {
		if (s[i] != last) {
			ans.push_back({i - pos, last});
			last = s[i];
			pos = i;
		}
	}
	ans.push_back({n - pos, last});
	return ans;
}

void solve() {
	string s, t;
	cin >> s >> t;
	auto help = get(s);
	auto help2 = get(t);
	if (help.size() != help2.size()) {
		cout << "NO\n";
		return;
	}
	int n = help.size();
	for (int i = 0; i < n; i++) {
		if (help[i].second != help2[i].second) {
			cout << "NO\n";
			return;
		}
		if (help[i].first > help2[i].first) {
			cout << "NO\n";
			return;
		}
	}
	cout << "YES\n";
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}