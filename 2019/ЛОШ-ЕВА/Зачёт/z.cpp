#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

vector<int> query(vector<int> a) {
	cout << "next ";
	for (auto i : a) cout << i << " ";
	cout << endl;
	int q;
	cin >> q;
	vector<int> ans(q);
	for (int i = 0; i < q; i++)
		cin >> ans[i];
	return ans;
}

void ans(vector<int> a) {
	if (a.size() == 1) {
		cout << "done" << endl;
		exit(0);
	}
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (true) {
		query({0, 1});
		if (query({0}).size() == 2) 
			break;
	}
	while (true) {
		ans(query({0, 1, 2, 3, 4, 5, 6, 7, 8, 9}));
	}
	return 0;
}