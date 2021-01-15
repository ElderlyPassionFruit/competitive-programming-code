#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

int n;
vector<int> a;

void read() {
    cin >> n;
    a.resize(n);
    for (auto& i : a) {
        cin >> i;
    }
}

void no() {
    cout << "No\n";
    exit(0);
}

vector<int> order;
vector<pair<int, int>> ans;

void run() {
    /*vector<int> compressed = a;
    sort(all(compressed));
    compressed.resize(unique(all(compressed)) - compressed.begin());
    for (auto& i : a) {
        i = lower_bound(all(compressed) - compressed.begin());
    }*/
    /*
    vector<int> cnt(compressed.size());
    vector<int> pref(compressed.size() + 1);
    for (auto i : a) {
        cnt[i]++;
    }
    for (int i = 1; i < pref.size(); ++i) {
        pref[i] = pref[i - 1] + cnt[i - 1];
    }*/
    vector<int> sorted = a;
    sort(all(sorted));

    /*cerr << "sorted = " << endl;
    for (auto i : sorted) {
        cerr << i << " ";
    }
    cerr << endl;*/

    map<pair<int, int>, vector<int>> need;

    for (int i = 0; i < n; ++i) {
        int needType = sorted[i];
        if (a[i] == needType) continue;
        if (need[{a[i], needType}].size()) {
            ans.push_back({i, need[{a[i], needType}].back()});
            need[{a[i], needType}].pop_back();
        } else {
            need[{needType, a[i]}].push_back(i);
        }
    }
    for (auto i : need) {
        if (!i.second.empty()) {
            no();
        }
    }
}

void write() {
    cout << "Yes\n";
    cout << ans.size() << '\n';
    for (auto i : ans) {
        cout << i.first + 1 << ' ' << i.second + 1 << '\n';
    }
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
    read();
    run();
    write();
    return 0;
}