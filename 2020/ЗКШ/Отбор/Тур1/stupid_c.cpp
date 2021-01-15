#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}


int n, k, mod;

void read() {
    cin >> n >> k >> mod;
}

set<vector<int> > used;
set<vector<int> > ans;

void solve(vector<int> a, int n, int k) {
    if (used.count(a)) return;
    used.insert(a);
    if (a.size() == k) {
        ans.insert(a);
        return;
    }
    for (int i = a.back() + 1; i <= n; i++) {
        bool flag = true;
        for (auto j : a) {
            flag &= (j * 2 != i); 
            flag &= (j * 4 != i); 
        }
        if (!flag) continue;
        a.push_back(i);
        solve(a, n, k);
        a.pop_back();
    }
}

int solve(int n, int k) {
    used.clear();
    ans.clear();
    for (int i = 1; i <= n; i++) {
        solve({i}, n, k);
    }
    return ans.size();
}
 
void wr(int n, int k) {
    cout << solve(n, k) << endl;
    for (auto i : ans) {
        for (auto j : i)
            cout << j << " ";
        cout << endl; 
    }
} 

vector<int> make(vector<int> a) {
    vector<int> ans;
    for (int i = 1; i < a.size(); i++) {
        ans.push_back(a[i] - a[i - 1]);
    }
    return ans;
}

void out() {
    for (int t = 0; t < 16; t++){
        for (int i = 16; i <= 160; i += 16) {
            cout << solve(i + t, 3) << " ";
        }
        cout << endl;
    }
}

void run() {
    solve(n, k);
    return;
    out();
    return;
    vector<int> a;

    for (int i = 16; i <= 1000; i += 16) {
        cout << solve(i, 4) << " ";
        cout.flush();
        continue;
        a.push_back(solve(i, 4));
    }
    cout << endl;
    for (int i = 0; i < 20; i++) {
        a = make(a);
        for (auto j : a) cout << j << " ";
        cout << endl; 
    }
    cout << endl;
    /*for (int i = 1; i <= 1; i += 4) {
        for (int j = 1; j <= 20; j++) {
            if (solve(i, j) == 0) break;
            cout << solve(i, j) << " ";
        }
        cout << endl;
    }*/
}

void write() {
    cout << ans.size() % mod << endl;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    read();
    run();
    write();
    return 0;
}