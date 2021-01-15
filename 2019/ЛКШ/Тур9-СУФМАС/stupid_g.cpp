#include <bits/stdc++.h>

using namespace std;
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

vector<int> z_function(string s) {
	int n = s.size();
	vector<int> z(n);
	int l = 0, r = 0;
	for (int i = 1; i < n; i++) {
		if (i <= r)
			z[i] = min(z[i - l], r - i + 1);
		while (i + z[i] < n && s[z[i]] == s[i + z[i]])
			z[i]++;
		if (z[i] + i - 1 > r)
			l = i, r = z[i] + i - 1;
	}
	return z;
}

bool check(string s, string t) {
	string x = s + "@" + t;
	auto z = z_function(x);
	for (int i = s.size(); i < x.size(); i++)
		if (z[i] == s.size())
			return true;
	return false;
}

string substr(string s, int l, int r) {
	string ans = "";
	for (int i = l; i <= r; i++)
		ans += s[i];
	return ans;
}

bool check(string s, int l, int r) {
	int n = s.size();
	auto L = substr(s, 0, l - 1);
	auto R = substr(s, r + 1, n - 1);
	auto mid = substr(s, l, r);
	for (int i = 1; i < mid.size(); i++) {
		auto x = substr(mid, 0, i - 1);
		auto y = substr(mid, i, mid.size() - 1);
		if (check(x, L) && check(y, R))
			return true;
	}
	return false;
}

void solve() {
	string s;
	cin >> s;
	int n = s.size();
	int ans = 0;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			ans += check(s, i, j);
		}
	}
	cout << ans << endl;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	solve();
	return 0;
}