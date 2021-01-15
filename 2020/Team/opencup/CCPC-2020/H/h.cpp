#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int N = 1e5 + 228, M = 2e5 + 228;
int n, m, s;

int ans[M];
vector<int> have[M];
unordered_map<int, vector<pair<int, int>>> a[M];

int get(int y, int l, int r) {
    return lower_bound(all(have[y]), r) - lower_bound(all(have[y]), l);
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    cin >> m >> n >> s;
    for (int i = 0; i < s; ++i) {
        int t;
        cin >> t;
        int x, y;
        cin >> x >> y;
        if (t == 1) {
            a[x][y].push_back({i, s});
        } else if (t == 2) {
            a[x][y][a[x][y].size() - 1].second = i;
        } else {
            have[y].push_back(i);
            ans[x]--;
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (auto [y, border] : a[i]) {
            for (auto [l, r] : border) {
                ans[i] += get(y, l, r);
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        cout << ans[i] << '\n';
    }
	return 0;
}