#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int INF = 1e9 + 10;

struct segment_tree{
	vector<int> tree;
	int n;
	segment_tree() {

	}

	segment_tree(int sz) {
		n = sz;
		tree.assign(sz, INF);
	}

	void upd(int pos, int val) {
		tree[pos] = val;
	} 

	int get(int l, int r) {
		int ans = INF;
		for (int i = l; i <= r; i++)
			ans = min(ans, tree[i]);
		return ans;
	}
};

string s;
int n, k;

const int MAXN = 2e5 + 10, MAXA = 26;

int pref[MAXN][MAXA];
segment_tree tree;
	

void build() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < MAXA; j++) {
			if (i > 0)
				pref[i][j] = pref[i - 1][j];
		}
		pref[i][s[i] - 'a']++;
	}
	tree = segment_tree(n);
}

int get(int l, int r) {
	int ans = 0;
	for (int i = 0; i < MAXA; i++) {
		if (pref[r][i] - (l > 0 ? pref[l - 1][i]))
			ans++;
	} 
	return ans;
}

int get_l(int pos) {
	if (get(0, pos) < k) return -1;

}

int get_r(int pos) {
	if (get(0, pos) < k) return -1;
}

void solve(int pos) {
	
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	return 0;
	cin >> k;
	cin >> s;
	n = s.size();
	build();

	for (int i = 0; i < n; i++) {
		solve(i);
	}
}

















