#include <bits/stdc++.h>

using namespace std;
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

namespace hashs{
    const int MAXN = 1e6 + 10, MOD = 1e9 + 7, b = 179;
    int n, m;
    int pows[MAXN], h1[MAXN], h2[MAXN];

    void make(string & s, string & t) {
        pows[0] = 1;
        for (int i = 1; i < MAXN; i++) {
            pows[i] = (long long) pows[i - 1] * b % MOD;
        }

        n = s.size();
        h1[0] = 0;
        for (int i = 1; i <= n; i++) {
            h1[i] = (((long long)h1[i - 1] * pows[1] % MOD) + (long long)s[i - 1]) % MOD;
        }

        m = t.size();
        h2[0] = 0;
        for (int i = 1; i <= m; i++) {
            h2[i] = (((long long)h2[i - 1] * pows[1] % MOD) + (long long)t[i - 1]) % MOD;
        }
    }   

    int get1(int l, int r) {
        return (((long long)h1[r] - (long long)h1[l - 1] * pows[r - l + 1]) % MOD + MOD) % MOD; 
    }

    int get2(int l, int r) {
        return (((long long)h2[r] - (long long)h2[l - 1] * pows[r - l + 1]) % MOD + MOD) % MOD; 
    }

    bool get(int pos) {
        if (get1(1, 1) != get2(pos, pos))
            return get1(2, n) == get2(pos + 1, pos + n - 1);

        int l = 0, r = n;
        while (l < r - 1) {
            int mid = (l + r) / 2;
            if (get1(1, 1 + mid) == get2(pos, pos + mid))
                l = mid;
            else
                r = mid;
        }

        if (l >= n - 2) return true;
        return get1(1 + l + 2, n) == get2(pos + l + 2, pos + n - 1);
    }
};

void solve() {
    string s, t;
    cin >> s >> t;
    hashs::make(s, t);
    int n = s.size(), m = t.size();
    vector<int> ans;

    for (int i = 1; i + n - 1 <= m; i++) {
        if (hashs::get(i))
            ans.push_back(i);
    }

    cout << ans.size() << endl;
    for (auto i : ans)
        cout << i << " ";
    cout << endl;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    solve();
    return 0;
}