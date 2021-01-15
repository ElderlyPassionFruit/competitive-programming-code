#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct fenvik{
	vector<vector<vector<int> > > tree;
	int n;
	fenvik() {
		n = 0;
		tree = {};
	}

	fenvik(int sz) {
		n = sz;
		tree.assign(n, vector<vector<int> > (n, vector<int> (n, 0)));
	}

	int get(int x, int y, int z) {
		int ans = 0;
		for (int i = x; i >= 0; i = (i & (i + 1)) - 1)
			for (int j = y; j >= 0; j = (j & (j + 1)) - 1)
				for (int k = z; k >= 0; k = (k & (k + 1)) - 1)
					ans += tree[i][j][k];
		return ans;
	}

	int get(int x1, int y1, int z1, int x2, int y2, int z2) {
		int ans = 0;
		ans += get(x2, y2, z2);
		ans -= get(x2, y1 - 1, z2);
		ans -= get(x1 - 1, y2, z2);
		ans -= get(x2, y2, z1 - 1);
		ans += get(x1 - 1, y1 - 1, z2);
		ans += get(x1 - 1, y2, z1 - 1);
		ans += get(x2, y1 - 1, z1 - 1);
		ans -= get(x1 - 1, y1 - 1, z1 - 1);
		return ans;
	}

	void upd(int x, int y, int z, int val) {
		for (int i = x; i < n; i = (i | (i + 1)))
			for (int j = y; j < n; j = (j | (j + 1)))
				for (int k = z; k < n; k = (k | (k + 1)))
					tree[i][j][k] += val;
	}
};

int n;
fenvik tree;

void read() {
	cin >> n;
	tree = fenvik(n);
}

vector<int> ans;

void run() {
	while (true) {
		int type;
		cin >> type;
		if (type == 3)
			break;
		else if (type == 1) {
			int x, y, z, k;
			cin >> x >> y >> z >> k;
			tree.upd(x, y, z, k);
		}
		else if (type == 2) {
			int x1, y1, z1, x2, y2, z2;
			cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
			ans.push_back(tree.get(x1, y1, z1, x2, y2, z2));
		}
	}
}

void write() {
	for (auto i : ans)
		cout << i << "\n";
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