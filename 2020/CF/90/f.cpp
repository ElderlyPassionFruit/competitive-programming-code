#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

#define int ll

struct segmentTree{
	vector<int> tree;
	int n;
	segmentTree() {}
	segmentTree(vector<int> & a) {
		n = a.size();
		tree = a;
		for (int i = 0; i < n; i++) {
			if (i % 2 == 0) {
				tree[i] = 0;
			}
		}
	}
	int get(int l, int r) {
		int ans = 1e18;
		for (int i = l; i <= r; i++) {
			chkmin(ans, tree[i]);
		}
		return ans;
	}
};

void solve() {
	int n;
	cin >> n;
	vector<int> a(n);
	for (auto &i : a) {
		cin >> i;
	}	
	vector<int> b(n);
	for (auto &i : b) {
		cin >> i;
	}
	//swap(a, b);
	vector<int> have;
	for (int i = 0; i < n; i++) {
		have.push_back(-a[i]);
		have.push_back(b[i]);
	}
	for (int i = 0; i < n; i++) {
		have.push_back(-a[i]);
		have.push_back(b[i]);
	}
	cout << "have = " << endl;
	for (auto i : have) cout << i << " ";
	cout << endl;
	for (int i = 1; i < (int)have.size(); i++) {
		have[i] += have[i - 1];	
		if (i % 2 == 0) {
			chkmin(have[i], 0);
		}
	}
	cout << "have = " << endl;
	for (auto i : have) cout << i << " ";
	cout << endl;
	segmentTree tree(have);
	for (int i = 0; i + 2 * n - 1 < (int)have.size(); i += 2) {
		if (tree.get(i, i + 2 * n - 1) >= 0) {
			cout << "YES\n";
		//	cout << "i = " << i << endl;
			return;
		}
	}
	cout << "NO\n";

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