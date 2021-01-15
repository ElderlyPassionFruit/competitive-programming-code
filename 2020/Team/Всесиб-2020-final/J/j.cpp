#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

void turn(vector<vector<char>>& a) {
    auto ans = a;
    for (int i = 0; i < a.size(); ++i) {
        for (int j = 0; j < a.size(); ++j) {
            a[i][j] = ans[j][a.size() - 1 - i];
        }
    }
}

void swap(vector<vector<char>>& a) {
    auto ans = a;
    for (int i = 0; i < (int)a.size() - 1 - i; ++i) {
        swap(a[i], a[a.size() - 1 - i]);
    }
}

signed main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    int n;
    cin >> n;
    vector<vector<char>> a(n, vector<char>(n));

    vector<vector<char>> b(n, vector<char>(n));
    for (auto& i : a) {
        for (auto&j : i) {
            cin >> j;
        }
    }
    /*turn(a);
    for (auto i : a) {
        for (auto j : i) {
            cout << j;
        }
        cout << endl;
    }
    exit(0);*/
    for (auto& i : b) {
        for (auto& j : i) {
            cin >> j;
        }
    }

    for (int it = 0; it < 2; ++it) {
        for (int it2 = 0; it2 < 4; ++it2) {
            if (a == b) {
                cout << "YES\n";
                return 0;
            }
            turn(a);
        }
        swap(a);
    }
    cout << "NO\n";
	return 0;
}