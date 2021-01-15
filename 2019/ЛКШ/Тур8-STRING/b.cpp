#include <bits/stdc++.h>

using namespace std;
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

vector<int> prefix_function(string & s) {
	int n = s.size();
	vector <int> p(n, 0);
	for (int i = 1; i < n; i++) {
		p[i] = p[i - 1];
		while (p[i] > 0 && s[p[i]] != s[i])
			p[i] = p[p[i] - 1];
		if (s[p[i]] == s[i])
			p[i]++;
	}
	return p;
}

void solve() {
	string s;
	cin >> s;
	auto p = prefix_function(s);
	for (auto i : p)
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