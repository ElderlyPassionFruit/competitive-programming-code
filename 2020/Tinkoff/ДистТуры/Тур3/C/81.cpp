#include <bits/stdc++.h>

using namespace std;
//#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

mt19937 rnd(time(0));

struct node{
	int prior, val, col;
	node *l, *r;
	node() {}
	node(int new_val, int new_col) {
		val = new_val;
		col = new_col;
		l = nullptr;
		r = nullptr;
		prior = rnd();
	}
};

node * merge(node * tl, node * tr) {
	if (tl == nullptr)
		return tr;
	if (tr == nullptr)
		return tl;
	if (tl->prior < tr->prior) {
		tl->r = merge(tl->r, tr);
		return tl;
	}
	else {
		tr->l = merge(tl, tr->l);
		return tr;
	}
}

pair <node *, node *> split(node * tree, int pos) {
	if (tree == nullptr)
		return {nullptr, nullptr};
	if (tree->val > pos) {
		auto p = split(tree->l, pos);
		tree->l = p.second;
		return {p.first, tree};
	}
	else {
		auto p = split(tree->r, pos);
		tree->r = p.first;
		return {tree, p.second};
	}
}

node * getR(node * tree) {
	if (tree == nullptr)
		return nullptr;
	if (tree->r != nullptr)
		return getR(tree->r);
	else
		return tree;
}

node * getL(node * tree) {
	if (tree == nullptr)
		return nullptr;
	if (tree->l != nullptr)
		return getL(tree->l);
	else
		return tree;
}


int n, m, q;

void read() {
	cin >> n >> m >> q;
}

const int MAXN = 1e5 + 10;

map<int, int> Next[MAXN];

node * tree[2];

void build() {
	for (int i = 0; i < n; i++) {
		tree[i] = new node(0, i);
	}
}

void upd(int a, int b, int x) {
	//for (; x < m; x++)
	if (!Next[a].count(x))
		Next[a][x] = a;
	if (!Next[b].count(x))
		Next[b][x] = b;
	swap(Next[a][x], Next[b][x]);
} 

int get(int pos, int x) {
	for (int i = 0; i < x; i++){
		if (Next[pos].count(i))
			pos = Next[pos][i];
	}
	return pos;
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

void upd2(int a, int b, int x) {
	auto v = correct_split(tree[a], x);
	auto u = correct_split(tree[b], x);
	tree[a] = merge(v.first, u.second);
	tree[b] = merge(u.first, v.second);
} 

int get2(int pos, int x) {
	auto p = split(tree[pos], x);
	int ans = getR(p.first)->col;
	tree[pos] = merge(p.first, p.second);
	return ans;
}


vector<int> ans;

void run() {
	if (n == 2)
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
			if (n != 2)
				upd(a, b, x);
			else
				upd2(a, b, x);
		}
		if (type == 1) {
			int pos, x;
			cin >> pos >> x;
			pos--;
			if (n != 2)
				ans.push_back(get(pos, x));
			else
				ans.push_back(get2(pos, x));
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