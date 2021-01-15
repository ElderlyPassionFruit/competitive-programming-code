#include <bits/stdc++.h>

using namespace std;
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}


int n, m, q;

void read() {
	cin >> n >> m >> q;
}

const int MAXN = 2;

node * tree[MAXN];

void build() {
	for (int i = 0; i < n; i++) {
		tree[i] = new node(0, i);
	}
}

pair <node *, node*> correct_split(node * tree, int x) {
	auto p = split(tree, x);
	auto R = getR(p.first);
	auto L = getL(p.second);
	if (L == nullptr || L->val != x + 1) {
		p.second = merge(new node(x + 1, R->col), p.second);
	}
	return p;
}

void upd(int a, int b, int x) {
	auto v = correct_split(tree[a], x);
	auto u = correct_split(tree[b], x);
	tree[a] = merge(v.first, u.second);
	tree[b] = merge(u.first, v.second);
} 

int get(int pos, int x) {
	auto p = split(tree[pos], x);
	int ans = getR(p.first)->col;
	tree[pos] = merge(p.first, p.second);
	return ans;
}

vector<int> ans;

void run() {
	build();
	for (int i = 0; i < q; i++) {
		int type;
		cin >> type;
		if (type == 0) {
			int a, b, x;
			cin >> a >> b >> x;
			a--;
			b--;
			x--;
			upd(a, b, x);
		}
		if (type == 1) {
			int pos, x;
			cin >> pos >> x;
			pos--;
			ans.push_back(get(pos, x));
		}
	}
}

void write() {
	for (auto i : ans)
		cout << i + 1 << "\n";
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