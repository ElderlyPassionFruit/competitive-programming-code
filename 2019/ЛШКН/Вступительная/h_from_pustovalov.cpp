#define _CRT_SECURE_NO_WARNINGS
 
#include <set>
#include <map>
#include <deque>
#include <cmath>
#include <queue>
#include <cassert>
#include <random>
#include <bitset>
#include <time.h>
#include <ctime>
#include <string>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
//++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++
#define endl '\n'
#define mp make_pair
#define pbc push_back
#define pob pop_back()
#define empb emplace_back
#define queuel queue<long long>
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define matrix vector<vector<ll>>
#define pin(p) cin >> p.first >> p.second;
#define rev(v) reverse(v.begin(),v.end());
#define mx(v) max_element(v.begin(), v.end());
#define mn(v) min_element(v.begin(), v.end());
#define sout(s, c) for(auto i : s) cout << i << c;
#define pout(p) cout << p.first << " " << p.second;
#define er(v, l, r) erase(v.begin() + l, v.begin() + r);
#define vin(v) for(ll i = 0; i < v.size(); ++i) cin >> v[i];
#define vout(v, c) for(int i = 0; i < v.size(); ++i) cout << v[i] << c;
#define pushi(v, a) for(int i = 0; i < a.size(); ++i) v.push_back(a[i]);
#define sin(s, n) for(int i = 0; i < n; ++i){int a; cin >> a; s.insert(a);}
#define fastio() ios_base::sync_with_stdio(0);cout.tie(0);cin.tie(0);srand(time(NULL))
#define sp system("pause")
//++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++
using namespace std;
//++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
//++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++
const int MAXN = 1e5 + 1;
#define int ll
const int inf = 1e18;
vector<vector<pair<int, int>>> g(MAXN);
ll sodd[MAXN];
ll seven[MAXN];
int tin[MAXN];
int d[MAXN];
int tout[MAXN];
int up[MAXN][18];
int mnr[MAXN][18];
int am[MAXN];
int tl = 0;
void dfs(int v, int p, int r)
{
    tin[v] = tl++;
    sodd[v] = sodd[p] + (r % 2) * r;
    d[v] = d[p] + (v != p);
    am[v] = am[p] + (r % 2 == 0 && r);
    seven[v] = seven[p] + (r %2  == 0 ? 1 : 0) * r;
    up[v][0] = p;
    mnr[v][0] = (r == 0 || r % 2 ? inf : r);
    for (int i = 1; i < 18; ++i)
    {
        up[v][i] = up[up[v][i - 1]][i - 1];
        mnr[v][i] = min(mnr[v][i - 1], mnr[up[v][i - 1]][i - 1]);
    }
    for (auto i : g[v])
    {
        if (i.first != p)
        {
            dfs(i.first, v, i.second);
        }
    }
    tout[v] = tl++;
}
bool pp(int a, int  b)
{
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}
int lca(int a, int b)
{
    if (pp(a, b)) return a;
    if (pp(b, a)) return b;
    for (int i = 17; i >= 0; --i)
    {
        if (!pp(up[a][i], b))
        {
            a = up[a][i];
        }
    }
    return up[a][0];
}
ll osm(int a, int b, int c)
{
    return sodd[a] + sodd[b] - 2 * sodd[c];
}
ll esm(int a, int b, int c)
{
    return seven[a] + seven[b] - 2 * seven[c];
}
ll sm(int a, int b, int c)
{
    return esm(a, b, c) + osm(a, b, c);
}
int amm(int a, int b, int c)
{
    return am[a] + am[b] - 2 * am[c];
}
int minr(int a, int b, int c)
{
    int ans = inf;
    for (int i = 17; i >= 0; --i)
    {
        if (!pp(up[b][i], c))
        {
            ans = min(ans, mnr[b][i]);
            b = up[b][i];
        }
    }
    if (b != c) ans = min(ans, mnr[b][0]);
    for (int i = 17; i >= 0; --i)
    {
        if (!pp(up[a][i], c))
        {
            ans = min(ans, mnr[a][i]);
            a = up[a][i];
        }
    }
    if (a != c) ans = min(ans, mnr[a][0]);
    return ans;
}
int leng(int a, int  b, int c)
{
    return d[a] + d[b] - 2 * d[c];
}
signed main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    fastio();
    int n, q;
    cin >> n >> q;
    ll ans = 0;
    for (int i = 0; i < n - 1; ++i)
    {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].pbc({ b,c });
        g[b].pbc({ a,c });
        ans += c;
    }
    dfs(1, 1, 0);
    while (q--)
    {
        int a, b;
        cin >> a >> b;
        int x = lca(a, b);
        int kek = amm(a, b, x);
        ll len = sm(a, b, x);
        if (!kek)
        {
            cout << 1 << endl;
            continue;
        }
        if (kek == 1)
        {
            int zz = minr(a, b, x);
            if (zz < leng(a,b,x) - 1)
            {
                cout << 2 << endl;
            }
            else
            {
                cout << 1 << endl;
            }
            continue;
        }
        if (kek == 2)
        {
            int kekos = minr(a, b, x);
            if (kekos < leng(a,b,x) - 1)
            {
                cout << 2 << endl;
            }
            else
            {
                ll z = ans - esm(a,b,x);
                if (z % 2 == 0)
                {
                    cout << 2 << endl;
                }
                else
                {
                    cout << 1 << endl;
                }
            }
            continue;
        }
        else
        {
            cout << 2 << endl;
            continue;
        }
    }
 
    return 0;
    sp;
}