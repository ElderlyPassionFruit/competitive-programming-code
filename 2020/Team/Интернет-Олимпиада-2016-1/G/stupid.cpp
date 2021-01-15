#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

int n;
vector<string> a;

string get(string a, int mask) {
    string ans = "";
    for (int i = 0; i < a.size(); ++i) {
        if ((mask >> i) & 1) {
            ans += a[i];
        }
    }
    return ans;
}

void relax(string& a, string b) {
    if (a.size() > b.size()) return;
    if (a.size() == b.size() && a >= b) return;
    a = b;
}

string get(string a, string b) {
    string have = "";
    for (int i = 0; i < (1 << (int)a.size()); ++i) {
        string now = get(a, i);
        if (now.size() > b.size() || (now.size() == b.size() && now > b)) {
            continue;
        }
        relax(have, now);
    }
    return have;
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cout.setf(ios::fixed), cout.precision(20);
    /*cin >> n;
    a.resize(n);
    for (auto& i : a) {
        cin >> i;
    }
    int ans = 0;
    for (int i = n - 2; i >= 0; --i) {
        string now = get(a[i], a[i + 1]);
        if (now.empty()) {
            cout << "-1\n";
            exit(0);
        }
        ans += (int)a[i].size() - (int)now.size();
        a[i] = now;
    }
    cout << ans << endl;*/
    string a, b;
    cin >> a >> b;
    cout << get(a, b) << endl;
    return 0;  
}