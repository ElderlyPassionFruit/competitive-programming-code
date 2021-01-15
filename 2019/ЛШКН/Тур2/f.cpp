#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n;

vector<int> query(vector<int> q) {
	if (q.empty()) {
		return vector<int> (n, 1e9 + 10);
	}

	cout << q.size() << endl;
	for (auto i : q)
		cout << i + 1 << " ";
	cout << endl;
	vector<int> ans(n);
	for (auto &i : ans) {
		cin >> i;
	}
	return ans;
}

void out_ans(vector<int> ans) {
	cout << "-1" << endl;
	for (auto i : ans)
		cout << i << " ";
	cout << endl;
	exit(0);
}

void solve() {
	cin >> n;
	vector<int> ans(n, 1e9 + 10);

	for (int i = 0; i < 10; i++) {
		vector<int> fcheck;
		for (int j = 0; j < n; j++) {
			if ((j >> i) & 1)
				fcheck.push_back(j);
		}
		auto help = query(fcheck);

		for (int j = 0; j < n; j++) {
			if ((j >> i) & 1)
				continue;
			chkmin(ans[j], help[j]);
		}
	}

	for (int i = 0; i < 10; i++) {
		vector<int> fcheck;
		for (int j = 0; j < n; j++) {
			if (!((j >> i) & 1)) 
				fcheck.push_back(j);
		}
		auto help = query(fcheck);
		for (int j = 0; j < n; j++) {
			if (!((j >> i) & 1)) 
				continue;
			chkmin(ans[j], help[j]);	
		}
	}
	out_ans(ans);
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	solve();
	return 0;
}