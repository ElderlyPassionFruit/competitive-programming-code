#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

bool checkLess(string & a, string & b) {
	if (a.size() != b.size()) return a.size() < b.size();
	return a < b;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	string s;
	cin >> s;
	int ans = 0;
	vector<string> fans;
	for (int i = 0; i < (int)s.size(); i++) {
		assert(s[i] != '0');
		int r = i;
		string now = "";
		now += s[i];
		while (r + 1 < s.size() && s[r + 1] == '0') now += s[r++];
		fans.push_back(now);
		ans++;
		i = r;
	}
	int kek = 0;
	for (int i = 1; i < (int)fans.size(); i++) {
		if (checkLess(fans[0], fans[i])) {
			kek = i;
		} 
		fans[0] += fans[i];
	}
	cout << ans - kek << endl;
	return 0;
}