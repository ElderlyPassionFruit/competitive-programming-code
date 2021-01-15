#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

vector<int> get(string & s) {
	int n = s.size();
	vector<int> ans;
	int last = -1;
	for (int i = 0; i < n; i++) {
		if (last == s[i] - 'a') {
			ans.push_back(s[i] - 'a' + 26);
			last = s[i] - 'a' + 26;
		}
		else {
			ans.push_back(s[i] - 'a');	
			last = s[i] - 'a';
		}
	}
	return ans;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int n;
	cin >> n;
	vector<string> s(n);
	for (auto &i : s)
		cin >> i;
	vector<vector<int> > ans(n);
	for (int i = 0; i < n; i++) {
		ans[i] = get(s[i]);
	}

	set<int> have;
	for (auto i : ans)
		for (auto j : i)
			have.insert(j);
	map <int, int> coord;
	int cnt = 0;
	for (auto i : have)
		coord[i] = cnt++;
	cout << cnt << "\n";
	for (auto i : ans){
		for (auto j : i){
			cout << coord[j] + 1 << " ";
		}
		cout << "\n";
	}

	return 0;
}











