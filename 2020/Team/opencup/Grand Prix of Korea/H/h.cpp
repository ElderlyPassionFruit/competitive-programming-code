#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

#define int ll

const int N = 1e5 + 228;
int n;
int cnt[N];

const int INF = 1e18;

int add(int a, int b) {
    if (a + b > INF) return INF;
    return a + b;
}

bool check(int x) {
    int sumSuff = 1;
    int fadd = 0;
    for (int i = N - 1; i > 0; --i) {
        if (i >= x) {
            fadd = add(fadd, cnt[i]);
        } else {
            if (cnt[i] >= sumSuff) {
                fadd = add(fadd, cnt[i] - sumSuff);
            } else {
                sumSuff = add(sumSuff, sumSuff - cnt[i]);
            }
        }
    }
    return cnt[0] + fadd >= sumSuff;
}

void checkOne() {
    int sum = accumulate(cnt, cnt + N, 0LL);
    if (sum == 1) {
        int ans = max_element(cnt, cnt + N) - cnt;
        ans = max(ans, 1LL);
        cout << ans << "\n";
        exit(0);
    }
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> cnt[i];
    }
    /*n = 1e5;
    for (int i = 0; i < n; ++i) {
        cnt[i] = 1e9;
    }*/
    checkOne();
    int l = 0, r = N;
    while (l < r - 1) {
        int mid = (l + r) / 2;
        if (check(mid)) {
            l = mid;
        } else {
            r = mid;
        }
    }
    cout << l << "\n";
	return 0;
}