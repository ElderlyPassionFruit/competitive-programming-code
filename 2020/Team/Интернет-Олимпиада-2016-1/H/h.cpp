#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()
/*
const int N = 200;
int a[N][N];

int getMex(int x, int y) {
    vector<int> have;
    for (int i = 0; i < y; ++i) {
        have.push_back(a[x][i]);
    }
    for (int i = 0; i < x; ++i) {
        have.push_back(a[i][y]);
    }
    sort(all(have));
    have.resize(unique(all(have)) - have.begin());
    have.push_back(1e9);
    for (int i = 0; i < have.size(); ++i) {
        if (have[i] != i) {
            return i;
        }
    }
    assert(false);
    return -1;
}

void stupid() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            a[i][j] = getMex(i, j);
        }
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j <= i; ++j) {
            cout << a[i][j] << " ";
            if (a[i][j] < 10) cout << " ";
        }
        cout << endl;
    }
   // exit(0);
}
*/

ll smart(ll a, ll b) {
    //cout << a << " " << b << endl;
    if (a < b) swap(a, b);
    if (a == b) return 0;
    ll p = 1;
    while (p < a + 1) {
        p *= 2;
    }
    //cout << "p = " << p << endl;
    if (b * 2 < p) {
        return smart(a - p / 2, b) + p / 2;
    } else {
        return smart(a - p / 2, b - p / 2);
    }
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    freopen("schedule.in", "r", stdin);
    freopen("schedule.out", "w", stdout);
    /*stupid();
    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= i; j++) {
            cout << smart(i, j) << " ";
            assert(smart(i, j) == a[i][j]);
        }
        cout << endl;
    }
    //cout << smart(3, 2) << endl;
    exit(0);*/
    int q;
    cin >> q;
    while (q--) {
        int x, y;
        cin >> x >> y;
        //cout << a[x][y] << endl;
        cout << smart(x, y) << "\n";
    }    
	return 0;
}