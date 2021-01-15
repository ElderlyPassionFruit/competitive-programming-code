#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct segment_tree{
	vector<int> tree;
	int n;
	segment_tree(int sz) {
		n = sz;
		tree.assign(n, 0);
	}

	void upd(int s, int f, int x, int y) {
		for (int i = s; i <= f; i++) {
			tree[i] += x;
			x += y;
		}
	}

	int get(int pos) {
		return tree[pos];
	}
};

int n;
vector<int> a;

void read() {
	cin >> n;
	a.resize(n);
	for (auto &i : a)
		cin >> i;
}

segment_tree tree;

void upd(int pos) {

}

int get(int pos) {
	return tree.get(pos);
}

pair <int, int> ans;

void run() {
	tree = segment_tree(n);
	ans = {1e18, 0};
	for (int i = 0; i < n; i++)
		upd(i);
	for (int i = 0; i < n; i++) {
		chkmin(ans, make_pair(get(i), i));
	}
}

void write() {
	cout << ans.first << " " << ans.second << endl;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}