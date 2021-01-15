#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

void read() {

}

int calc(vector<int> a) {
    int ans = 0;
    for (auto i : a) {
        ans = (ans * 10 + i) % 7;
    }
    return ans;
}

vector<int> a = {0, 1, 1, 1, 1, 1, 1};
vector<int> b = {1, 0, 0, 0, 0, 0, 0};

int fullCnt = 0;

void relax(vector<int> num) {
    vector<int> mod(7);
    sort(all(num));
    do {
        mod[calc(num)] = 1;
        bool ok = true;
        for (auto i : mod) {
            ok &= i == 1;
        }
        if (ok) {
            break;
        }
    } while (next_permutation(all(num)));
    bool ok = true;
    for (auto i : mod) {
        ok &= i == 1;
    }
    if (ok) {
        /*vector<int> a = num;
        sort(all(num));
        num.resize(unique(all(num)) - num.begin());
    
        if (num.size() < 3) {
            cout << "num = ";
            for (auto i : a) cout << i << " ";
            cout << endl;
        }
        assert(num.size() >= 3);*/
        return;
    }
    cout << "num = ";
    for (auto i : num) {
        cout << i << " ";
    }
    cout << endl;
    sort(all(num));
    num.resize(unique(all(num)) - num.begin());
    assert(num.size() <= 2);
    cout << "num = ";
    for (auto i : num) cout << i << " ";
    cout << endl;
    cout << "mod = ";
    for (auto i : mod) cout << i << " ";
    cout << endl;
    cout << endl;
    ++fullCnt;
    //assert(mod == a || mod == b);
}

void rec(vector<int> num, int val, int n) {
    if (num.size() == n) {
        relax(num);
        return;
    }    
    num.push_back(val);
    while (num.back() < 7) {
        rec(num, num.back(), n);
        num[num.size() - 1]++;
    }
}

void run() {
    rec({}, 0, 13);
    cout << "fullCnt = " << fullCnt << endl;
}

void write() {

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