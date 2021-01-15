#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int N = 1e6 + 10;
int n;
int p[N];
bool used[N];
int a[N];
int cnt[N];

int calc(int pos) {
    used[pos] = true;
    int len = 1;
    int s = pos;
    while (p[pos] != s) {
        pos = p[pos];
        used[pos] = true;
        len++;
    }
    return len;
}

void build() {
    int sz = 0;
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            a[sz++] = calc(i);
        }
    }
    n = sz;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    cin >> n;
    int k = n;
    for (int i = 0; i < n; ++i) {
        cin >> p[i];
        p[i]--;
    }
    build();
    sort(a, a + n);
    for (int i = 0; i < n; ++i) {
        cnt[a[i]]++;
        cnt[a[i]] = min(2, cnt[a[i]]);
    }
    for (int i = 1; i <= k; ++i) {
        if (a[n - 1] >= i) {
            cout << "Yes\n";
            continue;
        }
        if (cnt[i]) {
            cout << "Yes\n";
            continue;
        }
        int pos = lower_bound(a, a + n, (i + 1) / 2) - a;
        if (pos == n) {
            cout << "No\n";
            continue;
        }
        bool ok = false;
        for (int j = pos; j < n; ++j) {
            if (a[j] + a[j] == i) {
                if (cnt[a[j]] == 2) {
                    ok = true;
                    break;
                }
            } else {
                if (cnt[i - a[j]]) {
                    ok = true;
                    break;
                }
            }
        }
        if (ok) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
	return 0;
}