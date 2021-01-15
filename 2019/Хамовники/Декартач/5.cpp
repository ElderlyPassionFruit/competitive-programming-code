#include <bits/stdc++.h>

using namespace std;
#define int long long
const int INF = 1e18;
struct node
{
	int val, prior, sz, min, mast;
	node * l, * r;
	node (int new_val)
	{
		val = new_val;
		min = new_val;
		sz = 1;
		prior = (rand() << 16) | rand();
		l = nullptr;
		r = nullptr;
	}
};

int sz(node * tree)
{
	if (tree == nullptr)
		return 0;
	return tree->sz;
}

int min(node * tree)
{
	if (tree == nullptr)
		return INF;
	return tree->min;
}

void upd(node * tree)
{
	if (tree == nullptr)
		return;
	tree->sz = 1 + sz(tree->l) + sz(tree->r);
	tree->min = min(tree->val, min(min(tree->l), min(tree->r)));
}

node * merge(node * tree_l, node * tree_r)
{
	if (tree_l == nullptr)
		return tree_r;
	if (tree_r == nullptr)
		return tree_l;
	if (tree_l->prior < tree_r->prior)
	{
		tree_l->r = merge(tree_l->r, tree_r);
		upd(tree_l);
		return tree_l;
	}
	else
	{
		tree_r->l = merge(tree_l, tree_r->l);
		upd(tree_r);
		return tree_r;
	}
}

pair <node *, node *> split(node * tree, int size)
{
	if (tree == nullptr)
		return {nullptr, nullptr};
	if (sz(tree->l) >= size)
	{
		auto p = split(tree->l, size);
		tree->l = p.second;
		upd(tree);
		return {p.first, tree};
	}
	else
	{
		auto p = split(tree->r, size - sz(tree->l) - 1);
		tree->r = p.first;
		upd(tree);
		return {tree, p.second};
	}
}

node * insert(node * tree, node * x, int pos)
{
	if (tree == nullptr)
		return x;
	if (x->prior < tree->prior)
	{
		auto p = split(tree, pos);
		x->l = p.first;
		x->r = p.second;
		upd(x);
		return x;
	}
	else
	{
		if (sz(tree->l) >= pos)
		{
			tree->l = insert(tree->l, x, pos);
		}
		else
		{
			tree->r = insert(tree->r, x, pos - sz(tree->l) - 1);
		}
		upd(tree);
		return tree;
	}
}

int get_min(node * tree, int l, int r)
{
	auto i = split(tree, r);
	auto j = split(i.first, l - 1);
	int ans = min(j.second);
	i.first = merge(j.first, j.second);
	tree = merge(i.first, i.second);
	return ans;
}

void write(node * tree)
{
	if (tree == nullptr)
		return;
	write(tree->l);
	cout << tree->val << " ";
	write(tree->r);
}


signed main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	node * tree = nullptr;
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < n; i++)
	{
		int x;
		cin >> x;
		tree = insert(tree, new node(x), i);
	}
	write(tree);
	cout << endl;
	for (int i = 0; i < m; i++)
	{
		int l, r;
		cin >> l >> r;
		cout << get_min(tree, l, r) << endl;
	}
	return 0;
}













