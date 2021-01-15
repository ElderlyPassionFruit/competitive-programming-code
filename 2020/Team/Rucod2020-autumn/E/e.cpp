#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int N = 2e6 + 10;
int n, m;
vector<int> add[N];
vector<pair<int, int>> del[N];

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        if (u > v) swap(u, v);
        add[u].push_back(i);
        del[v].push_back({i, u});
    }
    set<pair<int, int>> st;
    for (int i = 0; i < N; ++i) {
        for (auto [t, pos] : del[i]) {
            auto it = st.find({pos, t});
            st.erase(it);
        }
        for (auto [t, pos] : del[i]) {
            if (!st.empty() && (--st.end())->first > pos) {
                cout << "Unsafe\n";
                return 0;
            }
        }
        for (auto t : add[i]) {
            st.insert({i, t});
        }

        /*cout << "i = " << i << endl;
        for (auto x : st) {
            cout << x.first << " " << x.second << endl;
        }*/
    }
    cout << "Safe\n";
	return 0;
}