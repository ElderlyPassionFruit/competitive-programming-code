#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
#ifdef iq
    freopen("a.in", "r", stdin);
#endif // iq
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vector <int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector <int> ord;
    for (int i = 0; i < n; i++) ord.push_back(i);
    int ans = 0;
    for (int lg = 0; lg <= 25; lg++) {
        vector <int> l, r;
        for (int i : ord) {
            if ((a[i] >> lg) & 1) {
                l.push_back(i);
            } else {
                r.push_back(i);
            }
        }
        ord.clear();
        for (int i : r) ord.push_back(i);
        for (int i : l) ord.push_back(i);
        vector <int> arr;
        for (int i : ord) {
            arr.push_back(a[i] % (1 << (lg + 1)));
        }
        auto f = [&] (int l, int r) {
            int j = -1;
            int k = -1;
            ll ok = 0;
            for (int i = (int) arr.size() - 1; i >= 0; i--) {
                while (j + 1 < (int) arr.size() && arr[i] + arr[j + 1] < l) {
                    j++;
                }
                while (k + 1 < (int) arr.size() && arr[i] + arr[k + 1] <= r) {
                    k++;
                }
                ok += k - j;
            }
            return ok;
        };
        ll cur = f(1 << lg, (1 << (lg + 1)) - 1) + f((1 << (lg + 1)) + (1 << lg), 2 * (1 << (lg + 1)));
        for (int x : arr) {
            if (((x + x) >> lg) & 1) {
                cur--;
            }
        }
        cur /= 2;
        if (cur % 2) ans += (1 << lg);
    }
    cout << ans << endl;
}
