#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}


const int MOD = 998244353;

int add(int a, int b) {
    a += b;
    if (a >= MOD) return a - MOD;
    return a;
}

int sub(int a, int b) {
    a -= b;
    if (a < 0) return a + MOD;
    return a;
}

int mul(int a, int b) {
    return (ll) a * b % MOD;
}

int n;
map<int, int> cnt;

void read() {
    cin >> n;
    n *= 2;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        cnt[x]++;
    } 
}

vector<int> mul(vector<int> a, vector<int> b) {
    vector<int> ans(a.size() + b.size());
    for (int i = 0; i < (int)a.size(); ++i) {
        for (int j = 0; j < (int)b.size(); ++j) {
            ans[i + j] = add(ans[i + j], mul(a[i], a[j]));
        }
    }
    return ans;
}

vector<int> myMerge(vector<int> a, vector<int> b) {
    vector<int> ans(a.size() + b.size());
    for (int i = 0; i < (int)a.size(); ++i) {
        for (int j = 0; j < (int)b.size(); ++j) {
            ans[abs(j - i)] = add(ans[abs(j - i)], mul(a[i], b[j]));
        }
    } 
    cout << "a = " << endl;
    for (auto i : a) {
        cout << i << " ";
    }
    cout << endl;
    cout << "b = " << endl;
    for (auto i : b) {
        cout << i << " ";
    }
    cout << endl;
    cout << "ans = " << endl;
    for (auto i : ans) {
        cout << i << " ";
    }
    cout << endl;
    return ans;
}

int ans;

void run() {
    multiset<pair<int, vector<int>>> fans;
    for (auto i : cnt) {
        vector<int> a(i.second + 1, 0);
        a[i.second] = 1;
        fans.insert({i.second, a});
    }

    while (fans.size() >= 2) {
        auto it1 = *fans.begin();
        fans.erase(fans.begin());
        auto it2 = *fans.begin();
        fans.erase(fans.begin());
        fans.insert({it1.first + it2.first, myMerge(it1.second, it2.second)});
    }
    ans = fans.begin()->second[0];
}

void write() {
    cout << ans << endl;
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
    read();
    run();
    write();
    return 0;
}