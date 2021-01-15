#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

#define int ll

int get_int(string s) {
	int ans = 0;
	for (auto i : s) {
		ans *= 10;
		ans += i - '0';
		ans = min(ans, 100000LL);
	}
	return ans;
}

bool check(string x, string y) {
	if (x.empty()) {
		if (y[0] == '0') return false;
		if (y.size() == 1 && y == "1") return false;
		return true;
	} else {
		if (x.size() == 1 && x == "1") return false;
		if (y.size() == 1 && y == "1") return false;
		if (x[0] == '0' || x.back() == '0') return false;
		if (y[0] == '0') return false;
		if ((int)x.size() - 1 > get_int(y)) return false;
		return true;
	}
}

string gen(string x, string y) {
	if (x.empty()) {
		return "10^{" + y + "}"; 
	} else {
		if (x.size() == 1) {
			return x + " \\cdot 10^{" + y + "}";
		} else {
			string ans = "";
			ans += x[0];
			ans += '.';
			ans += x.substr(1, x.size() - 1);
			ans += " \\cdot 10^{";
			ans += y;
			ans += "}";
			return ans;
		}
	}
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	string s;
	cin >> s;
	vector<pair<string, string>> ans;
	if (s.size() <= 2) {
		cout << "Unique" << endl;
		exit(0);
	}
	for (int i = (int)s.size() - 3; i > 0; i--) {
		if (s[i] != '1' || s[i + 1] != '0') continue;
		string x = s.substr(0, i);
		string y = s.substr(i + 2, s.size() - i - 1);
		if (check(x, y)) {
			ans.push_back({y, gen(x, y)});
		}
	}
	if (s[0] == '1' && s[1] == '0') {
		string x = "";
		string y = s.substr(2, s.size() - 2);
		if (check(x, y)) {
			ans.push_back({y, gen(x, y)});
		}
	}
	if (ans.empty()) {
		cout << "Unique" << endl;
		exit(0);
	}
	sort(all(ans), [&] (pair<string, string> i, pair<string, string> j) {
		if (i.first.size() != j.first.size()) {
			return i.first.size() < j.first.size();
		}
		return i.first < j.first;
	}); 
	reverse(all(ans));
	for (auto i : ans) {
		cout << i.second << "\n";
	}
	return 0;
}