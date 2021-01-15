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
	int n = s.size();
	map<char, int> cnt;
	for (auto i : s)
		cnt[i]++;
	for (int i = 2; i < n; i++) {
		if (s[i - 2] == s[i] && s[i - 1] == s[i]) {
			char ans = 'a';
			while (true) {
				if (ans == s[i]) {
					ans = rand() % 26 + 'a';
					continue;
				}
				if (i + 1 < n && ans == s[i + 1]) {
					ans = rand() % 26 + 'a';
					continue;
				}
				break;
			}
			cnt[s[i]]--;
			for (int j = 0; j < 26; j++) {
				if (j == s[i] - 'a') continue;
				if (i + 1 < n && j == s[i + 1] - 'a') continue;
				if (cnt[ans] > cnt[j + 'a']) {
					ans = j + 'a';
				}
			}
			s[i] = ans;
			cnt[s[i]]++;
		}
	}

	for (int i = 0; i < n; i++) {
		if (cnt[s[i]] * 2 <= n) continue;
		char ans = 'a';
		while (true) {
			if (i - 1 >= 0 && ans == s[i - 1]) {
				ans = rand() % 26 + 'a';
				continue;
			}
			if (ans == s[i]) {
				ans = rand() % 26 + 'a';
				continue;
			}
			if (i + 1 < n && ans == s[i + 1]) {
				ans = rand() % 26 + 'a';
				continue;
			}
			break;
		}
		cnt[s[i]]--;
		for (int j = 0; j < 26; j++) {
			if (j == s[i] - 'a') continue;
			if (i + 1 < n && j == s[i + 1] - 'a') continue;
			if (i - 1 >= 0 && j == s[i - 1] - 'a') continue;
			if (cnt[ans] > cnt[j + 'a']) {
				ans = j + 'a';
			}
		}
		s[i] = ans;
		cnt[s[i]]++;
	}
	cout << s << endl;
	return 0;
}