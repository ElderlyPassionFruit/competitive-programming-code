#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <deque>
#include <math.h>
#include <iomanip>
#include <fstream>
#include <set>
#include <map>
#define ll long long
#define ld long double

using namespace std;

vector<ll> a, b;

bool cmp(int x, int y) {
    return b[x] < b[y];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    int n;
    ll bal = 0;
    cin >> n;
    a.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        bal += a[i];
    }
    b.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> b[i];
        bal -= b[i];
    }
    if (bal != 0) {
        cout << "No\n";
        return 0;
    }
    vector<int> inc;
    for (int i = 0; i < n; ++i) {
        if (a[i] > b[i]) {
            if ((a[i] - b[i]) % 2 == 1) {
                cout << "No\n";
                return 0;
            }
            inc.push_back(i);
        }
    }
    for (int i = 1; i < inc.size(); ++i) {
        if (inc[i] == inc[i - 1] + 1) {
            cout << "No\n";
            return 0;
        }
    }
    if (inc.size() > 0 && inc[0] == 0 && inc.back() == n - 1) {
        cout << "No\n";
        return 0;
    }
    vector<ll> a2 = a;
    sort(inc.begin(), inc.end(), cmp);
    for (int ind : inc) {
        //cerr << ind << " ";
        ll need = (a2[ind] - b[ind]) / 2;
        int L1 = (ind - 1 + n) % n;
        int R1 = (ind + 1) % n;
        a2[L1] += (need - 1);
        a2[R1] += (need - 1);
        a2[ind] -= 2 * (need - 1);
        if (a2[ind] < 2 + max(a2[L1], a2[R1])) {
            //for (auto elem : a2)
            //    cerr << elem << "/";
            //cerr << "\n";
            //cerr << ind << " here\n";
            cout << "No\n";
            return 0;
        }
        a2[ind] -= 2;
        a2[L1]++;
        a2[R1]++;
    }
    for (int i = 0; i < n; ++i) {
        if (a2[i] != b[i]) {
            cout << "No\n";
            return 0;
        }
    }
    cout << "Yes\n";
}
//*/