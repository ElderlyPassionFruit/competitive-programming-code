#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int INF = -1e9;

vector<int> build_suff(vector<int> & s) {
    s.push_back(INF);
    int n = s.size();
    vector<int> a(n);
    iota(all(a), 0);
    stable_sort(all(a), [&] (int i, int j) {return s[i] < s[j];});
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
            pref[i] = pref[i - 1] + cnt[i - 1];
        vector<int> na(n);
        for (int i = 0; i < n; i++) {
            int ind = (a[i] - l + n) % n;
            na[pref[c[ind]]++] = ind;
        }
        a = na;
        vector<int> nc(n);
        int cc = 0;
        for (int i = 0; i < n; i++) {
            if (i == 0 || c[a[i]] != c[a[i - 1]] || c[(a[i] + l) % n] != c[(a[i - 1] + l) % n])
                nc[a[i]] = cc++;
            else
                nc[a[i]] = nc[a[i - 1]];
        }
        c = nc;
    }
    return a;
}

vector<int> build_lcp(vector<int> & a, vector<int> & s) {
    int n = a.size();
    vector<int> ra(n);
    for (int i = 0; i < n; i++)
        ra[a[i]] = i;
    vector<int> lcp(n - 1);
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        cnt--;
        chkmax(cnt, 0);
        if (ra[i] == n - 1) {
            cnt = 0;
            continue;
        }
        int j = a[ra[i] + 1];
        while (s[i + cnt] == s[j + cnt])
            cnt++;
        lcp[ra[i]] = cnt;
    }
    a.erase(a.begin());
    s.pop_back();
    lcp.erase(lcp.begin());
    return lcp;
}

int n, m;
vector<int> s;

void read() {
    cin >> n >> m;
    s.resize(n);
    for (auto &i : s)
        cin >> i;
}

int cnt;
vector<int> ans;

void run() {
    auto a = build_suff(s);
    auto lcp = build_lcp(a, s);
    cnt = 1;
    int pos = 0, len = n;
    vector<int> ra(n);
    for (int i = 0; i < n; i++)
        ra[a[i]] = i;

    /*for (int i = 0; i < n; i++) {
        int x = n - a[i];
        for (int j = i; j < n - 1; j++) {
            chkmin(x, lcp[j]);
            if (x * (j - i + 2) > len * cnt) {
                pos = a[i];
                len = x;
                cnt = j - i + 2;
            }
        }
    }*/
    vector<int> st, l(n - 1), r(n - 1);
    for (int i = 0; i < n - 1; i++) {
        l[i] = 0;
        while (!st.empty() && lcp[st.back()] >= lcp[i])
            st.pop_back();
        if (!st.empty())
            l[i] = st.back() + 1;
        st.push_back(i);
    }
    st.clear();
    for (int i = n - 2; i >= 0; i--) {
        r[i] = n - 1;
        while (!st.empty() && lcp[st.back()] >= lcp[i])
            st.pop_back();
        if (!st.empty())
            r[i] = st.back();
        st.push_back(i);
    }

    for (int i = 0; i < n - 1; i++) {
        if ((ll)(r[i] - l[i] + 1) * lcp[i] > (ll) cnt * len) {
            len = lcp[i];
            pos = a[i];
            cnt = r[i] - l[i] + 1;
        }
    }
    for (int i = pos; i < pos + len; i++)
        ans.push_back(s[i]);
}

void write() {
    cout << (ll)cnt * ans.size() << endl;
    cout << ans.size() << endl;
    for (auto i : ans)
        cout << i << " ";
    cout << endl;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    read();
    run();
    write();
    return 0;
}
