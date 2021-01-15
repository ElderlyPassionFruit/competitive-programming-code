#include <bits/stdc++.h>

using namespace std;
#define all(a) a.begin(), a.end()

bool checkNum(string s) {
	if (s.empty()) return false;
	if (s.size() > 1 && s[0] == '0') return false;
	for (auto i : s) {
		if (i < '0' || i > '9') return false;
	}
	return s.size() <= 3;
}

bool check(string s) {
	if (s.size() < 7) return false;
	vector<string> have;
	have.push_back("");
	for (auto i : s) {
		if (i == '.') {
			have.push_back("");
		} else {
			have[have.size() - 1] += i;
		}
	}
	if (have.size() != 4) return false;
	for (auto i : have) {
		if (!checkNum(i)) return false;
	}
	return true;
}

string solve(string s) {
	int n = s.size();
	string ans = "";
	for (int i = 0; i < n; i++) {
		string now = "";
		for (int j = i; j < min(n, i + 15); j++) {
			now += s[j];
			if (check(now)) {
				if (now.size() > ans.size()) {
					ans = now;
				}
			}
		}
	}
	return ans;
}

signed main() {
	string s;
	while (cin >> s) {
		cout << solve(s) << "\n";
	}
	return 0;
}