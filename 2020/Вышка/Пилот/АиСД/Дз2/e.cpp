//#pragma GCC optimize("Ofast")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,tune=native")
//#pragma GCC optimize("unroll-loops") 
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>
#include <stdio.h>

using namespace std;
#define FAST ios_base::sync_with_stdio(false); \
    cin.tie(nullptr); \
    cout.tie(nullptr)

#define int long long

struct node {
    int val, prior, sz;
    node * l, *r;
    node(int v)
    {
        val = v;
        prior = (rand() << 16) | rand();
        l = nullptr;
        r = nullptr;
        sz = 1;
    }
};

int sz(node * tree)
{
    if (tree == nullptr)
        return 0;
    return tree->sz;
}

void upd(node * tree)
{
    if (tree == nullptr)
        return;
    tree->sz = sz(tree->l) + sz(tree->r) + 1;
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
        return { nullptr, nullptr };
    if (sz(tree->l) >= size)
    {
        auto p = split(tree->l, size);
        tree->l = p.second;
        upd(tree);
        return { p.first, tree };
    }
    else
    {
        auto p = split(tree->r, size - sz(tree->l) - 1);
        tree->r = p.first;
        upd(tree);
        return { tree, p.second };
    }
}

node * insert(node * tree, node * v, int k)
{
    if (tree == nullptr)
        return v;
    if (v->prior < tree->prior)
    {
        auto p = split(tree, k);
        v->l = p.first;
        v->r = p.second;
        upd(v);
        return v;
    }
    if (sz(tree->l) >= k)
        tree->l = insert(tree->l, v, k);
    else
        tree->r = insert(tree->r, v, k - sz(tree->l) - 1);
    upd(tree);
    return tree;
}

node * erase(node * tree, int k)
{
    if (tree == nullptr)
        return nullptr;
    if (sz(tree->l) == k)
        return merge(tree->l, tree->r);
    if (sz(tree->l) > k)
        tree->l = erase(tree->l, k);
    else
        tree->r = erase(tree->r, k - sz(tree->l) - 1);
    upd(tree);
    return tree;
}
int n, m;
node * tree;
void read()
{
    cin >> n >> m;
    tree = nullptr;
    for (int i = 1; i <= n; i++)
    {
        tree = insert(tree, new node(i), i - 1);
    }
}
vector <int> ans;


void fwrite(node * tree)
{
    if (tree == nullptr)
        return;
    fwrite(tree->l);
    cout << tree->val << " ";
    fwrite(tree->r);
}

void run()
{
    for (int i = 0; i < m; i++)
    {
        int l, r;
        cin >> l >> r;
       // fwrite(tree);
       // cout << endl;
        auto p = split(tree, r);
        auto j = split(p.first, l - 1);
        p.first = merge(j.second, j.first);
        tree = merge(p.first, p.second);
    }
}


void write()
{
    fwrite(tree);
}

signed main()
{
    freopen("movetofront.in", "r", stdin);
    freopen("movetofront.out", "w", stdout);
    FAST;
    read();
    run();
    write();
    return 0;
}