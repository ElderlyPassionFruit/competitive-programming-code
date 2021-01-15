#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

int n, w, d;
const int C = 41, W = 110;
int cnt[C];

int ansVal[W], ansCnt[W];

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    cin >> n >> w >> d;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        cnt[x]++;
    }
    int topAns = 0;
    for (int i = 0; i < C; ++i) {
        if (!cnt[i]) continue;
        ansCnt[topAns] = cnt[i];
        ansVal[topAns] = i;
        topAns++;
    }
    if (topAns > w) {
        cout << "-1\n";
        return 0;
    }
    for (int i = 0; i < topAns; ++i) {
        if (ansCnt[i] > d) {
            cout << "-1\n";
            return 0;
        }
    }
    if (topAns != w) {
        cout << "-1\n";
        return 0;
    }
    for (int i = 0; i < topAns; ++i) {
        cout << ansVal[i] << " ";
    }
    cout << "\n";
    for (int i = 0; i < topAns; ++i) {
        cout << ansCnt[i] << " ";
    }
    cout << "\n";
	return 0;
}