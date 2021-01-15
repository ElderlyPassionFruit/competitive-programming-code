#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cout.setf(ios::fixed), cout.precision(20);
    cout << "vector<string> words = {";
    string s;
    while (cin >> s) {
        cout << "\"" << s << "\",";
    }
    cout << "};";
    return 0;
}