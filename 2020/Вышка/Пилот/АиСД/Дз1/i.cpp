#include <bits/stdc++.h>

using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(a) a.begin(), a.end()

using namespace std;

template<typename T1, typename T2> inline void chkmin(T1& x, const T2& y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1& x, const T2& y) {if (x < y) x = y;}

int q;
multiset<int> a;

vector<string> ans;

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.setf(ios::fixed), cout.precision(20);
    int q;
    cin >> q;
    while (q--) {
        string s;
        cin >> s;
        if (s == "insert") {
            int x;
            cin >> x;
            a.insert(x);
            ans.push_back(s + " " + to_string(x));
        } else if (s == "removeMin") {
            if (a.empty()) {
                ans.push_back("insert 1");
                a.insert(1);
            }
            a.erase(a.begin());
            ans.push_back(s);
        } else if (s == "getMin") {
            int x;
            cin >> x;
            if (!a.count(x)) {
                ans.push_back("insert " + to_string(x));
                a.insert(x);
            }
            while (*a.begin() != x) {
                ans.push_back("removeMin");
                a.erase(a.begin());
            }
            ans.push_back(s + " " + to_string(x));
        } else {
            assert(false);
        }
    }
    cout << ans.size() << '\n';
    for (auto i : ans) {
        cout << i << '\n';
    }
    return 0;
}