#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

int n;
vector<pair<int, int>> a[3];
map<pair<int, int>, vector<int>> cnt;
string ans[3];
signed main() {
	freopen("snakes2.in", "r", stdin);
	freopen("snakes2.out", "w", stdout);
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n;
	for (int i = 0; i < n; i++) {
		int sz;
		cin >> sz;
		a[i].resize(sz);
		for (auto &x : a[i]) {
			cin >> x.first >> x.second;
			cnt[x].push_back(i);
		}
	}

	for (int i = 0; i < n; i++) {
		ans[i] = "";
		for (auto x : a[i]) {
			if (cnt[x].size() == 1) continue;
			if (cnt[x][0] == i) {
				ans[i] += "-";
				cnt[x][0] = -1;
			} else {
				ans[i] += "+";
				cnt[x][1] = -1;
			}		
		}
	}

	for (int i = 0; i < n; i++) {
		cout << ans[i] << endl;
	}
	return 0;
}