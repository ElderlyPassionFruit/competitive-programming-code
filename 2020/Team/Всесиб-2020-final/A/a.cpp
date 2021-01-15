#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

void solve() {
    string s;
    getline(cin, s);
    bool ok = true;
    char last = ' ';
    for (auto i : s) {
        if ((last == ':' || last == '-') && i != ' ') {
            cout << ' ';
            ok = true;
        }
        if (i == ':' || i == '-') {
            if (!ok) {
                cout << ' ';
            }
            ok = false;
        } else if (i == ' ') {
            ok = true;
        } else {
            ok = false;
        }
        last = i;
        cout << i;
    }
    cout << '\n';
}

signed main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    string a;
    getline(cin, a);
    int t = stoi(a);
    while (t--) {
        solve();
    }
	return 0;
}