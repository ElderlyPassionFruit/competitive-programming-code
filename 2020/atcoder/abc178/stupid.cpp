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
deque<int> b;

void read() {
    cin >> n;
    a.resize(n);
    for (auto &i : a) {
        cin >> i;
    }
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        b.push_back(x);
    }
}

mt19937 rnd(time(0));
vector<int> order;

bool check() {
    for (auto i : order) {
        if (a[i] == b[i]) {
            return false;
        }
    }
    return true;
}

void nxt() {
    b.push_back(b[0]);
    b.pop_front();
}

void run() {
    order.resize(n);
    iota(all(order), 0);
    shuffle(all(order), rnd);
    /*
    do {
        if (check()) {
            cout << "Yes\n";
            for (auto i : b) {
                cout << i << " ";
            }
            cout << "\n";
            exit(0);
        }
    } while (next_permutation(all(b)));*/
    for (int i = 0; i < n; i++) {
        if (check()) {
            cout << "Yes\n";
            /*for (auto i : b) {
                cout << i << " ";
            }
            cout << "\n";*/
            exit(0);
        }
        nxt();
    }
}

void write() {
    cout << "No\n";
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
    read();
    run();
    write();
    return 0;
}
