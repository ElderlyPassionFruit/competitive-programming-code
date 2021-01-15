#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int smart(vector <int> a) {
    int ret = 0;
    int c = *max_element(a.begin(), a.end());
    int n = a.size();
    for (int x = 0; x <= c; x++) {
        string s = "";
        for (int i= 0; i < n; i++) {
            if (a[i] <= x) {
                s += '0';
            } else {
                s += '1';
            }
        }
        vector <char> term(n);
        term[0] = true;
        term[n - 1] = true;
        for (int i= 1; i < n; i++) {
            if (s[i] == s[i - 1]) {
                term[i] = term[i - 1] = true;
            }
        }
        int len = 0;
        int ans = 0;
        for (int i= 0; i < n; i++) {
            if (term[i]) {
                ans = max(ans, (len + 1) / 2);
                len = 0;
            } else {
                len++;
            }
        }
        ret = max(ret, ans);
    }
    return ret;
}

int f(int a, int b, int c) {
    vector <int> ord = {a, b, c};
    sort(ord.begin(), ord.end());
    return ord[1];
}

int stup(vector <int> a) {
    int n = (int) a.size();
    for (int it = 0; ; it++) {
        vector <int> b = a;
        bool ch = false;
        for (int i= 1; i + 1 < n; i++) {
            int x =f(a[i-1],a[i],a[i+1]);
            if (a[i] != x) {
                ch = true;
            }
            b[i] = x;
        }
        if (!ch) return it;
        a = b;
    }
}

mt19937 rnd(228);

int main() {
#ifdef iq
    freopen("a.in", "r", stdin);
#endif // iq
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, t;
    cin >> n >> t;
    vector <int> a(n);
    for (int i= 0; i < n; i++) {
        cin >> a[i];
    }
    cout << smart(a) << endl;
}
