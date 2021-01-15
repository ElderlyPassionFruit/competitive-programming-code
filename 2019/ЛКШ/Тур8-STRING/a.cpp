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


void solve() {
	string s;
	cin >> s;
	auto z = z_function(s);
	z[0] = s.length();
	for (auto i : z)
		cout << i << " ";
	cout << endl;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	solve();
	return 0;
}