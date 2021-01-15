#include <bits/stdc++.h>

using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(a) a.begin(), a.end()

using namespace std;

template<typename T1, typename T2> inline void chkmin(T1& x, const T2& y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1& x, const T2& y) {if (x < y) x = y;}

const int N = 6e5 + 10;
int n, q;
int a[N];

void read() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
}

const int INF = 1e9 + 228;

struct Stack{
    vector<int> st;
    vector<int> minVal;
    vector<int> maxVal;
    Stack() {}
    void push(int x) {
        st.push_back(x);
        minVal.push_back(x);
        maxVal.push_back(x);
        if (st.size() >= 2) {
            chkmin(minVal[minVal.size() - 1], minVal[minVal.size() - 2]);
            chkmax(maxVal[maxVal.size() - 1], maxVal[maxVal.size() - 2]);
        }
    }
    void pop() {
        st.pop_back();
        minVal.pop_back();
        maxVal.pop_back();
    }
    int getVal() {
        return st.back();
    }
    int getMax() {
        return (maxVal.empty() ? -INF : maxVal.back());
    }
    int getMin() {
        return (minVal.empty() ? INF : minVal.back());
    }
};

struct Queue{
    Stack top, bottom;
    Queue() {}
    void relax() {
        while (!bottom.st.empty()) {
            top.push(bottom.getVal());
            bottom.pop();
        }
    }
    void push(int x) {
        bottom.push(x);
    }
    void pop() {
        if (top.st.empty()) {
            relax();
        }
        top.pop();
    }
    int getMax() {
        return max(top.getMax(), bottom.getMax());
    }
    int getMin() {
        return min(top.getMin(), bottom.getMin());
    }
};

int ansL, ansR;

void relax(int l, int r) {
    if (r - l > ansR - ansL) {
        ansL = l;
        ansR = r;
    }
}

void solve() {
    int k;
    cin >> k;
    ansL = 0, ansR = 0;
    int r = 0;
    Queue q;
    q.push(a[0]);
    for (int l = 0; l < n; ++l) {
        while (r < n && q.getMax() - q.getMin() <= k) {
            relax(l, r);
            ++r;
            q.push(a[r]);
        }
        q.pop();
    }
    cout << ansL + 1 << " " << ansR + 1 << '\n';
}

void run() {
    cin >> q;
    while (q--) {
        solve();
    }
}

void write() {

}

signed main() {
    freopen("e.in", "r", stdin);
    freopen("e.out", "w", stdout);
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.setf(ios::fixed), cout.precision(20);
    read();
    run();
    write();
    return 0;
}