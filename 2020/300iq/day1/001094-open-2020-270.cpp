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
    auto f = [&] (int a, int b, int c) {
        vector <int> ord = {a, b, c};
        sort(ord.begin(), ord.end());
        return ord[1];
    };
    bool ch = true;
    int ans = 0;
    while (ch) {
        ch = false;
        vector <int> b = a;
        for (int i = 1; i + 1 < n; i++) {
            int x = f(a[i - 1], a[i], a[i + 1]);
            if (a[i] != x) ch = true;
            b[i] = x;
        }
        a = b;
        ans += ch;
    }
    cout << ans << endl;
    if (t == 1)
    for (int i = 0; i < n; i++) {
        cout << a[i] << ' ';
    }
    cout << endl;
}
