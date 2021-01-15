#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct fenvik{
	vector<int> tree;
	int n;

	fenvik() {
		n = 0;
		tree = {};
	}

	fenvik(int sz) {
		n = sz;
		tree.assign(n, 0);
	}

	int get(int r) {
		int ans = 0;
		for (; r >= 0; r = (r & (r + 1)) - 1)
			ans += tree[r];
		return ans;
	}

	int get(int l, int r) {
		return get(r) - get(l - 1);
	}

	void upd(int pos) {
		for (; pos < n; pos = (pos | (pos + 1)))
			tree[pos]++;
		//tree[pos]++;
	}

	void wr() {
		cout << "tree = " << endl;
		for (int i = 0; i < n; i++)
			cout << tree[i] << " ";
		cout << endl;
	}

};

int n, k;

void read() {
	cin >> n >> k;
	k = min(k, n - k);
}

vector<int> ans;

void run() {
	int fans = 1;
	int pos = 0;
	fenvik help(2 * n);
	for (int i = 0; i < n; i++) {
		int fget = help.get(pos + 1, pos + k - 1) + 1;
		//cout << "i = " << i << " get = " << fget << endl;
		help.upd(pos);
		help.upd((pos + n) % (2 * n));
		help.upd(pos + k);
		help.upd((pos + k + n) % (2 * n));
		fans += fget;
		ans.push_back(fans);
		pos += k;
		pos %= n;
		//help.wr();
	}
}

void write() {
	for (auto i : ans)
		cout << i << " ";
	cout << endl;
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