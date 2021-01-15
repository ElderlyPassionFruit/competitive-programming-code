#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

void out(vector<char> have, int w) { 
    for (int i = 0; i < have.size(); ++i) {
        cout << have[i];
        if ((i + 1) % w ==0) cout << endl;
    }
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    

    /*vector<char> have(391);
    for (auto& i : have) {
        cin >> i;
    }
    out(have, 23);*/

    vector<vector<char>> have;
    char x;
    while (cin >> x) {
        if (have.empty()) {
            have.push_back({});
        } else if (have[have.size() - 1].size() == 23) {
            have.push_back({});
        }
        have[have.size() - 1].push_back(x);
    }

    vector<ll> fans;

    for (int i = 0; i < 23; ++i) {
        int p = 0;
        bool flag = false;
        ll ans = 0;
        for (int j = have.size() - 1; j >= 0; --j) {
            if (have[j][i] == '.') {
                if (flag) ++p;
                continue;
            }
            if (flag) {
                ans += 1LL << p;
                ++p;
            } else {
                flag = true;
            }
        }
        if (flag) {
            fans.push_back(ans);
        }
    }

    for (int i = 0; i < fans.size(); ++i) {
        if (i > 0) cout << " ";
        cout << fans[i];
    }

    /*for (int i = 30; i < 50; ++i) {
        out(have, i);
        cout << endl << endl << endl;
    }*/
    /*int x;
    while (cin >> x) {
        cout << static_cast<char>(x);
    }*/
	return 0;
}