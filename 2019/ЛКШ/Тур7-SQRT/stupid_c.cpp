#include <bits/stdc++.h>

using namespace std;
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

vector<int> z_function(string &s) {
	int sz = s.size();
	vector<int> z(sz, 0);
	int l = 0, r = 0;
	for (int i = 1; i < sz; i++) {
		if (i <= r)
			z[i] = min(z[i - l], r - i + 1);
		while (z[i] + i < sz && s[z[i]] == s[z[i] + i])
			z[i]++;
		if (r < z[i] + i - 1)
			l = i, r = z[i] + i - 1;
	}
	return z;
}

bool cnt(string & s, string & t) {
	string x = s + '#' + t;
	//cout << "x = " << x << endl;
	auto z = z_function(x);
	//cout << "z = ";
	//for (auto i : z)
	//	cout << i << " ";
	//cout << endl;
	int cnt = 0;
	for (int i = s.size(); i < x.size(); i++) {
		cnt += (z[i] == s.size());
	}
	return cnt;
}

void solve() {
	int n, q;
	cin >> n >> q;
	vector<string> s(n);
	for (int i = 0; i < n; i++)
		cin >> s[i];

	for (int i = 0; i < q; i++) {
		int l, r;
		string x;
		cin >> l >> r >> x;
		l--;
		r--;
		int ans = 0;
		for (int j = l; j <= r; j++) {
			ans += cnt(x, s[j]);
		}
		cout << ans << "\n";
	}
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	solve();
	return 0;
}