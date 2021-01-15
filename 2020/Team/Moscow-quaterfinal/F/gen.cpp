#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

#define int ll

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

int get(int l, int r) {
    return rnd() % (r - l + 1) + l;
}

const int INF = 1e18 + 228;

const int N = 8;
const int S = 50;

vector<int> gen(int n, int sum) {
    vector<int> a;
    a.resize(n);
    for (int i = 0; i < n - 1; ++i) {
        int x = get(0, sum);
        sum -= x;
        a[i] = x;
    }
    a[n - 1] = sum;
    shuffle(all(a), rnd);
    return a;
}

void make(vector<int>& a, int pos, bool& flag) {
    int n = a.size();
    int prev = (pos - 1 + n) % n;
    int nxt = (pos + 1) % n;
    if (a[pos] - 2 >= max(a[prev], a[nxt])) {
        flag = true;
        a[pos] -= 2;
        a[prev]++;
        a[nxt]++;
    } else {
        flag = false;
    }
}

vector<int> gen(vector<int> a, int cntOp) {
    for (int i = 0; i < cntOp; ++i) {
        vector<int> order(a.size());
        iota(all(order), 0);
        shuffle(all(order), rnd);
        for (auto i : order) {
            bool flag = false;
            make(a, i, flag);
            if (flag) break;
        }
    }
    return a;
}

void tryBuild() {
    int n = get(3, N);
    cout << n << endl;
    int sum = get(1, S);
    auto a = gen(n, sum);
    auto b = gen(a, get(0, S));
    for (auto i : a) {
        cout << i << " ";
    }
    cout << endl;
    for (auto i : b) {
        cout << i << " ";
    }
    cout << endl;
    exit(0);
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
    while (true) {
        tryBuild();
    }
    return 0;
}