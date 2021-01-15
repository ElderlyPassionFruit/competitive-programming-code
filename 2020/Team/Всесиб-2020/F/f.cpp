#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

#define int ll

int INF;

vector<int> primes;

int mul(int a, int b) {
    if (INF / a < b) return INF;
    return a * b;
}

vector<int> nums;

void rec(int now, int pos) {
    if (pos == primes.size()) {
        nums.push_back(now);
        return;
    }
    while (now < INF) {
        rec(now, pos + 1);
        now = mul(now, primes[pos]);
    }
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    int x;
    cin >> x;
    for (int i = 2; i * i <= x; ++i) {
        if (x % i) continue;
        primes.push_back(i);
        while (x % i == 0) {
            x /= i;
        }
    }
    if (x > 1) {
        primes.push_back(x);
    }
    sort(all(primes));
    cin >> INF;
    INF++;
    rec(1, 0);
    sort(all(nums));
    int t;
    cin >> t;
    while (t--) {
        int x;
        cin >> x;
        auto now = lower_bound(all(nums), x);
        if (now == nums.end() || *now >= INF) {
            cout << -1 << "\n";
        } else {
            cout << *now - x << "\n";
        }
    }
    return 0;
}