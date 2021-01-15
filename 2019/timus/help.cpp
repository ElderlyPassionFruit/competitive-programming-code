#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n, m;
vector<int> p;

vector<int> z_function(string s) {
	int n = s.size();
	vector<int> z(n, 0);
	int l = 0, r = 0;
	for (int i = 1; i < n; i++) {
		if (i <= r) 
			z[i] = min(r - i + 1, z[i - l]);
		while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
		if (i + z[i] - 1 > r)
			l = i, r = i + z[i] - 1;
	}
	return z;
}

vector<int> gen_z(vector<int> p) {
	set<int> have;
	int n = p.size();
	vector<vector<int>> fdel(p.size());
	vector<int> z(n);
	for (int i = n - 1; i >= 1; i++) {
		have.insert(i);
		fdel[i - p[i]].push_back(i);
		for (auto j : fdel[i]) 
			have.erase(j);
		if (have.empty()) continue;
		z[i] = (*(--have.end())) - i + 1;
	}
	return z;
}

string gen_s(vector<int> z) {
	string ans = "a";
}

void solve() {
	for (int i = 0; i < n; i++) {
		if (p[i] > i || (i > 0 && p[i - 1] + 1 < p[i])) {
			cout << "NO\n";
			return;
		}
	}
	string ans = gen_s(gen_z(p));
	if (gen_z(p) != z_function(ans)) {
		cout << "NO\n";
		return;
	}
	cout << "YES\n";
	cout << ans << "\n";
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n >> m) {
		p.resize(n);
		for (auto &i : p)
			cin >> i;
		solve();
	}
	return 0;
}