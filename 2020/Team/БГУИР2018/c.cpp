#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

#define int ll

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int n, m;
	cin >> n >> m;
	string s;
	cin >> s;
	map <char, pair<int, int> > can;
	for (int i = 0; i < m; i++) {
		char x;
		cin >> x;
		int l, r;
		cin >> l >> r;
		can[x] = {l, r};
	}

	/*cout << "s = " << s << endl;
	cout << "can = " << endl;
	for (auto i : can) {
		cout << i.first << " " << i.second.first << " " << i.second.second << endl;
	}*/

	vector<char> st;
	int cnt = 0;

	map<char, int> cnt1, cnt2;
	char last = '+';
	ll ans = 0;

	for (int i = 0; i < n; i++) {
		//cout << s[i] << endl;
		if (s[i] == ')') {
			if (st.back() == '-')
				cnt--;
			st.pop_back();
		}
		else if (s[i] == '(') {
			if (last != '-')
				st.push_back('+');
			else {
				st.push_back('-');
				cnt++;
			}
		}
		else if (s[i] >= 'a' && s[i] <= 'z') {
			if ((cnt + (last == '-')) % 2 == 1) {
				cnt2[s[i]]++;
			}
			else {
				cnt1[s[i]]++;
			}
		}
		else if (s[i] >= '0' && s[i] <= '9') {
			if ((cnt + (last == '-')) % 2 == 1) {
				ans -= s[i] - '0';
			}
			else {
				ans += s[i] - '0';
			}
		}
		last = s[i];
	}

	/*for (auto i : cnt1) {
		cout << i.first << " " << i.second << endl;
	}

	for (auto i : cnt2) {
		cout << i.first << " " << i.second << endl;
	}*/

	for (auto i : can) {
		if (cnt1[i.first] >= cnt2[i.first]) {
			ans += (ll) (cnt1[i.first] - cnt2[i.first]) * i.second.second; 
		}
		else {
			ans -= (ll) (cnt2[i.first] - cnt1[i.first]) * i.second.first;
		}
	}
	cout << ans << endl;
	return 0;
}

















