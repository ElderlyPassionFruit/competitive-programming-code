#include <bits/stdc++.h>

using namespace std;
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

vector<int> build(string & s) {
    s += "$";
    int n = s.length();
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        a[i] = i;
    sort(a.begin(), a.end(), [&] (int i, int j) {return s[i] < s[j];});

    vector<int> c(n);
    int cc = 0;
    for (int i = 0; i < n; i++) {
        if (i == 0 || s[a[i]] != s[a[i - 1]])
            c[a[i]] = cc++;
        else
            c[a[i]] = c[a[i - 1]];
    }

    for (int l = 1; l < n; l *= 2) {
        vector<int> cnt(n);
        for (auto i : c)
            cnt[i]++;

        vector<int> pref(n);
        for (int i = 1; i < n; i++)
            pref[i] = cnt[i - 1] + pref[i - 1];

        vector<int> na(n);
        for (int i = 0; i < n; i++) {
            int ind = (a[i] - l + n) % n;
            na[pref[c[ind]]++] = ind;
        }
        a = na;
        cc = 0;
        vector<int> nc(n);
        for (int i = 0; i < n; i++) {
            if (i == 0 || c[a[i]] != c[a[i - 1]] || c[(a[i] + l) % n] != c[(a[i - 1] + l) % n])
                nc[a[i]] = cc++;
            else
                nc[a[i]] = nc[a[i - 1]];
        }
        c = nc;
    }
    a.erase(a.begin());
    return a;
}

void solve() {
    string s;
    cin >> s;
    auto ans = build(s);
    for (auto i : ans)
        cout << i + 1 << " ";
    cout << endl;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    solve();
    return 0;
}