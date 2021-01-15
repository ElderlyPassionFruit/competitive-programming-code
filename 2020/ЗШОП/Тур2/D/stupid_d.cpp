#include <bits/stdc++.h>
 
using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()
 
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
 
int n, m, q;
string s, t;
 
vector<int> z_function(const string & s) {
    int n = s.size();
    vector<int> z(n);
    int l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        if (i <= r)
            z[i] = min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[i + z[i]] == s[z[i]]) z[i]++;
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return z;
}
 
vector<ll> a;
vector<ll> pref;
 
void build() {
    string help;
    vector<int> z;
    vector<int> ans_s, ans_t;
 
    // Строим подстроки S
    help = t + "$" + s;
    z = z_function(help);
 
    ans_t.assign(n, 0);
    for (int i = t.size() + 1; i < help.size(); i++) {
        ans_t[i - t.size() - 1] = z[i];
    }
 
    help = s + "$" + s;
    reverse(all(help));
    z = z_function(help);
    ans_s.assign(n, 0);
 
    for (int i = s.size() + 1; i < help.size(); i++) {
        ans_s[i - s.size() - 1] = z[i];
    } 
    reverse(all(ans_s));
 
    a.assign(n, 0);
    for (int i = 1; i < n; i++) {
        if (ans_s[i - 1] == 0) continue;
        chkmax(a[n - ans_s[i - 1]], ans_t[i]);
    }
 
    // Строим подстроки T
    help = t + "$" + t;
    z = z_function(help);
    ans_t.assign(m, 0);
 
    /*cout << "help = " << endl;
    for (auto i : help)
        cout << i << " ";
    cout << endl;
 
    cout << "z = " << endl;
    for (auto i : z)
        cout << i << " ";
    cout << endl;*/
 
    for (int i = t.size() + 1; i < help.size(); i++) {
        ans_t[i - t.size() - 1] = z[i];
    }
 
    help = t + "$" + s;
    reverse(all(help));
    z = z_function(help);
    ans_s.assign(m, 0);
    for (int i = s.size() + 1; i < help.size(); i++) {
        ans_s[i - s.size() - 1] = z[i];
    }
    reverse(all(ans_s));
 
 
    /*cout << "ans_s = " << endl;
    for (auto i : ans_s)
        cout << i << " ";
    cout << endl;
 
    cout << "ans_t = " << endl;
    for (auto i : ans_t)
        cout << i << " ";
    cout << endl;*/
 
    for (int i = 1; i < m; i++) {
        if (ans_s[i - 1] == 0) continue;
        chkmax(a[n - ans_s[i - 1]], ans_t[i]);
    }
 
    for (int i = 1; i < n; i++)
        chkmax(a[i], a[i - 1]);
 
    //pref = a;
    //for (int i = 1; i < n; i++)
    //  pref[i] += pref[i - 1];
}   
 
ll get(ll ls, ll rs, ll lt, ll rt) {
    ll ans = 0;
    for (int i = ls; i <= rs; i++) {
        ans += max(0LL, min(rt - lt + 1, a[i] - lt));   
    }
    return ans;
}
 
void solve() {
    build();
    /*cout << "a = " << endl;
    for (auto i : a)
        cout << i << " ";
    cout << endl;*/
    while (q--) {
        int ls, rs, lt, rt;
        cin >> ls >> rs >> lt >> rt;
        ls--;
        rs--;
        lt--;
        rt--;
        cout << get(ls, rs, lt, rt) << "\n";
    }
}
 
signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    while (cin >> n >> m >> q >> s >> t) {
        solve();
    }
    return 0;
}