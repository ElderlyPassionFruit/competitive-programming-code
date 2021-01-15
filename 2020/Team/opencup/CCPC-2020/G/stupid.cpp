#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int mod = 65536;

int main() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int j = 0; j < q; ++j) {
        int tp;
        cin >> tp;
        if (tp == 1) {
            int l, r;
            cin >> l >> r;
            l--; r--;
            for (int i = l; i <= r; ++i) {
                a[i]++;
                if (a[i] == mod) {
                    a[i] = 0;
                }
            }
        } else {
            int L1, L2, len;
            cin >> L1 >> L2 >> len;
            L1--;
            L2--;
            bool flag = 1;
            for (int i = 0; i < len; ++i) {
                if (a[L1 + i] != a[L2 + i]) {
                    flag = 0;
                    break;
                }
            }
            if (flag) {
                cout << "yes\n";
            } else{
                cout << "no\n";
            }
        }
    }
}