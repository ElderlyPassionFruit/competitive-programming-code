#include <bits/stdc++.h>

using namespace std;
#define int long long

bool check(string a) {
	for (int i = 1; i < a.size(); i++) {
		if (abs(a[i] - a[i - 1])==1)
			return false;
	}
	return true;
}


void solve() {
	string s;
	cin >> s;
	map <char, int> help;
	for (auto i : s) {
		help[i]++;
	}
	string ans1 = "";
	for (auto i : help) {
		if (i.first % 2 == 0) {
			for (int j = 0; j < i.second; j++) {
				ans1 += i.first;
			}
		}
	}

	string ans2 = "";

	for (auto i : help) {
		if (i.first % 2 != 0) {
			for (int j = 0; j < i.second; j++) {
				ans2 += i.first;
			}
		}
	}

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			if (check(ans1 + ans2)) {
				cout << ans1 + ans2 << endl;
				return;
			}
			if (check(ans2 + ans1)) {
				cout << ans2 + ans1 << endl;
				return;
			}
			reverse(ans1.begin(), ans1.end());
		}
		reverse(ans1.begin(), ans1.end());
	}

	cout << "No answer" << endl;
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