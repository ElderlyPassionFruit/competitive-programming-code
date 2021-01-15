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
    b.push_front(b.back());
    b.pop_back();
}

bool check(int la, int ra, int lb, int rb) {
    return max(la, lb) <= min(ra, rb);
}

vector<int> pref;

void ban(int l, int r) {
    //cout << "l = " << l << " r = " << r << endl;
    pref[l]++;
    pref[r + 1]--;
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
    
    pref.assign(5 * n + 10, 0);

    vector<int> l(n + 1, n), r(n + 1, -1);
    for (int i = 0; i < n; i++) {
        chkmin(l[a[i]], i);
        chkmax(r[a[i]], i);
    }
    for (int L = 0; L < n; L++) {
        if (l[b[L]] == n) continue;
        int R = L;
        while (R < n && b[R] == b[L]) R++;
        R--;
        if (check(l[b[L]], r[b[L]], L, R)) {
            ban(0, r[b[L]] - L);
        } else {
            if (R < l[b[L]]) {
                ban(l[b[L]] - R, r[b[L]] - L);
            } else {
                l[b[L]] += n;
                r[b[L]] += n;
                ban(l[b[L]] - R, r[b[L]] - L);
            }
        }
        L = R;
    }

    for (int i = 1; i < 5 * n; i++) {
        pref[i] += pref[i - 1];
    }
    for (int i = 0; i < 5 * n + 10; i++) {
        pref[i % n] += pref[i];
    }
    /*cout << "pref = " << endl;
    for (int i = 0; i < n; i++) {
        cout << pref[i] << " ";
    }
    cout << endl;*/
    for (int i = 0; i < n; i++) {
        /*cout << "i = " << i << endl;
        cout << "b = " << endl;
        for (auto x : b) {
            cout << x << " ";
        }
        cout << endl;*/
        if (pref[i] == 0 && check()) {
            cout << "Yes\n";
            for (auto i : b) {
                cout << i << " ";
            }
            cout << "\n";
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
