#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct segment{
	int l, r;
	segment() {}
	segment(int a, int b) {
		l = a, r = b;
	}
};

bool operator<(const segment & a, const segment & b) {
	return a.l < b.l;
}

int get(vector<segment> a) {
	sort(all(a));
	vector<segment> ans;
	for (auto i : a) {
		if (ans.empty() || i.l > ans.back().r) {
			ans.push_back(i);
		}
		else {
			chkmax(ans[ans.size() - 1].r, i.r);
		}
	}
	return ans.size();
}

void solve() {
	int n;
	cin >> n;
	vector<segment> a(n);
	for (auto &i : a)
		cin >> i.l >> i.r;
	int ans = 0;
	for (int i = 0; i < n; i++) {
		vector<segment> b = a;
		b.erase(b.begin() + i);
		chkmax(ans, get(b));
	}
	cout << ans << endl;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t--)
		solve();
	return 0;
}