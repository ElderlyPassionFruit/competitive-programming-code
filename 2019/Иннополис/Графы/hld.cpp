#include <bits/stdc++.h>
 
using namespace std;
 
#define int long long
 
struct segment_tree{
    vector <int> tree;
    int n;
    segment_tree()
    {
 
    }
    segment_tree(int new_n)
    {
        n = new_n;
        tree.assign(4 * n, 0);
    }
 
    /*void build(int v, int l, int r)
    {
        if (l == r - 1)
        {
            tree[v] = a[l];
            return;
        }
        int m = (l + r) / 2;
        build(v * 2, l, m);
        build(v * 2 + 1, m, r);
        tree[v] = max(tree[v * 2], tree[v * 2 + 1]);
    }*/
 
    void upd(int v, int tl, int tr, int l, int r, int val)
    {
        if (tl >= r || tr <= l)
            return;
        if (tl == l && tr == r)
        {
            tree[v] += val;
            return;
        }
        int tm = (tl + tr) / 2;
        upd(v * 2, tl, tm, l, r, val);
        upd(v * 2 + 1, tm, tr, l, r, val);
        tree[v] = max(tree[v * 2], tree[v * 2 + 1]);
    }
 
    int get_max(int v, int tl, int tr, int l, int r)
    {
        if (tl >= r || tr <= l)
            return -1e18;
        if (tl >= l && tr <= r)
            return tree[v];
        int m = (tl + tr) / 2;
        return max(get_max(v * 2, tl, m, l, r), get_max(v * 2 + 1, m, tr, l, r));   
    }
};
 
const int MAXN = 1e5 + 10, MAXLOG = 15;
vector <int> g[MAXN];
int n, q;
int tin[MAXN], tout[MAXN], dp[MAXN][MAXLOG], timer = 0, h[MAXN], pred[MAXN];
 
void dfs_lca(int v, int p, int len)
{
    tin[v] = timer++;
    h[v] = len++;
    pred[v] = p;
    dp[v][0] = p;
    for (int i = 1; i < MAXLOG; i++)
        dp[v][i] = dp[dp[v][i - 1]][i - 1];
    for (auto i : g[v])
    {
        if (i != p)
        {
            dfs_lca(i, v, len);
        }
    }
    tout[v] = timer++;
}
 
bool is_upper(int v, int u)
{
    return tin[v] <= tin[u] && tout[v] >= tout[u];
}
 
int lca(int v, int u)
{
    if (is_upper(v, u))
        return v;
    if (is_upper(u, v))
        return u;
 
    for (int i = MAXLOG - 1; i >= 0; i--)
    {
        if (!is_upper(dp[v][i], u))
            v = dp[v][i];
    }
    return dp[v][0];
}
 
int dist(int v, int u)
{
    return h[v] + h[u] - 2*h[lca(v, u)];
}
int arr[MAXN];
void read()
{
    cin >> n;
   /* for (int i = 0; i < n; i++)
    	cin >> arr[i];*/
    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
}
 
int sz[MAXN];
void dfs_sz(int v, int p)
{
    sz[v] = 1;
    pred[v] = p;
    for (auto i : g[v])
    {
        if (i != p)
        {
            dfs_sz(i, v);
            sz[v] += sz[i];
        }
    }
}
 
pair <int, int > ind[MAXN]; 
vector <vector <int> > path; 
 
void dfs_hld(int v, int p, int ind1, int ind2)
{
    ind[v] = {ind1, ind2};
    path[ind1].push_back(v);
 
    for (auto i : g[v])
    {
        if (i != p)
        {
            if (sz[i] > sz[v] / 2)
            {
                dfs_hld(i, v, ind1, ind2 + 1);
            }
            else
            {
                path.push_back({});
                dfs_hld(i, v, path.size() - 1, 0);
            }
        }
    }
}
 
segment_tree trees[MAXN];
int get_max(int v, int u)
{
    int l = lca(v, u);
    int cnt = dist(v, l) + 1;
    int c = v;
    int ans = -1e18;
    while (cnt)
    {
        int i = ind[c].first;
        int j = ind[c].second;
        int cur_cnt = min(cnt, j + 1);
        ans = max(ans, trees[i].get_max(1, 0, trees[i].n, j + 1 - cur_cnt, j + 1));
        c = pred[path[i][0]];
        cnt -= cur_cnt;
    }
 
    cnt = dist(u, l) + 1;
    c = u;
    while (cnt)
    {
        int i = ind[c].first;
        int j = ind[c].second;
        int cur_cnt = min(cnt, j + 1);
        ans = max(ans, trees[i].get_max(1, 0, trees[i].n, j + 1 - cur_cnt, j + 1));
        c = pred[path[i][0]];
        cnt -= cur_cnt;
    }
 
    return ans;
}
 
vector <int> ans;
void run()
{
    dfs_sz(0, -1);
    dfs_lca(0, 0, 0);
    path.push_back({});
    dfs_hld(0, 0, 0, 0);
     
    for (int i = 0; i < path.size(); i++)
    {
        trees[i] = segment_tree(path[i].size());
    }
 
 /*	for (int i = 0; i < n; i++) { int u, val; u = i; val = arr[i];
trees[ind[u].first].upd(1, 0, trees[ind[u].first].n, ind[u].second,
ind[u].second + 1, val); }*/
    cin >> q;

    for (int i = 0; i < q; i++)
    {
        char type;
        cin >> type;
        if (type == 'I')
        {
            int u, val;
            cin >> u >> val;
            u--;
            trees[ind[u].first].upd(1, 0, trees[ind[u].first].n, ind[u].second, ind[u].second + 1, val);
        }
        else
        {
            int a, b;
            cin >> a >> b;
            a--;
            b--;
            ans.push_back(get_max(a, b));
        }
    }
}
 
void write()
{
    for (auto i : ans)
    {
        cout << i << endl;
    }
}
 
signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    freopen("caves.in", "r", stdin);
    freopen("caves.out", "w", stdout);
    read();
    run();
    write();
    return 0;
}