#include <bits/stdc++.h>

using namespace std;
#define int long long
#define double long double
#define all(a) a.begin(), a.end()

template <typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (y > x) x = y;}
template <typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}

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
			chkmax(ans, tree[r]);
		return ans;
	}

	void upd(int pos, int val) {
		for (; pos < n; pos = (pos | (pos + 1)))
			chkmax(tree[pos], val);
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

struct event{
	int l, r;
	event() {
		l = 1e9, r = -1e9;
	}
};

const int MAXN = 1e5 + 10;

event have[MAXN];
int dp[MAXN];

int ans;
int cnt;

void run() {
	set <int> num;
	for (auto i : a)
		num.insert(i);
	cnt = 0;
	map <int, int> coord;
	for (auto i : num)
		coord[i] = cnt++;
	
	for (int i = 0; i < n; i++) {
		a[i] = coord[a[i]];
	}

	for (int i = 0; i < cnt; i++) {
		have[i] = event(); 
	}

	for (int i = 0; i < n; i++) {
		chkmin(have[a[i]].l, i);
		chkmax(have[a[i]].r, i);
	}

	vector<int> help;
	for (int i = 0; i < cnt; i++) {
		help.push_back(i);
	}

	sort(help.begin(), help.end(), [&] (int i, int j) {return have[i].r < have[j].r;});
	fenvik fdp(n);

	ans = 1;
	for (int i = 0; i < cnt; i++) {
		int x = help[i];
		dp[x] = 1;
		chkmax(dp[x], fdp.get(have[x].l) + 1);
		fdp.upd(have[x].r, dp[x]);
		chkmax(ans, dp[x]);
	}
}

void write() {
	cout << cnt - ans << endl;
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