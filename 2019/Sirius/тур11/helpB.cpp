#include <bits/stdc++.h>
 
using namespace std;
#define int long long
int n, q;
const int MAXN = 1e6 + 10;
int arr[MAXN];
void read() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
}
vector <int> ans;
 
multiset <int> pos;
multiset <int> bad;
 
void fans2(int a, int b) {
    if (a <= b) {
        a ^= b;
        int p = -1;
        while (a) {
            a /= 2;
            p++;
        }
        bad.insert(p);
    }
    else {
        a ^= b;
        int p = -1;
        while (a) {
            a /= 2;
            p++;
        }
        pos.insert(p);
    }
}
 
void fans3(int a, int b) {
    if (a <= b) {
        a ^= b;
        int p = -1;
        while (a) {
            a /= 2;
            p++;
        }
        bad.erase(bad.find(p));
    }
    else {
        a ^= b;
        int p = -1;
        while (a) {
            a /= 2;
            p++;
        }
        pos.erase(pos.find(p));
    }
}
 
void fans(int v, int val) {
    if (v > 0) {
        fans3(arr[v - 1], arr[v]);
    }
    if (v < n - 1) {
        fans3(arr[v], arr[v + 1]);
    }
    arr[v] = val;
    if (v > 0) {
        fans2(arr[v - 1], arr[v]);
    }
    if (v < n - 1) {
        fans2(arr[v], arr[v + 1]);
    }
}
 
set <int> help;
 
void check() {
    int b = 0;
    for (auto i : pos) {
        b += pow(2, i);
    }
     
    bool flag = true;
    for (int i = 0; i < 31; i++) {
        bool p = pos.find(i) != pos.end();
        bool b = bad.find(i) != bad.end();
        if (p == true && b == true) {
            flag = false;
            break;
        }
    }
 
    if (flag) {
        ans.push_back(b);
    }
    else {
        ans.push_back(-1);
    }
}
 
void make() {
    for (int i = 1; i < n; i++) {
        int a, b;
        a = arr[i - 1];
        b = arr[i];
        if (a <= b) {
            a ^= b;
            int p = -1;
            while (a) {
                a /= 2;
                p++;
            }
            bad.insert(p);
        }
        else {
            a ^= b;
            int p = -1;
            while (a) {
                a /= 2;
                p++;
            }
            pos.insert(p);
        }
    }
}
 
void run() {
    make();
    check();
    cin >> q;
    while (q--) {
        int pos, val;
        cin >> pos >> val;
        pos--;
        fans(pos, val);
        check();
    }
}
 
void write() {
    for (auto i : ans) {
        cout << i << endl;
    }
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