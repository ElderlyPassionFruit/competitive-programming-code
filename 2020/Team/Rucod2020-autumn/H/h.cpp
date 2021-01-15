#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int N = 1e5 + 10;
int n, m;
int a[N], b[N];

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> b[i];
    }
    sort(a, a + n);
    reverse(a, a + n);
    sort(b, b + n);
    reverse(b, b + n);
    ll now = 0;
    for (int i = 0; i < n; ++i) {
        now += a[i];
        if (now >= m) {
            cout << "MIPT\n";
            return 0;
        }
        now -= b[i];
        if (now <= -m) {
            cout << "HSE\n";
            return 0;
        }
    }
    cout << "NO\n";
	return 0;
}