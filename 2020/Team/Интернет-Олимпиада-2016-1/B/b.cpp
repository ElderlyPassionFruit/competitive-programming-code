#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int N = 1e3 + 10;
int n;
int d[N][N];

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    cin >> n;
    int x = 0, y = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> d[i][j];
            if (d[i][j] > d[x][y]) {
                x = i;
                y = j;
            }
        }
    }
    cout << "x = " << x << " y = " << y << endl;
    vector<int> order(n);
    iota(all(order), 0);
    sort(all(order), [&] (int a, int b) {return d[x][a] < d[x][b];});
    vector<int> realX(n);
    for (int i = 0; i < n; ++i) {
        realX[i] = d[x][i];
    } 
    cout << "order = " << endl;
    for (auto i : order) {
        cout << i << " ";
    }
    cout << endl;
    vector<int> rorder(n);
    for (int i = 0; i < n; ++i) {
        rorder[order[i]] = i;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (abs(realX[i] - realX[rorder[j]]) != d[i][j]) {
                cout << "NO" << endl;
                exit(0);
            }
        }
    }
    cout << "YES\n";
    for (auto i : realX) {
        cout << i << " ";
    }
    cout << endl;
    for (int i = 0; i < n; ++i) {
        cout << i + 1 << " ";
    }
    cout << endl;
    for (auto i : rorder) {
        cout << i + 1 << " ";
    }
    cout << endl;
	return 0;
}