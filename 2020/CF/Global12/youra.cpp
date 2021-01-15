//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,abm,mmx,avx,avx2,popcnt,tune=native")
//#pragma GCC optimize("fast-math")
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
//#pragma comment(linker, "/STACK:106777216")


#define _CRT_SECURE_NO_WARNINGS
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
#define type type1337
#define right right228
//++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++
using namespace std;
//++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
//++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++
const ld EPS = 1e-5;
const ld EPS2 = 1e-12;
const ld PI = acos(-1);
int mod = (int)998244353;
const int MOD7 = 1000000007;
const int MOD9 = 1000000009;
const int a228 = 18;
const ll INF = 1e18;
const int inf = 1e9;
const ll kekmod = 1791791791;
const ll bestmod = 1148822869;
set<int> sos;
map<int, int> cnt;
int ssm;
void add(int x)
{
    cnt[x]++; ++ssm;
    sos.insert(x);
}
void del(int x)
{
    cnt[x]--; --ssm;
    if (cnt[x] == 0) sos.erase(x);
}
bool oak()
{
    return *sos.rbegin() == sos.size() && sos.size() == ssm;
}
signed main()
{
    fastio();
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        vector<int> a(n);
        ssm = 0;
        vin(a);
        vector<pair<int, int>> st;
        vector<int> lt(n, -1);
        vector<int> rt(n,n);
        for (int i = 0; i < n; ++i)
        {
            while (st.size() && st.back().first > a[i])
            {
                rt[st.back().second] = i;
                st.pob;
            }
            st.pbc({ a[i],i });
        }
        st.clear();
        for (int i = n - 1; i >= 0; --i)
        {
            while (st.size() && st.back().first > a[i])
            {
                lt[st.back().second] = i;
                st.pob;
            }
            st.pbc({ a[i],i });
        }cnt.clear();
        sos.clear();
        vector<int> addbad(n + 1);
        vector<int> delbad(n + 1);
        vector<bool> ok(n + 1, 1);
        vector<int> lst(n + 1, -2);
        vector<int> cunt(n + 1);
        for (int i : a)
        {
            cunt[i]++;
    //      if (cunt[i] == 2) ok[1] = 0;
        }
        vector<vector<int>> vals(n+1);
        for (int i = 0; i < n; ++i)
        {
            int r = rt[i];
            int l = lt[i];
            l = max(l, lst[a[i]]);
            int xx = min(i - l, r - i);
            if (xx >= 2)
            {
                addbad[2] ++;
                delbad[r-l-2]++;
            }
            vals[r - l - 1].pbc(a[i]);
            add(a[i]);
            lst[a[i]] = i;
        }
        int cant = 0;
        for (int i = 1; i <= n; ++i)
        {
            cant += addbad[i];
            if (cant) ok[i] = 0;
            cant -= delbad[i];
        }
        for (int i = 1; i <= n; ++i)
        {
            if (!oak())ok[i] = 0;
            for (int j : vals[i])  del(j);
        }
        for (int i = 1; i <= n; ++i)
        {
            if (ok[i])cout << 1;
            else cout << 0;
        }
        cout << endl;
    }// sp;
}