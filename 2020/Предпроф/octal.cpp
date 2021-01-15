#include <bits/stdc++.h>

using namespace std;

signed main() {
    int x;
    cin >> x;
    string ans = "";
    while (x) {
        ans += x % 8 + '0';
        x /= 8;
    }
    reverse(ans.begin(), ans.end());
    cout << ans;
    return 0;
}