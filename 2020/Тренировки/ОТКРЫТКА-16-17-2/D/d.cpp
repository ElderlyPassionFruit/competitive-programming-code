#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

#define int ull

map<int, pair<int, int>> used;

pair<int, int> query(int x) {
	if (used.count(x)) return used[x];
	cout << "X " << x << endl;
	pair<int, int> ans;
	cin >> ans.first;
	assert(ans.first != -1);
	cin >> ans.second;
	used[x] = ans;
	return ans;
}

void out_ans(int x) {
	cout << "N " << x << endl;
	string s;
	cin >> s;
	if (s == "Correct") return;
	assert(false);
}

void solve() {
	used.clear();
	int l = 0, r = 60;
	int ans = 0;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		pair<int, int> fans = query(1LL << mid);
		chkmax(ans, fans.second);
		if (fans.first == 0)
			r = mid;
		else
			l = mid;
	}
	pair<int, int> fans = query(1LL << l);
	out_ans(fans.second);
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int q;
	cin >> q;
	while (q--)
		solve();
	return 0;
}