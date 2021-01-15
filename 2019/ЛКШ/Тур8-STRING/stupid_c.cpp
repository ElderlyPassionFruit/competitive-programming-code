#include <bits/stdc++.h>

using namespace std;
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

vector<int> z_function(string & s) {
	int n = s.size();
	vector<int> z(n, 0);
	int l = 0, r = 0;
	for (int i = 1; i < n; i++) {
		if (i <= r)
			z[i] = min(z[i - l], r - i + 1);
		while (z[i] + i < n && s[z[i]] == s[z[i] + i])
			z[i]++;
		if (z[i] + i - 1 > r)
			l = i, r = z[i] + i - 1;
	}
	return z;
}

bool check(string & s, string & t) {
	string x = s + '#' + t;
	auto z = z_function(x);
	for (int i = s.size(); i < x.size(); i++) {
		if (z[i] == s.size())
			return true;
	}
	return false;
}

void solve() {
	vector<string> a;
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		a.push_back(s);
	}
	string t;
	cin >> t;
	for (int i = 0; i < n; i++) {
		if (check(a[i], t))
			cout << "YES\n";
		else
			cout << "NO\n";
	}
}

signed main() {
	freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	solve();
	return 0;
}