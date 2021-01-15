#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

int n;
map<string, int> a;

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    cin >> n;
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        a[s]++;
    }
    vector<pair<int, string>> ans;
    for (auto i : a) {
        ans.push_back({i.second, i.first});
    }
    sort(all(ans));
    if (ans[ans.size() - 1].first * 2 <= n) {
        cout << "NONE\n";
    } else {
        cout << ans.back().second << "\n";
    }
	return 0;
} 