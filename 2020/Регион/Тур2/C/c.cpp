#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

#define int ll

struct node{
	map<char, int> go;
	ll sum = 0;
	ll cnt = 0;
	ll cnt_term = 0;
	ll sum_term = 0;
	node() {

	}
};

const int MAXSZ = 1e6 + 10;
node tree[MAXSZ];
int sz = 0;

void add_string(string & s) {
	int now = 0;
	tree[now].sum += s.size();
	tree[now].cnt++;
	for (int i = 0; i < s.size(); i++) {
		if (!tree[now].go.count(s[i])) tree[now].go[s[i]] = ++sz;
		now = tree[now].go[s[i]];
		tree[now].sum += s.size();
		tree[now].cnt++;
	}
	tree[now].cnt_term++;
	tree[now].sum_term += s.size();
}

void read() {
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		add_string(s);
	}
}

ll ans;

void dfs(int now, ll len) {	
	ll add = (tree[now].sum - tree[now].sum_term - len * (tree[now].cnt - tree[now].cnt_term)) * tree[now].cnt_term;
	ans += add;
	for (auto i : tree[now].go) {
		dfs(i.second, len + 1);
		ll my_sum = tree[now].sum;
		ll my_cnt = tree[now].cnt;
		ll go_sum = tree[i.second].sum;
		ll go_cnt = tree[i.second].cnt;
		ll add = ((my_sum - go_sum) - len * (my_cnt - go_cnt)) * go_cnt;
		ll del = (go_sum - go_cnt * len) * (my_cnt - go_cnt);
		ans += add + del;
	}
}

void solve() {
	ans = 0;
	dfs(0, 0);
}

void run() {		
	solve();
}

void write() {
	cout << ans << endl;
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