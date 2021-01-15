#include <bits/stdc++.h>
using namespace std;

#define int long long

struct fenvik
{
	vector <int> t;
	vector <int> arr;
	int n;
	fenvik() {
		t = {};
		arr = {};
		n = 0;
	}

	fenvik(int sz) {
		n = sz;
		t.assign(sz, 0);
		arr.assign(n, 0);
	}

	int sum(int r) {
		int ans = 0;
		for (int i = r; i >= 0; i = (i & (i + 1)) - 1)
			ans += t[i];
		return ans;
	}

	void set_val(int r, int val) {
		int delta = val - arr[r];
		arr[r] = val;
		for (int i = r; i < n; i = (i | i + 1))
			t[i] += delta;
	}

	fenvik(vector <int> a) {
		n = a.size();
		t.assign(n, 0);
		for (int i = 0; i < n; i++)
			set_val(i, a[i]);
	}
};

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	fenvik help(10);
	while (true) {
		int type;
		cin >> type;
		if (type == 0)
			break;
		if (type == 1) {
			int l, r;
			cin >> l >> r;	
			cout << help.sum(r) - help.sum(l - 1) << endl;
		}
		if (type == 2) {
			int pos, val;
			cin >> pos >> val;
			help.set_val(pos, val);
		}
	}
	return 0; 
}