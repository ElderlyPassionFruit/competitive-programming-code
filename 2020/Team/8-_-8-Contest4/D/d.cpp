/*#pragma GCC optimize("Ofast")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("unswitch-loops")
#pragma GCC optimize("fast-math")
#pragma GCC optimize("section-anchors")
#pragma GCC optimize("profile-reorder-functions")
#pragma GCC optimize("profile-values")
#pragma GCC optimize("tracer")
#pragma GCC optimize("vpt")
#pragma GCC optimize("rename-registers")
#pragma GCC optimize("move-loop-invariants")
#pragma GCC optimize("function-sections")
#pragma GCC optimize("data-sections")
#pragma GCC optimize("branch-target-load-optimize")
#pragma GCC optimize("branch-target-load-optimize2")
#pragma GCC optimize("btr-bb-exclusive")
#pragma GCC target("sse2")
#pragma GCC target("sse3")
#pragma GCC target("ssse3")
#pragma GCC target("sse4.1")
#pragma GCC target("sse4.2")
#pragma GCC target("avx")
#pragma GCC target("avx2")
#pragma GCC target("popcnt")
#pragma GCC target("abm")
#pragma GCC target("mmx")
#pragma GCC target("tune=native")*/
#pragma GCC target("avx,avx2")
#pragma GCC target("sse,sse2,sse3,ssse3")

#include<bits/stdc++.h>
using namespace std;
#define ii pair <int, int>
#define app push_back
#define all(a) a.begin(), a.end()
#define bp __builtin_popcountll
#define ll long long
#define mp make_pair
#define f first
#define s second
#define Time (double)clock()/CLOCKS_PER_SEC
#define debug(x) std::cout << #x << ": " << x << '\n';

const int MAXA = 26;

bool win[(1 << MAXA) + 5];
bool used[MAXA];

signed main() {
    /*#ifdef HOME
    freopen("input.txt", "r", stdin);
    #else
    #define endl '\n'
    freopen("forbidden-words.in", "r", stdin);
    freopen("forbidden-words.out", "w", stdout);
    ios_base::sync_with_stdio(0); cin.tie(0);
    #endif*/

    int n;
    //cin >> n;
    n = 2;
    vector<string> t = {"a", "ab"};
    for (int i = 0; i < n; ++i) {
    	fill(used, used + MAXA, 0);
        string s = t[i];
        //cin >> s;
        for (char c : s)
            used[c - 'a'] = 1;
        int mask = 0;
        for (int j = 0; j < MAXA; ++j)
            if (used[j])
                mask += 1 << j;
        win[mask] = 1;                    
    }   

    for (int bit = 0; bit < MAXA; ++bit)
        for (int i = 0; i < (1 << MAXA); ++i)
            if ((i >> bit) & 1)
                win[i] = win[i] | win[i ^ (1 << bit)];

    for (int mask = (1 << MAXA) - 1; mask >= 0; --mask) {
        if (win[mask])
            continue;
        for (int i = 0; i < MAXA; ++i) {
            if ((mask >> i) & 1)
                continue;
            if (!win[mask + (1 << i)]) {
                win[mask] = 1;
                break;
            }
        }   
    }                   

    if (win[0])
        cout << "First" << endl;
    else
        cout << "Second" << endl;

    freopen("bracket-expression.in", "r", stdin);
    freopen("bracket-expression.out", "w", stdout);
    cout << 3 << endl;
    /*#ifdef HOME
    cout << Time << endl;
    #endif*/
}