#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()
#define int ll

vector<pair<int, int>> get(int sz, int cnt, int s) {
	vector<pair<int, int>> ans;
	vector<int> last = {0};
	for (int i = 0; i < cnt; i++) {
		vector<int> nlast;
		for (int j = 0; j < sz; j++) {
			nlast.push_back(s);
			for (auto x : last) {
				ans.push_back({x, s});
			}	
			s++;
		}
		last = nlast;
	}
	for (auto x : last) {
		ans.push_back({x, 1});
	}
	return ans;
}

int pow(int a, int n) {
	int ans = 1;
	for (int i = 0; i < n; i++) {
		ans *= a;
	}
	return ans;
}

pair<int, vector<int>> get(int k, int cnt) {
	vector<int> ans;
	int fans = 0;
	while (k) {
		int now = 1;
		while (pow(now + 1, cnt) <= k) now++;
		fans += now * cnt;
		ans.push_back(now);
		k -= pow(now, cnt);
	}
	return {fans, ans};
}

//const int BUBEN = 6;

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int k;
	cin >> k;
	vector<pair<int, int>> fans;
	int s = 2;
	for (int cnt = 1; cnt <= 13; cnt++) {
		auto have = get(k, cnt);
		if (have.first <= 998) {
			for (auto sz : have.second) {
				auto fadd = get(sz, cnt, s);
				for (auto x : fadd) {
					fans.push_back(x);
				}
				s += sz * cnt;
				k -= pow(sz, cnt);
			}
			break;
		} 
	}
	assert(!fans.empty());
	/*cout << "fans = " << endl;
	for (auto i : fans) {
		cout << i.first << " " << i.second << endl;
	}*/
	assert(s < 1000);
	vector<vector<int>> ans(s, vector<int> (s, 0));
	for (auto [x, y] : fans) {
		ans[x][y] = true;
		ans[y][x] = true;
	}
	cout << s << endl;
	for (auto i : ans) {
		for (auto j : i) {
			cout << (j == 1 ? "Y" : "N");
		}
		cout << endl;
	}
	return 0;
}