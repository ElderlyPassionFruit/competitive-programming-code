#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct get_min{
	vector<int> a;
	int n;

	get_min() {
		n = 0, a = {};
	}

	get_min(int sz) {
		n = sz;
		a.resize(n);
	}


	void upd(int pos, int val) {
		for (; pos < n; pos = (pos | (pos + 1)))
			chkmax(a[pos], val); 
	}

	int get(int r) {
		int x = 1e9;
		for (; r >= 0; r = (r & (r + 1)) - 1)
			chkmin(x, a[r]);
		return x;
	}

	get_min(vector<int> x) {
		n = x.size();
		a.assign(n, 0);
		for (int i = 0; i < n; i++)
			upd(i, x[i]);
	}

	void upd(int pos) {
		upd(pos, 1e9);
	}

};

void solve() {
	int n;
	vector<pair <int, int> > a, b;
	vector<int> ax, bx;
	cin >> n;
	a.clear();
	b.clear();
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		ax.push_back(x);
		a.push_back({x, i});
	}
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		bx.push_back(x);
		b.push_back({x, i});
	}

	sort(a.begin(), a.end());
	sort(b.begin(), b.end());
	map <int, int> pos;
	for (int i = 0; i < n; i++) {
		if (a[i].first != b[i].first) {
			cout << "NO\n";
			return;
		}
		pos[b[i].second] = a[i].second;
	}

	//cout << "pos = " << endl;
	//for (auto i : pos) {
//		cout << i.first << " " << i.second << endl;
//	}

	get_min help(ax);
	
	for (auto i : pos) {
		if (help.get(i.second) < bx[i.first]) {
			cout << "NO\n";
			return;
		}
		help.upd(i.second);
	}
	cout << "YES\n";
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t--) {
		solve();
	}	
	return 0;
}
/*

1
3
1 2 3
3 2 1
*/