#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

#define int ll
int n;
vector<pair<pair<int, pair<int, int>>, int>> a;
int L, R;

void read() {
	cin >> n;
	a.resize(n);
	int it = 1;
	for (auto &i : a) {
		cin >> i.first.second.first >> i.first.second.second >> i.first.first;
		i.second = it++;
	}
	cin >> L >> R;
}

bool check(int t) {
	vector<pair<int, int>> have;
	for (int i = 0; i < t; i++) {
		have.push_back(a[i].first.second);
	}
	sort(all(have));
	vector<pair<int, int>> ans;
	for (auto [l, r] : have) {
		if (ans.empty() || ans.back().second < l) {
			ans.push_back({l, r});
		} else {
			chkmax(ans[ans.size() - 1].second, r);
		}
	}
	for (auto [l, r] : ans) {
		if (l <= L && R <= r) return true;
	}
	return false;
}

void run() {
	sort(all(a));
	int l = 0, r = n + 1;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (check(mid)) {
			r = mid;
		} else {
			l = mid;
		}
	}
	if (r == n + 1) {
		cout << -1 << endl;
	} else {
		vector<int> ans;
		for (int i = 0; i < r; i++) {
			ans.push_back(a[i].second);
		}
		sort(all(ans));
		cout << ans.size() << "\n";
		for (auto i : ans) {
			cout << i << " ";
		}
		cout << "\n";
	}
}

void write() {

}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
	read();
	run();
	write();
	return 0;
}