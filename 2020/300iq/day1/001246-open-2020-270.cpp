#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

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
    int ret = 0;
    for (int x = 0; x <= 100; x++) {
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
        for (int i = n - 2; i >= 0; i--) {
            if (s[i] == s[i + 1]) {
                term[i] = term[i + 1] = true;
            }
        }
        int len = 0;
        int ans = 0;
        for (int i= 0; i < n; i++) {
            if (term[i]) {
                ans += (len + 1) / 2;
                len = 0;
            } else {
                len++;
            }
        }
        ret = max(ret, ans);
    }
    cout << ret << endl;
}
