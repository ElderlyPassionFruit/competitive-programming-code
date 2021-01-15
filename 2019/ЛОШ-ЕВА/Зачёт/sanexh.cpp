#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
vector<pair<int,ll>> g[(int)1e6];
vector<pair<int,ll>> rev[(int)1e6];
set<ll> s[(int)1e6];
#define  x first
#define y second
#pragma GCC optimize("O3")
int mx = 0;
void gen(int v, ll cur)
{
    s[v].insert(cur);
    for(auto e : g[v])
    {
        if(cur + e.y <= mx && s[e.x].find(cur + e.y) == s[e.x].end())
            gen(e.x, cur + e.y);
    }
}
void solve()
{
    int n, m, q, p;
    cin >> n >> m >> q >> p;
    mx = 5000 * p / (p - 1);
    for(int i = 1; i<=n; i++)
    {
        s[i].clear();
        rev[i].clear();
        g[i].clear();
    }
    for(int i = 1; i<=m; i++)
    {
        ll x, y, d;
        cin >> x >> y >> d;
        g[x].push_back({y,d});
        rev[y].push_back({x,d});
    }
    gen(1,0);
    for(int i = 1; i<=q;i++)
    {
        ll v, r;
        cin >>v >>  r;
        auto it = s[v].lower_bound(r);
        if(it == s[v].end())
        {

            cout << 0;
        }
        else
        {
            if(r * p / (p - 1) < *it)
                cout<<0;
            else
                cout<<1;
        }
    }
    cout<<'\n';
}
int main()
{
    //freopen("input.txt","r",stdin);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while(t--)
        solve();
}