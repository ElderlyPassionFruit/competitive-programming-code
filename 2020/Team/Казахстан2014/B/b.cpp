#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

vector<vector<char>> make(vector<vector<char>> a) {
	int n = 16;
	vector<vector<char>> ans(16, vector<char> (16));
	for(int i =0 ; i< 16;++i) for(int j=0 ; j< 16;++j) ans[j][n-i-1] =a[i][j];
	return ans;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	vector<vector<char>> a(16, vector<char> (16));
	for(int i =0 ; i< 16;++i) for(int j=0 ; j< 16;++j) cin>>a[i][j];
	bool L = false, R = false;
	for (auto i : a) for (auto j : i) {
		if (j == 'L') L = true;
		if (j == 'R') R = true;
	}
	if (R) a = make(a);
	else if (L) {
		a = make(a);
		a = make(a);
		a = make(a);
	} else {
		assert(false);
	}
	for (auto i : a) {
		for (auto j : i) {
			cout << j;
		}
		cout << endl;
	}
	return 0;
}