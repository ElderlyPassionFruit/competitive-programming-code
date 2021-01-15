#include <bits/stdc++.h>

using namespace std;
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

mt19937 rnd(time(0));

struct node {
	int val, sz, prior;
	node * L, * R;
	node() {
		sz = 0;
		L = nullptr;
		R = nullptr;
	}

	node(int _val) {
		val = _val;
		sz = 1;
		prior = rnd();
		L = nullptr;
		R = nullptr;
	}
};

int sz(node * tree) {
	if (tree == nullptr) return 0;
	return tree->sz;
}

void upd(node * tree) {
	if (tree == nullptr) return;
	tree->sz = 1 + sz(tree->L) + sz(tree-R);
}

node * merge(node * L, node * R) {
	if (L == nullptr) return R;
	if (R == nullptr) return L;
	if (L->prior < R.prior) {
		L->R = merge(L->R, R);
		upd(L);
		return L;
	} else {
		R->L = merge(L, R->L);
		upd(R);
		return R;
	}
}

pair<node *, node *> split (node * tree, int size) {
	if (tree == nullptr) return {nullptr, nullptr};
	if (sz(tree->L) >= size) {
		auto p = split(tree->L, size);
		tree->L = p.second;
		upd(tree);
		return {p.first, tree};
	} else {
		auto p = split(tree->R, size - sz(tree->L) - 1);
		tree->R = p.first;
		upd(tree);
		return {tree, p.second};
	}
} 

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	return 0;
}




