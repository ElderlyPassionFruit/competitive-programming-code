#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(s) (s).begin(),(s).end()

string s;
int n;
vector<int> cnt(10);
	
bool check(int len) {
	vector<int> have = cnt;
	for (int i = 0; i < len; i++) {
		have[s[i] - '0']--;
	}
	for (auto i : have)
		if (i < 0) 
			return false;
	return true;
}

string gen() {
	string ans = "";
	for (int i = 1; i <= 9; i++) {
		if (cnt[i]) {
			ans += '0' + i;
			cnt[i]--;
			break;
		}
	}
	if (ans.empty()) {
		cout << -1 << endl;
		exit(0);
	}
	for (int i = 0; i <= 9; i++)
	for (int j = 0; j < cnt[i]; j++){
		ans += '0' + i;
		if (ans.size() == s.size() + 1)
			break;
	}
	while (ans.size() > s.size() + 1)
		ans.pop_back();
	return ans;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> s;
	n = s.size();
	for (auto &i : cnt)
		cin >> i;

	int l = 0, r = n + 1;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (check(mid))
			l = mid;
		else
			r = mid;
	} 
	r = l;
	if (r == n)
		r--;
	string now = "";
	for (int i = 0; i < r; i++) {
		cnt[s[i] - '0']--;
		now += s[i];
	}
	/*cout << "r = " << r << endl;
	cout << now << endl;
	cout << "cnt = " << endl;
	for (auto i : cnt)
		cout << i << " ";
	cout << endl;*/
	while (r >= 0) {
		for (int i = s[r] - '0' + 1; i <= 9; i++) {
			if (cnt[i]) {
				now += i + '0';
				cnt[i]--;
				//cout << "now " << now << endl;
				for (int j = 0; j <= 9; j++) {
					if (now.size() == s.size())
						break;
					for (int k = 0; k < cnt[j]; k++) {
						now += j + '0';
						if (now.size() == s.size())
							break;
					}
				}
				if (now.size() == s.size()) {
					cout << now << endl;
					return 0;
				}
				else {
					cout << "-1\n";
					return 0;
				}
			}
		}
		if (!now.empty()) {
			cnt[now.back() - '0']++;
			now.pop_back();
		}
		r--;
	}
	string ans = gen();
	if (ans.size() == s.size() + 1) {
		cout << ans << endl;
	}
	else {
		cout << "-1" << endl;
	}
	return 0;
}









