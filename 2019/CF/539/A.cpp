#include <bits/stdc++.h>

using namespace std;

#define int long long

struct node{
	int key, prior;
	node * l, * r;
	node (int new_key)
	{
		l = nullptr;
		r = nullptr;
		key = new_key;
		prior = (rand() << 16) | rand();
	}
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
		return tree_l;
	}
	else
	{
		tree_r->l = merge(tree_l, tree_r->l);
		return tree_r;
	}
}

pair <node*, node*> split(node * tree, int key)
{
	if (tree == nullptr)
		return {nullptr, nullptr};
	if (tree->key <= key)
	{
		auto p = split(tree->r, key);
		tree->r = p.first;
		return {tree, p.second};
	}
	else
	{
		auto p = split(tree->l, key);
		tree->l = p.second;
		return {p.first, tree};
	}
}

node * insert(node * tree, node * x)
{
	if (tree == nullptr)
		return x;
	if (x->prior < tree->prior)
	{
		auto p = split(tree, x->key);
		x->l = p.first;
		x->r = p.second;
		return x;
	}
	else
	{
		if (x->key < tree->key)
		{
			tree->l = insert(tree->l, x);
		}
		else
		{
			tree->r = insert(tree->r, x);
		}
		return tree;
	}
}


node * erase(node * tree, int key)
{
	if (tree == nullptr)
		return nullptr;
	if (tree->key == key)
		return merge(tree->l, tree->r);
	if (tree->key > key)
	{
		tree->l = erase(tree->l, key);
	}
	else
	{
		tree_>r = erase(tree->r, key);
	}
	return tree;
}

node * prev(node * tree, int key)
{
	
}

void read()
{
	
}

void run()
{
	
}

void write()
{
	
}

signed main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}