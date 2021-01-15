#include <bits/stdc++.h>

using namespace std;
#define int long long

int get(int x) {
    int ans = 1;
    for (int i = 2; i * i <= x; i++) {
        if (x % i) continue;
        int now = 0;
        while (x % i == 0) {
            x /= i;
            now++;
        }
        ans *= now + 1;
    }
    if (x > 1) ans *= 2;
    return ans;
}

signed main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n;
    cin >> n;
    int now = 0;
    int add = 1;
    while (true) {
        now += add;
        add++;
        if (get(now) > n) {
            cout << now << endl;
            return 0;
        }
    }
    return 0;
}