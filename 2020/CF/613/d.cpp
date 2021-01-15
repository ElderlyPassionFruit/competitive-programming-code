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
	int l = -1, r = -1;
	node() {}
};

const int MAXLEN = 30;
const int MAXN = 3e6 + 10;
int sz = 0;
node tree[MAXN];

void add(int x) {
	int now = 0;
	for (int i = MAXLEN; i >= 0; i--) {
		if ((x >> i) & 1) {
			//cout << now << " " << x << " " << i << endl;
			if (tree[now].r == -1) 
				tree[now].r = ++sz;
			now = tree[now].r;
		}
		else {
			if (tree[now].l == -1) 
				tree[now].l = ++sz;
			now = tree[now].l;
		}
	}
}

int n;

void read() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		add(x);
	}
	//cout << (1 >> MAXLEN) << endl;
}

int dfs(int now, int len = MAXLEN) {
	//cout << "now = " << now << endl;
	if (now == -1) return 0;

	int l = tree[now].l;
	int r = tree[now].r;
	//cout << "l = " << l << " r = " << r << endl;
	if (len == 0) return 0;
	if (l != -1 && r != -1) {
		return min(dfs(l, len - 1), dfs(r, len - 1)) + (1 << (len));
	}
	if (l != -1) {
		return dfs(l, len - 1);
	}
	if (r != -1) {
		return dfs(r, len - 1);
	}
	assert(false);
}



int ans;

void run() {
	ans = dfs(0);
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