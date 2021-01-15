#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

int n;
vector<int> a;
int m;
vector<int> b;

bool check(int mid) {
	int pos = 0;
	for (int i = 0; i < n; i++) {
		if (a[i] >= mid) continue;
		while (pos < m && a[i] + b[pos] < mid)
			pos++;
		if (pos == m) return false;
		pos++;
	}
	return true;
}

vector<pair<int, int> > get_ans(int mid) {
	int pos = 0;
	vector<pair<int, int> > ans;
	for (int i = 0; i < n; i++) {
		if (a[i] >= mid) continue;
		while (pos < m && a[i] + b[pos] < mid)
			pos++;
		ans.push_back({i, pos});
		pos++;
	}
	return ans;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	freopen("wall.in", "r", stdin);
	freopen("wall.out", "w", stdout);
	cin >> n;
	a.resize(n);
	for (auto &i : a)
		cin >> i;
	cin >> m;
	b.resize(m);
	for (auto &i : b)
		cin >> i;

	int l = 0, r = 1e9;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (check(mid)) {
			l = mid;
		}
		else {
			r = mid;
		}
	}
	auto ans = get_ans(l);
	cout << l << " " << ans.size() << "\n";
	for (auto i : ans) {
		cout << i.first + 1 << " " << i.second + 1 << "\n";
	}

	return 0;
}

/*
3 
10 5 10
1 
5

*/