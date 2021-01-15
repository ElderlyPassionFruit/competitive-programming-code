#include <bits/stdc++.h>

using namespace std;
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

vector <int> z_function(vector<int> s) {
    int n = s.size();
    vector<int> z(n, 0);
    int l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        if (i <= r)
            z[i] = min(z[i - l], r - i + 1);
        while (z[i] + i < n && s[z[i]] == s[z[i] + i])
            z[i]++;
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return z;
}

int n, m;
vector<int> a;
vector<int> z;
void read() {
    cin >> n >> m;
    a.resize(n);
    for (auto &i : a)
        cin >> i;
    z = a;
    reverse(a.begin(), a.end());


    for (int i = 0; i < n; i++)
        z.push_back(a[i]);
   
    z = z_function(z);
}

vector<int> ans;

void run() {
    ans.push_back(n);
    for (int i = 1; i <= n / 2; i++) {
        if (z[2 * n - 2 * i] >= i)
            ans.push_back(n - i);
    } 
}

void write() {
    sort(ans.begin(), ans.end());
    for (auto i : ans) {
        cout << i << " ";
    }
    cout << endl;
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