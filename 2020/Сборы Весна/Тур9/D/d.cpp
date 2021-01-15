#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct node{
	int l, r;
	int flag;
	int sz;
	node() {
		l = -1, r = -1, flag = 0;
		sz = 0;
	}
};

const int MAXMEM = 2e7;
node tree[MAXMEM];
int topQ = 0;
const int MAXLOG = 21;

void push(int root, int bit) {
	bit--;
	if ((tree[root].flag >> bit) & 1) {
		swap(tree[root].l, tree[root].r);
	}
	int l = tree[root].l;
	int r = tree[root].r;
	if (l != -1) {
		tree[l].flag ^= tree[root].flag;
	} 
	if (r != -1) {
		tree[r].flag ^= tree[root].flag;
	}
	tree[root].flag = 0;
}

struct bin_trie{
	int sz;
	int root;
	vector<int> x;
	bin_trie() {
		sz = 0;
		root = -1;
		x = {};
	}

	bool check(int a) {
		if (root == -1) return false;
		int now = root;
		for (int i = MAXLOG; i > 0; i--) {
			push(now, i);
			int nxt = (a >> (i - 1)) & 1;
			if (nxt == 0) {
				if (tree[now].l == -1) return false;
				now = tree[now].l;
			} else {
				if (tree[now].r == -1) return false;
				now = tree[now].r;
			}
		}
		return true;
	}

	void add(int a) {
		if (root == -1) {
			root = topQ++;
		}
		if (check(a)) return;
		sz++;
		int now = root;
		tree[now].sz++;
		for (int i = MAXLOG; i > 0; i--) {
			push(now, i);
			int nxt = (a >> (i - 1)) & 1;
			if (nxt == 0) {
				if (tree[now].l == -1) tree[now].l = topQ++;
				now = tree[now].l;
			} else {
				if (tree[now].r == -1) tree[now].r = topQ++;
				now = tree[now].r;
			}
			tree[now].sz++;
		}		 
	}	

	int get_mex() {
		if (root == -1) return 0;
		int now = root;
		int ans = 0;
		for (int i = MAXLOG; i > 0; i--) {
			if (now == -1) break;
			push(now, i);
			int l = tree[now].l;
			int r = tree[now].r;
			if (l != -1 && tree[l].sz == (1 << (i - 1))) {
				ans += (1 << (i - 1));
				if (r != -1 && tree[r].sz == (1 << (i - 1))) {
					ans += (1 << (i - 1));
					break;
				}
				now = r;
			} else {
				now = l;
			}
		}
		return ans;
	}

	void Xor(int a) {
		if (root == -1) return;
		tree[root].flag ^= a;
	}
};

struct event{
	int root, val, level;
	event() {}
	event(int _root, int _val, int _level) {
		root = _root, val = _val, level = _level;
	}
};	

void merge(bin_trie & a, bin_trie & b) {
	if (a.sz < b.sz) swap(a, b);
	int now = b.root;
	if (now == -1) return;
	queue<event> q;
	q.push({now, 0, MAXLOG});
	while (!q.empty()) {
		event x = q.front();
		q.pop();
		if (x.level == 0) {
			a.add(x.val);
			continue;
		}
		push(x.root, x.level);
		if (tree[x.root].l != -1) {
			q.push({tree[x.root].l, x.val, x.level - 1});
		}
		if (tree[x.root].r != -1) {
			q.push({tree[x.root].r, x.val + (1 << (x.level - 1)), x.level - 1});
		}
	}
}

const int MAXN = 5e5 + 10;
vector<int> g[MAXN];
int n;

void read() {
	cin >> n;
	for (int i = 1; i < n; i++) {
		int p;
		cin >> p;
		p--;
		g[p].push_back(i);
	}
}

int grundy[MAXN];
bin_trie have[MAXN];

int ans;

void solve(int v) {
	for (auto i : g[v]) {
		solve(i);
	}
	have[v] = bin_trie();
	int Xor = 0;
	for (auto i : g[v]) {
		Xor ^= grundy[i];
	}	
	have[v].add(Xor);
	for (auto i : g[v]) {
		have[i].Xor(Xor ^ grundy[i]);
		merge(have[v], have[i]);
	}
	grundy[v] = have[v].get_mex();
}

void run() {
	ans = 0;
	solve(0);
	for (int i = 0; i < n; i++) {
		int Xor = 0;
		for (auto v : g[i]) {
			Xor ^= grundy[v];
		}
		ans += Xor > 0;
	}
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