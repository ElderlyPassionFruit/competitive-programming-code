#pragma GCC optimize("sse,sse2,sse3,sse4.1,ssse3,sse4.2,sse4,abm,mmx,avx,avx2,popcnt,tune=native")
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x)( x).begin(),(x).end()

string s, t;
int n;

vector<int> get_s(int l, int r) {
	vector<int> ans(26);
	for (int i = l; i < r; i++)
		ans[s[i] - 'a']++;
	return ans;
}

vector<int> get_t(int l, int r) {
	vector<int> ans(26);
	for (int i = l; i < r; i++)
		ans[t[i] - 'a']++;
	return ans;
}

pair<string, bool> solve(int sl, int sr, int tl, int tr);

pair<string, bool> get_1(int sl, int sr, int tl, int tr) {
	int sm = (sl + sr) / 2;
	auto s_l = get_s(sl, sm);
	auto s_r = get_s(sm, sr);

	int tm = (tl + tr) / 2;
	auto t_l = get_t(tl, tm);
	auto t_r = get_t(tm, tr);
	if (s_l == t_l && s_r == t_r){
		auto l = solve(sl, sm, tl, tm);
		if (!l.second) return {"", false};
		auto r = solve(sm, sr, tm, tr);
		if (!r.second) return {"", false};
		pair<string, bool> ans;
		ans.first = l.first + r.first + "0";
		ans.second = l.second && r.second;
		return ans;
	}
	else {
		return {"", false};
	}
}

pair<string, bool> get_2(int sl, int sr, int tl, int tr) {
	int sm = (sl + sr) / 2;
	auto s_l = get_s(sl, sm);
	auto s_r = get_s(sm, sr);

	int tm = (tl + tr) / 2;
	auto t_l = get_t(tl, tm);
	auto t_r = get_t(tm, tr);
	if (s_l == t_r && s_r == t_l) {
		auto l = solve(sl, sm, tm, tr);
		if (!l.second) return {"", false};
		auto r = solve(sm, sr, tl, tm);
		if (!r.second) return {"", false};
		pair<string, bool> ans;
		ans.first = l.first + r.first + "1";
		ans.second = l.second && r.second;
		return ans;
	}
	else {
		return {"", false};
	}
}

pair<string, bool> solve(int sl, int sr, int tl, int tr) {
	if (sl == sr - 1) {
		if (s[sl] != t[tl]) {
			return {"", false};
		}
		return {"", true};
	}
	auto x = get_1(sl, sr, tl, tr);
	if (x.second) return x;
	auto y = get_2(sl, sr, tl, tr);
	if (y.second) return y;
	return {"", false};
}

void solve() {
	cin >> s >> t;
	n = s.size();
	auto ans = solve(0, n, 0, n);
	if (ans.second) {
		cout << "Yes" << "\n";
		for (auto i : ans.first)
			cout << i << " ";
		cout << "\n";
	}
	else {
		cout << "No" << "\n";
	}
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	freopen("processing.in", "r", stdin);
	freopen("processing.out", "w", stdout);
	int t;
	cin >> t;
	while(t--)
		solve();
	return 0;
}