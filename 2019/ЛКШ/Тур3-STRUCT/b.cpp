#include <bits/stdc++.h>

using namespace std;
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct fenvik{
	vector<vector<long long> > tree;
	long long n;

	fenvik() {
		n = 0;
		tree = {};
	}

	fenvik(long long sz) {
		n = sz;
		tree.assign(n, vector<long long> (n, 0));
	}

	long long get(long long r1, long long r2) {
		long long ans = 0;
		for (long long i = r1; i >= 0; i = (i & (i + 1)) - 1)
			for (long long j = r2; j >= 0; j = (j & (j + 1)) - 1)
				ans += tree[i][j];
		return ans;
	}

	long long get(long long l1, long long r1, long long l2, long long r2) {
		long long ans = 0;
		ans += get(r1, r2);
		ans -= get(l1 - 1, r2);	
		ans -= get(r1, l2 - 1);
		ans += get(l1 - 1, l2 - 1);
		return ans;
	}

	void upd(long long r1, long long r2, long long val) {
		for (long long i = r1; i < n; i = (i | (i + 1)))
			for (long long j = r2; j < n; j = (j | (j + 1)))
				tree[i][j] += val;
	}
};

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	long long x, s;
	cin >> x;
	cin >> s;
	fenvik tree(s);
	while (cin >> x) {
		if (x == 3) break;
		if (x == 1) {
			long long r1, r2, a;
			cin >> r1 >> r2 >> a;
			tree.upd(r1, r2, a);
		}
		if (x == 2) {
			long long l1, r1, l2, r2;
			cin >> l1 >> l2 >> r1 >> r2;
			cout << tree.get(l1, r1, l2, r2) << "\n";
		}
	}	
	return 0;
}

/*

0 4
1 1 2 3
2 0 0 2 2
1 1 1 2
1 1 2 -1
2 1 1 2 3
3

*/