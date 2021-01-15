//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,abm,mmx,avx,avx2,popcnt,tune=native")
//#pragma GCC optimize("Ofast")
/*#pragma GCC optimize("section-anchors")
#pragma GCC optimize("profile-values,profile-reorder-functions,tracer")
#pragma GCC optimize("vpt")
#pragma GCC optimize("rename-registers")
#pragma GCC optimize("move-loop-invariants")
#pragma GCC optimize("unswitch-loops")
#pragma GCC optimize("function-sections")
#pragma GCC optimize("data-sections")
#pragma GCC optimize("branch-target-load-optimize")
#pragma GCC optimize("branch-target-load-optimize2")
#pragma GCC optimize("btr-bb-exclusive")*/
//#pragma GCC optimize("inline")
//#pragma comment(linker, "/STACK:16777216")
//#define _CRT_SECURE_NO_WARNINGS
#include <chrono>
#include <set>
#include <map>
#include <deque>
#include <string>
#include <cstdint>
#include <cmath>
#include <queue>
#include <cassert>
#include <random>
#include <bitset>
#include <iomanip>
#include <numeric>
#include <time.h>//////////////
#include <ctime>
#include <climits>
#include <string>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
//++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++
//#define endl '\n'
#define mp make_pair
#define pbc push_back
#define pob pop_back()
#define empb emplace_back
#define queuel queue<long long>
#define sqr(a) ((a) * (a))
#define lsqr(a) (ld(a) * a)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define pin(p) cin >> p.first >> p.second;
#define uniq(a) sort(all(a));(a).resize(unique(all(a)) - a.begin());
#define rev(v) reverse(v.begin(), v.end());
#define sout(s, c) for (auto i : s) cout << i << c;
#define pout(p) cout << p.first << " " << p.second;
#define er(v, l, r) erase(v.begin() + l, v.begin() + r);
#define vin(v) for (ll i = 0; i < v.size(); ++i) cin >> v[i];
#define vout(v, c) for (int i = 0; i < v.size(); ++i) cout << v[i] << c;
#define pushi(v, a) for (int i = 0; i < a.size(); ++i) v.push_back(a[i]);
#define fastio() ios_base::sync_with_stdio(0); cout.tie(0); cin.tie(0); srand(time(NULL))
#define dab(v) for(auto i:v)cout<<i<<' ';
#define sp system("pause")
#define left left228
#define calc calc228
#define next next228
#define type type1337
#define right right228
//++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++
using namespace std;
//++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
//++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++
const ld EPS = 1e-4;
const ld EPS2 = 1e-12;
const ld PI = acos(-1);
int mod = (int)998244353;
const int MOD7 = 1000000007;
const int MOD9 = 1000000009;
const int a228 = 18;
const ll INF = 1e18;
const int inf = 1e9;
mt19937 rnd(time(0));
const ll kekmod = 1791791791;
const ll bestmod = 1148822869;
struct node
{
    node* l;
    node*r;
    int val;
    node()
    {
        l = r = nullptr;
        val = -228;
    }
};
node *root;
void add(int x, int id)
{
    node *v = root;
    vector<node*>ps;
    for (int bt = 30; bt >= 0; --bt)
    {
        ps.pbc(v);
        if (x & (1 << bt))
        {
            if (v->r == nullptr) v->r = new node();
            v = v->r;
        }
        else
        {
            if (v->l == nullptr) v->l = new node();
            v = v->l;
        }

    }
    v->val = id;
    for (auto i : ps) i->val = id;
}
int solve(vector<ll> a)
{
    root = new node();
    vector<ll> pref(a.size());
    for (int i = 0; i < a.size(); ++i)
    {
        pref[i] = (i == 0 ? 0ll : pref[i - 1]) + a[i];
    }
    int n = a.size();
    ll ans = 0;
    for (int i = 2; i < n; ++i)
    {
        add(a[i - 2], i - 2);
        node * v = root;
        for (int bt = 30; bt >= 0; --bt)
        {

            if (a[i] & (1 << bt))
            {
                if (v->r == nullptr)break;
                v = v->r;
                continue;
            }
            node *tv = v;
            if (tv->r != nullptr) {
                tv = v->r;
                int lol = tv->val;
                if (lol >= 0)
                {
                    if ((ll)(a[lol] ^ a[i]) == pref[i - 1] - pref[lol])
                    {
                        ++ans;
                    }
                }
            }
            if (v->l == nullptr) break;
            v = v->l;
        }
    }
    return ans;
}
signed main()
{
    fastio();
    int n;
    cin >> n;
    vector<ll> a(n);
    vin(a);
    ll ans = solve(a);
    rev(a);
    ans += solve(a);
    cout << ans << endl;
    //sp;
}